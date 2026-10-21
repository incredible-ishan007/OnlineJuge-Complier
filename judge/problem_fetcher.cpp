#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

string getBetween(string s, string a, string b)
{
    size_t x = s.find(a);

    if (x == string::npos)
        return "";

    x += a.size();

    size_t y = s.find(b, x);

    if (y == string::npos)
        return "";

    return s.substr(x, y - x);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "USAGE: problem_fetcher.exe <problem_url>" << endl;
        return 1;
    }

    string url = argv[1];

    size_t p = url.find("/problemset/problem/");

    if (p == string::npos)
    {
        cout << "INVALID_CODEFORCES_URL" << endl;
        return 1;
    }

    string rest = url.substr(p + 20);

    size_t slash = rest.find('/');

    if (slash == string::npos)
    {
        cout << "INVALID_CODEFORCES_URL" << endl;
        return 1;
    }

    string contestId = rest.substr(0, slash);
    string index = rest.substr(slash + 1);

    size_t end = index.find('/');

    if (end != string::npos)
        index = index.substr(0, end);

    cout << "Contest: " << contestId << endl;
    cout << "Problem: " << index << endl;

    string command =
        "curl.exe -L -s "
        "\"https://codeforces.com/api/problemset.problems\" "
        "-o \"output\\cf_api.json\"";

    int result = system(command.c_str());

    if (result != 0)
    {
        cout << "DOWNLOAD_ERROR" << endl;
        return 1;
    }

    ifstream file("output\\cf_api.json");

    if (!file)
    {
        cout << "DOWNLOAD_ERROR" << endl;
        return 1;
    }

    string json(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    string target =
        "\"contestId\":" + contestId +
        ",\"index\":\"" + index + "\"";

    size_t pos = json.find(target);

    if (pos == string::npos)
    {
        cout << "PROBLEM_NOT_FOUND" << endl;
        return 1;
    }

    size_t problemStart = json.rfind("{", pos);

    size_t problemEnd = json.find("}", pos);

    if (problemStart == string::npos ||
        problemEnd == string::npos)
    {
        cout << "PARSE_ERROR" << endl;
        return 1;
    }

    string problem =
        json.substr(
            problemStart,
            problemEnd - problemStart + 1
        );

    string name =
        getBetween(
            problem,
            "\"name\":\"",
            "\""
        );

    string rating =
        getBetween(
            problem,
            "\"rating\":",
            ","
        );

    string tags =
        getBetween(
            problem,
            "\"tags\":[",
            "]"
        );

    string folder =
        "problems\\" + contestId;

    string makeFolder =
        "mkdir \"" + folder + "\" 2>nul";

    system(makeFolder.c_str());

    ofstream out(
        folder + "\\problem.txt"
    );

    if (!out)
    {
        cout << "FILE_ERROR" << endl;
        return 1;
    }

    out << "Contest ID: "
        << contestId << '\n';

    out << "Problem: "
        << index << '\n';

    out << "Name: "
        << name << '\n';

    out << "Rating: "
        << rating << '\n';

    out << "Tags: "
        << tags << '\n';

    out.close();

    cout << "DOWNLOADED" << endl;
    cout << "Name: " << name << endl;
    cout << "Rating: " << rating << endl;
    cout << "Saved: problems\\" << contestId
         << "\\problem.txt" << endl;

    return 0;
}