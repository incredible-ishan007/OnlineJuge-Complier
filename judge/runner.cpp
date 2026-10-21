#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const SIZE_T MEMORY_LIMIT = 256ULL * 1024ULL * 1024ULL;
const DWORD TIME_LIMIT = 2000;

bool containsBadAlloc(const string& file)
{
    ifstream in(file);

    if (!in)
        return false;

    string line;

    while (getline(in, line))
    {
        if (line.find("bad_alloc") != string::npos)
            return true;

        if (line.find("std::bad_alloc") != string::npos)
            return true;

        if (line.find("bad allocation") != string::npos)
            return true;
    }

    return false;
}

bool isMemoryError(DWORD code)
{
    return code == 0xC0000017 ||
           code == 0xC000009A ||
           code == 0xC000012D;
}

void closeHandles(
    HANDLE process,
    HANDLE thread,
    HANDLE job
)
{
    if (process != NULL)
        CloseHandle(process);

    if (thread != NULL)
        CloseHandle(thread);

    if (job != NULL)
        CloseHandle(job);
}

int main(int argc, char* argv[])
{
    SetErrorMode(
        SEM_NOGPFAULTERRORBOX |
        SEM_FAILCRITICALERRORS |
        SEM_NOOPENFILEERRORBOX
    );

    if (argc != 4)
    {
        cout << "RUNNER_ERROR" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];
    string executable = argv[3];

    string errorFile = "output\\error.txt";

    HANDLE input = CreateFileA(
        inputFile.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (input == INVALID_HANDLE_VALUE)
    {
        cout << "RUNNER_ERROR" << endl;
        return 1;
    }

    HANDLE output = CreateFileA(
        outputFile.c_str(),
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (output == INVALID_HANDLE_VALUE)
    {
        CloseHandle(input);

        cout << "RUNNER_ERROR" << endl;
        return 1;
    }

    HANDLE error = CreateFileA(
        errorFile.c_str(),
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (error == INVALID_HANDLE_VALUE)
    {
        CloseHandle(input);
        CloseHandle(output);

        cout << "RUNNER_ERROR" << endl;
        return 1;
    }

    SetHandleInformation(
        input,
        HANDLE_FLAG_INHERIT,
        HANDLE_FLAG_INHERIT
    );

    SetHandleInformation(
        output,
        HANDLE_FLAG_INHERIT,
        HANDLE_FLAG_INHERIT
    );

    SetHandleInformation(
        error,
        HANDLE_FLAG_INHERIT,
        HANDLE_FLAG_INHERIT
    );

    HANDLE job = CreateJobObjectA(
        NULL,
        NULL
    );

    if (job == NULL)
    {
        CloseHandle(input);
        CloseHandle(output);
        CloseHandle(error);

        cout << "RUNNER_ERROR" << endl;
        return 1;
    }

    JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits;

    ZeroMemory(
        &limits,
        sizeof(limits)
    );

    limits.ProcessMemoryLimit = MEMORY_LIMIT;

    limits.BasicLimitInformation.LimitFlags =
        JOB_OBJECT_LIMIT_PROCESS_MEMORY |
        JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;

    BOOL limitSet = SetInformationJobObject(
        job,
        JobObjectExtendedLimitInformation,
        &limits,
        sizeof(limits)
    );

    if (!limitSet)
    {
        CloseHandle(input);
        CloseHandle(output);
        CloseHandle(error);
        CloseHandle(job);

        cout << "RUNNER_ERROR" << endl;
        return 1;
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(
        &si,
        sizeof(si)
    );

    ZeroMemory(
        &pi,
        sizeof(pi)
    );

    si.cb = sizeof(si);

    si.dwFlags = STARTF_USESTDHANDLES;

    si.hStdInput = input;
    si.hStdOutput = output;
    si.hStdError = error;

    string command =
        "\"" + executable + "\"";

    vector<char> commandLine(
        command.begin(),
        command.end()
    );

    commandLine.push_back('\0');

    BOOL created = CreateProcessA(
        executable.c_str(),
        commandLine.data(),
        NULL,
        NULL,
        TRUE,
        CREATE_NO_WINDOW | CREATE_SUSPENDED,
        NULL,
        NULL,
        &si,
        &pi
    );

    CloseHandle(input);
    CloseHandle(output);
    CloseHandle(error);

    if (!created)
    {
        CloseHandle(job);

        cout << "FAILED_TO_START" << endl;
        return 1;
    }

    BOOL assigned = AssignProcessToJobObject(
        job,
        pi.hProcess
    );

    if (!assigned)
    {
        TerminateProcess(
            pi.hProcess,
            1
        );

        WaitForSingleObject(
            pi.hProcess,
            1000
        );

        closeHandles(
            pi.hProcess,
            pi.hThread,
            job
        );

        cout << "RUNNER_ERROR" << endl;
        return 1;
    }

    DWORD resumeResult =
        ResumeThread(pi.hThread);

    if (resumeResult == (DWORD)-1)
    {
        TerminateJobObject(
            job,
            1
        );

        WaitForSingleObject(
            pi.hProcess,
            1000
        );

        closeHandles(
            pi.hProcess,
            pi.hThread,
            job
        );

        cout << "RUNNER_ERROR" << endl;
        return 1;
    }

    DWORD waitResult =
        WaitForSingleObject(
            pi.hProcess,
            TIME_LIMIT
        );

    if (waitResult == WAIT_TIMEOUT)
    {
        TerminateJobObject(
            job,
            124
        );

        WaitForSingleObject(
            pi.hProcess,
            1000
        );

        closeHandles(
            pi.hProcess,
            pi.hThread,
            job
        );

        cout << "TIME_LIMIT" << endl;
        return 2;
    }

    if (waitResult == WAIT_FAILED)
    {
        TerminateJobObject(
            job,
            1
        );

        closeHandles(
            pi.hProcess,
            pi.hThread,
            job
        );

        cout << "RUNNER_ERROR" << endl;
        return 1;
    }

    DWORD exitCode = 0;

    BOOL gotExitCode =
        GetExitCodeProcess(
            pi.hProcess,
            &exitCode
        );

    if (!gotExitCode)
    {
        closeHandles(
            pi.hProcess,
            pi.hThread,
            job
        );

        cout << "RUNNER_ERROR" << endl;
        return 1;
    }

    bool memoryLimit = false;

    if (isMemoryError(exitCode))
        memoryLimit = true;

    if (containsBadAlloc(errorFile))
        memoryLimit = true;

    closeHandles(
        pi.hProcess,
        pi.hThread,
        job
    );

    if (memoryLimit)
    {
        cout << "MEMORY_LIMIT" << endl;
        return 4;
    }

    if (exitCode != 0)
    {
        cout << "RUNTIME_ERROR" << endl;
        return 3;
    }

    cout << "OK" << endl;

    return 0;
}