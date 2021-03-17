#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h>
#include <unistd.h>
#include <algorithm>

#include "common.h"

#define Max_Len 1024

void debugPrint(std::string text, int colorcode, std::string stringEnd) {
    std::cout << "\x1B[" << colorcode << "m" << text << "\033[0m" << stringEnd;
}

void returnPrint(int cmdRet, std::string text){
    int colorcode = 32;
    if (cmdRet != 0)
        colorcode = 31;
    std::cout << "\x1B[" << colorcode << "m" << text << "\033[0m";
}


void errorPrint(std::string text, int colorcode, int exitCode){
    debugPrint(text, colorcode);
    std::cout << "\x1B[33m";
    system("pause");
    std::cout << "\033[0m";
    exit(exitCode);
}

void refreshConsoleInfo(int& w, int& h){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

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

std::wstring ExePath() {
    TCHAR buffer[1024] = { 0 };
    GetModuleFileName( NULL, buffer, 1024 );
    std::wstring::size_type pos = std::wstring(reinterpret_cast<const wchar_t *>(buffer)).find_last_of(L"\\/");
    return std::wstring(reinterpret_cast<const wchar_t *>(buffer)).substr(0, pos);
}

std::string getDir() {
    const unsigned long maxDir = 260;
    char currentDir[maxDir];
    GetCurrentDirectory(maxDir, currentDir);
    return std::string(currentDir);
}

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out) {
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

bool in_array(const std::string &value, const std::vector<std::string> &array) {
    return std::find(array.begin(), array.end(), value) != array.end();
}