#ifndef NOSESHELL_COMMON_H
#define NOSESHELL_COMMON_H

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
bool in_array(const std::string &value, const std::vector<std::string> &array);
void debugPrint(std::string text, int colorcode, std::string stringEnd = "\n");
void returnPrint(int cmdRet, std::string text);
void refreshConsoleInfo(int& w, int& h);
std::string getDir();
std::string getTime();

#endif
