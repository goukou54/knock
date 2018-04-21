#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>

int main()
{
    std::ifstream col1("col1.txt");
    std::ifstream col2("col2.txt");

    std::ofstream merge("merge.txt");

    std::array<std::string, 2> line;
    while (std::getline(col1, line[0]) && std::getline(col2, line[1])) {
        merge << line[0] << '\t' << line[1] << std::endl;
    }

    return 0;
}
