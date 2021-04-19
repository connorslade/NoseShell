#include <utility>
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <unistd.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "windows.h"
#else
#include <sstream>
#include <sys/ioctl.h>
#endif

#include "common.hpp"
#include "config.hpp"

namespace common {
    // Function to print with colors using ANSI codes
    void debugPrint(std::string text, int colorCode, std::string stringEnd) {
        std::cout << "\x1B[1;" << colorCode << "m" << text << "\033[0m" << stringEnd;
    }

    // DebugPrint based on return status of a command
    void returnPrint(int cmdRet, std::string text) {
        int colorCode = config::cmdSuccess;
        if (cmdRet != 0)
            colorCode = config::cmdFail;
        std::cout << "\x1B[1;" << colorCode << "m" << text << "\033[0m";
    }

    // Return Ansi Code for color
    std::string colorFromCode(int code) {
        std::string color = "\x1B[1;" + std::to_string(code) + "m";
        return color;
    }

    // Enable AnsiCodes for windows
    void enableAnsiCodes() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        DWORD l_mode;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleMode(hStdout, &l_mode);
        SetConsoleMode(hStdout, l_mode | 0x0004 | 0x0008);
#endif
    }

    // DebugPrint then Exit
    void errorPrint(std::string text, int colorCode, int exitCode) {
        debugPrint(std::move(text), colorCode);
        std::cout << "\x1B[33m";
        system("pause");
        std::cout << "\033[0m";
        exit(exitCode);
    }

    // Get Width and Height of Console
    void refreshConsoleInfo(int &w, int &h) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

        w = size.ws_col;
        h = size.ws_row;
#endif
    }

    // Get current time as a String
    std::string getTime() {
        time_t rawTime;
        struct tm *timeInfo;
        char buffer[80];

        time(&rawTime);
        timeInfo = localtime(&rawTime);

        strftime(buffer, sizeof(buffer), "%H:%M:%S", timeInfo);
        std::string str(buffer);

        return str;
    }

    // I wish I knew what this did :/
    /*std::wstring ExePath() {
        TCHAR buffer[1024] = { 0 };
        GetModuleFileName( NULL, buffer, 1024 );
        std::wstring::size_type pos = std::wstring(reinterpret_cast<const wchar_t *>(buffer)).find_last_of(L"\\/");
        return std::wstring(reinterpret_cast<const wchar_t *>(buffer)).substr(0, pos);
    }
    */

    // Get current Working Dir
    std::string getDir() {
        char buffer[config::maxDir];
        if (getcwd(buffer, sizeof(buffer)) != nullptr) return std::string(buffer);
        return "";
    }

    // Split String to Vector based on char
    void tokenize(std::string const &str, const char delim, std::vector<std::string> &out) {
        size_t start;
        size_t end = 0;

        while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
            end = str.find(delim, start);
            out.push_back(str.substr(start, end - start));
        }
    }

    std::string getTrueValue(std::string command) {
        for (const auto &alia : config::alias) {
            if (command == alia[0]) return alia[1];
        }
        return command;
    }

    std::string vectorToString(std::vector<std::string> strings) {
        const char *const delim = " ";

        std::ostringstream imploded;
        std::copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(imploded, delim));

        return imploded.str();
    }
}