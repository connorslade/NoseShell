#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

#include "common.h"

#define Max_Len 1024

int main() {
    int cmdRet = 0;
    char line[Max_Len];
    DWORD l_mode;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hStdout, &l_mode);
    SetConsoleMode(hStdout, l_mode | 0x0004 | 0x0008);

    debugPrint("\x1B[1;32m#### Welcome to NOSE SHELL! ####\n                     \x1B[35mV0.0.1\n", 32);

    while (true) {
        returnPrint(cmdRet, "[*]");
        if (!fgets(line, Max_Len, stdin)) break;
        std::cout << "\033[F\033[2K" << "\x1B[33m * " << line << "\x1B[35m" << std::endl;
        cmdRet = system(line);
    }

    return 0;
}