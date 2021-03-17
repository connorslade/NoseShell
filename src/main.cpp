#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <unistd.h>
#include <vector>

#include "common.h"

#define Max_Len 1024

int main() {
    std::vector<std::string> validShellCommands {"cd"};
    std::vector<std::string> out;
    std::string workingDir, tmpString, cdStr;
    int cmdRet = 0, w, h;
    char line[Max_Len];
    DWORD l_mode;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hStdout, &l_mode);
    SetConsoleMode(hStdout, l_mode | 0x0004 | 0x0008);

    debugPrint("\x1B[1;34mWelcome to NOSE SHELL! \x1B[35mV0.0.1", 32);
    debugPrint("Copyright (C) Connor Slade. All rights reserved.\n", 35);

    while (true) {
        refreshConsoleInfo(w, h);
        workingDir = "[*] \033[33m[" + getDir() + "]";
        returnPrint(cmdRet, workingDir);
        std::cout << "\033[" << std::to_string(w - (5 + workingDir.length())) << "C\033[36m[" << getTime() << "]\033[0m\033[" << std::to_string(w - workingDir.length() + 3)<< "D";
        if (!fgets(line, Max_Len, stdin)) break;

        tmpString.assign(line, line + Max_Len);
        tokenize(tmpString, ' ', out);

        if (in_array(out[0], validShellCommands)){
            cdStr = getDir() + "\\" + out[1];
            std::cout << cdStr << " ~~~ " << tmpString;
            SetCurrentDirectory(tmpString.c_str());
        }

        std::cout << "\033[F\033[2K" << "\x1B[33m * " << line << "\x1B[35m" << std::endl;
        cmdRet = system(line);
    }

    return 0;
}