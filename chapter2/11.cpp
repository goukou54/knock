#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>

void replace(std::string& str, const std::string& from, const std::string& to)
{
    std::size_t pos = str.find(from);
    while (pos != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos = str.find(from);
    }
}

int main()
{
    std::ifstream ifs("hightemp.txt");

    std::size_t cnt = 0;
    std::string line;
    while (std::getline(ifs, line)) {
        replace(line, "\t", " "); 
        std::cout << line << std::endl;
    }

    return 0;
}
