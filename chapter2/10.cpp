#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>

int main()
{
    std::ifstream ifs("hightemp.txt");

    std::size_t cnt = 0;
    std::string line;
    while (std::getline(ifs, line)) {
        ++cnt;
    }

    // Output
    std::cout << "LineCount=" << cnt << std::endl;

    return 0;
}
