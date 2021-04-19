// Suckless inspired Config system

#include <string>
#include <vector>

#ifndef NOSESHELL_CONFIG_HPP
#define NOSESHELL_CONFIG_HPP
namespace config {
    /* COLORES */
    static const int cmdSuccess = 32;
    static const int cmdFail = 31;

    static const int dirBar = 33;
    static const int timeBar = 36;

    /* OPTIONS */
    static const bool showTime = true;

    /* STRINGS */
    static const char nose[] = "\n^..^      /\n/_/\\_____/\n   /\\   /\\\n  /  \\ /  \\";

    /* NUMBERS */
    static const unsigned long maxDir = 260;

    /* ARRAYS */
    static const std::string alias[2][2] = {{"ls", "ls -CF --color=auto"},
                                            {"c", "clear"}};
}
#endif
