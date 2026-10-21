#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <cctype>

using namespace std;

vector<int> getTests(const string& testFolder)
{
    vector<int> tests;

    string searchPath = testFolder + "\\test*.in";

    WIN32_FIND_DATAA data;

    HANDLE h = FindFirstFileA(
        searchPath.c_str(),
        &data
    );

    if (h == INVALID_HANDLE_VALUE)
        return tests;

    do
    {
        string name = data.cFileName;

        if (name.size() > 7 &&
            name.substr(0, 4) == "test" &&
            name.substr(name.size() - 3) == ".in")
        {
            string number =
                name.substr(4, name.size() - 7);

            bool valid = !number.empty();

            for (char c : number)
            {
                if (!isdigit((unsigned char)c))
                {
                    valid = false;
                    break;
                }
            }

            if (valid)
                tests.push_back(stoi(number));
        }

    } while (FindNextFileA(h, &data));

    FindClose(h);

    sort(tests.begin(), tests.end());

    return tests;
}

string getCurrentDirectory()
{
    char buffer[MAX_PATH];

    DWORD len = GetCurrentDirectoryA(
        MAX_PATH,
        buffer
    );

    if (len == 0)
        return "";

    return string(buffer);
}

string quote(const string& s)
{
    return "\"" + s + "\"";
}

int runProcess(
    const string& program,
    const string& arguments
)
{
    string command =
        quote(program) + " " + arguments;

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

    vector<char> cmd(
        command.begin(),
        command.end()
    );

    cmd.push_back('\0');

    BOOL created = CreateProcessA(
        NULL,
        cmd.data(),
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (!created)
        return -1;

    WaitForSingleObject(
        pi.hProcess,
        INFINITE
    );

    DWORD exitCode = 1;

    BOOL gotExitCode =
        GetExitCodeProcess(
            pi.hProcess,
            &exitCode
        );

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (!gotExitCode)
        return -1;

    return (int)exitCode;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout
            << "USAGE: judge.exe <problem_id> <submission.cpp>"
            << endl;

        return 1;
    }

    string problemId = argv[1];
    string submission = argv[2];

    string root = getCurrentDirectory();

    if (root.empty())
    {
        cout << "JUDGE_ERROR" << endl;
        return 1;
    }

    string problemFolder =
        root +
        "\\problems\\" +
        problemId;

    string testFolder =
        problemFolder +
        "\\tests";

    string toolsFolder =
        problemFolder +
        "\\tools";

    string runner =
        root +
        "\\output\\runner.exe";

    string checker =
        toolsFolder +
        "\\checker.exe";

    string outputFolder =
        root +
        "\\output";

    vector<int> tests =
        getTests(testFolder);

    if (tests.empty())
    {
        cout << "NO_TESTS" << endl;
        return 0;
    }

    ifstream runnerCheck(runner);

    if (!runnerCheck)
    {
        cout
            << "RUNNER_NOT_FOUND"
            << endl;

        return 1;
    }

    ifstream checkerCheck(checker);

    if (!checkerCheck)
    {
        cout
            << "CHECKER_NOT_FOUND"
            << endl;

        return 1;
    }

    string submissionPath = submission;

    if (submissionPath.find(":\\") == string::npos)
    {
        submissionPath =
            root +
            "\\" +
            submissionPath;
    }

    ifstream submissionCheck(submissionPath);

    if (!submissionCheck)
    {
        cout
            << "SUBMISSION_NOT_FOUND"
            << endl;

        return 1;
    }

    string exeName =
        outputFolder +
        "\\submission_" +
        to_string(GetCurrentProcessId()) +
        ".exe";

    string compileArguments =
        quote(submissionPath) +
        " -o " +
        quote(exeName);

    cout << "Compiling..." << endl;

    int compileResult =
        runProcess(
            "g++",
            compileArguments
        );

    if (compileResult != 0)
    {
        cout
            << "COMPILATION_ERROR"
            << endl;

        return 0;
    }

    cout << "Compilation successful." << endl;
    cout << endl;

    for (int i : tests)
    {
        string inputFile =
            testFolder +
            "\\test" +
            to_string(i) +
            ".in";

        string resultFile =
            outputFolder +
            "\\test" +
            to_string(i) +
            "_result.out";

        DeleteFileA(
            resultFile.c_str()
        );

        cout
            << "Test "
            << i
            << ": ";

        string runnerArguments =
            quote(inputFile) +
            " " +
            quote(resultFile) +
            " " +
            quote(exeName);

        int runnerResult =
            runProcess(
                runner,
                runnerArguments
            );

        if (runnerResult == 2)
        {
            DeleteFileA(
                exeName.c_str()
            );

            cout
                << "TIME_LIMIT_EXCEEDED"
                << endl;

            return 0;
        }

        if (runnerResult == 4)
        {
            DeleteFileA(
                exeName.c_str()
            );

            cout
                << "MEMORY_LIMIT_EXCEEDED"
                << endl;

            return 0;
        }

        if (runnerResult == 3)
        {
            DeleteFileA(
                exeName.c_str()
            );

            cout
                << "RUNTIME_ERROR"
                << endl;

            return 0;
        }

        if (runnerResult == 1 ||
            runnerResult == -1)
        {
            DeleteFileA(
                exeName.c_str()
            );

            cout
                << "RUNNER_ERROR"
                << endl;

            return 0;
        }

        if (runnerResult != 0)
        {
            DeleteFileA(
                exeName.c_str()
            );

            cout
                << "RUNNER_ERROR"
                << endl;

            return 0;
        }

        string checkerArguments =
            quote(inputFile) +
            " " +
            quote(resultFile);

        int checkerResult =
            runProcess(
                checker,
                checkerArguments
            );

        if (checkerResult == 0)
        {
            cout
                << "AC"
                << endl;
        }
        else if (checkerResult == 1)
        {
            DeleteFileA(
                exeName.c_str()
            );

            cout
                << "WA"
                << endl;

            return 0;
        }
        else
        {
            DeleteFileA(
                exeName.c_str()
            );

            cout
                << "CHECKER_ERROR"
                << endl;

            return 0;
        }
    }

    DeleteFileA(
        exeName.c_str()
    );

    cout << endl;
    cout << "ACCEPTED" << endl;

    return 0;
}