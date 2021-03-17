#ifndef NOSESHELL_COMMON_H
#define NOSESHELL_COMMON_H

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
void debugPrint(std::string text, int colorcode, std::string stringEnd = "\n");
void returnPrint(int cmdRet, std::string text);
void refreshConsoleInfo(int& w, int& h);
std::string colorFromCode(int code);
std::string getDir();
std::string getTime();

#endif
