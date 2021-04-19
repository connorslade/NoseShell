#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <sys/ioctl.h>
#include <unistd.h>

#include "common.hpp"
#include "config.hpp"

namespace common {
    // Function to print with colors useing ANSI codes
    void debugPrint(std::string text, int colorcode, std::string stringEnd) {
        std::cout << "\x1B[1;" << colorcode << "m" << text << "\033[0m" << stringEnd;
    }

    // DebugPrint based on return status of a command
    void returnPrint(int cmdRet, std::string text){
        int colorcode = config::cmdSuccess;
        if (cmdRet != 0)
            colorcode = config::cmdFail;
        std::cout << "\x1B[1;" << colorcode << "m" << text << "\033[0m";
    }

    // Return Ansi Code for color
    std::string colorFromCode(int code){
        std::string color = "\x1B[1;" + std::to_string(code) + "m";
        return color;
    }

    // DebugPrint then Exit
    void errorPrint(std::string text, int colorcode, int exitCode){
        debugPrint(text, colorcode);
        std::cout << "\x1B[33m";
        system("pause");
        std::cout << "\033[0m";
        exit(exitCode);
    }

    // Get Width and Height of Console
    void refreshConsoleInfo(int& w, int& h){
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

        w = size.ws_col;
        h = size.ws_row;
    }

    // Get current time as a String
    std::string getTime(){
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,sizeof(buffer),"%H:%M:%S",timeinfo);
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

    // Get current WOrking Dir
    std::string getDir() {
        char buffer[config::maxDir];
        if (getcwd(buffer, sizeof(buffer)) != NULL) return std::string(buffer);
        return "";
    }

    // Split String to Vector based on char
    void tokenize(std::string const &str, const char delim, std::vector<std::string> &out) {
        size_t start;
        size_t end = 0;

        while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
        {
            end = str.find(delim, start);
            out.push_back(str.substr(start, end - start));
        }
    }

    std::string getTrueVaule(std::string command) {
        for (int i = 0; i < sizeof(config::alias)/sizeof(config::alias[0]); i++) {
            if (command == config::alias[i][0]) return config::alias[i][1];
        }
        return command;
    }

    std::string vectorToString(std::vector<std::string> strings) {
        const char* const delim = " ";

        std::ostringstream imploded;
        std::copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(imploded, delim));

        return imploded.str();
    }
}