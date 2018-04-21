#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

std::vector<std::string> split(const std::string& str, char delim)
{
    std::stringstream ss(str);

    std::vector<std::string> ret; 
    std::string buf;
    while (std::getline(ss, buf, delim)) {
        ret.push_back(buf);
    }

    return ret;
}

int main()
{
    std::ifstream ifs("hightemp.txt");

    std::ofstream col1("col1.txt");
    std::ofstream col2("col2.txt");

    std::string line;
    while (std::getline(ifs, line)) {
        std::vector<std::string> cols = split(line, '\t');
        col1 << cols[0] << std::endl;
        col2 << cols[1] << std::endl;
    }

    return 0;
}
