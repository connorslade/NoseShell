#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "windows.h"
#else
#include <filesystem>
#endif

#include "common.hpp"
#include "config.hpp"

int main() {
    std::vector<std::string> out;
    std::string workingDir, line, command;
    int cmdRet = 0, w, h;

    common::enableAnsiCodes();
    common::debugPrint("\x1B[1;34mWelcome to NOSE SHELL! \x1B[35mV0.0.3", 32);
    common::debugPrint("Copyright (C) Connor Slade. All rights reserved... NOT! :P\n", 35);

    while (true) {
        common::refreshConsoleInfo(w, h);
        workingDir = "\n[*] " + common::colorFromCode(config::dirBar) + "[" + common::getDir() + "]";
        common::returnPrint(cmdRet, workingDir);

        if (config::showTime)
            std::cout << "\033[" << std::to_string(w - (5 + workingDir.length())) << "C"
                      << common::colorFromCode(config::timeBar) << "[" << common::getTime() << "]\033[0m\033["
                      << std::to_string(w - workingDir.length() + 4) << "D";

        if (!std::getline(std::cin, line)) break;
        common::tokenize(line, ' ', out);

        if (out.empty()) out.push_back(line);
        command = common::getTrueValue(out.at(0));
        out[0] = command;


        if (command == "cd") {
            std::cout << "\033[F\033[2K" << "\x1B[1;33m * " << line << "\x1B[0;0m" << std::endl;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
            try { SetCurrentDirectory(out.at(1).c_str()); }
#else
                try { std::filesystem::current_path(out.at(1).c_str()); }
#endif
            catch (...) { common::debugPrint("Error: \x1B[34m" + out.at(1) + " \x1B[31mIs not a Folder", 31); }
            out.erase(out.begin(), out.end());
            continue;
        }

        if (command == "nose") {
            std::cout << "\033[F\033[2K" << "\x1B[1;33m * " << line << "\x1B[0;0m" << std::endl;
            common::debugPrint(config::nose, 32);
            out.erase(out.begin(), out.end());
            continue;
        }

        if (command == "exit") exit(0);

        std::cout << "\033[F\033[2K" << "\x1B[1;33m * " << line << "\x1B[0;0m" << std::endl;
        cmdRet = system(common::vectorToString(out).c_str());
        out.erase(out.begin(), out.end());
    }

    return 0;
}

/* [ TODO ]

x Make ls Run ls -CF --color=auto
x add alaises
x make cd Not crach when given non exsisnat folder or any file
* Make Fully Cross platform
x put all Config stuff in config Namespace
* make command lowercase for internal commandws

*/