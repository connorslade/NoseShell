#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <unistd.h>
#include <vector>
#include <algorithm>


#include "common.h"

#define Max_Len 1024

int main() {
    std::vector<std::string> validShellCommands {"cd"};
    std::vector<std::string> out;
    std::string workingDir, tmpString, cdStr;
    int cmdRet = 0, w, h;
    std::string line;
    DWORD l_mode;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hStdout, &l_mode);
    SetConsoleMode(hStdout, l_mode | 0x0004 | 0x0008);

    debugPrint("\x1B[1;34mWelcome to NOSE SHELL! \x1B[35mV0.0.1", 32);
    debugPrint("Copyright (C) Connor Slade. All rights reserved.\n", 35);

    while (true) {
        refreshConsoleInfo(w, h);
        workingDir = "\n[*] \033[33m[" + getDir() + "]";
        returnPrint(cmdRet, workingDir);
        std::cout << "\033[" << std::to_string(w - (5 + workingDir.length())) << "C\033[36m[" << getTime() << "]\033[0m\033[" << std::to_string(w - workingDir.length() + 4)<< "D";

        if (!std::getline(std::cin, line)) break;
        tokenize(line, ' ', out);

        if (out.size() < 1)
            out.push_back(line);

        if (out.at(0) == "cd"){
            SetCurrentDirectory(out.at(1).c_str());
            out.erase(out.begin() , out.end());
            continue;
        }
        if (out.at(0) == "exit"){
            exit(0);
        }

        std::cout << "\033[F\033[2K" << "\x1B[33m * " << line << "\x1B[35m" << std::endl;
        cmdRet = system(line.c_str());
        out.erase(out.begin() , out.end());
    }

    return 0;
}