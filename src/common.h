#include <vector>

void debugPrint(std::string text, int colorcode, std::string stringEnd = "\n") {
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

void tokenize(std::string const &str, const char delim,
              std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}