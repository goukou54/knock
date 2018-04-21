#include <iostream>
#include <fstream>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <fileName> <num>" << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << "Failed to open file" << std::endl;
        return -1;
    }

    int cnt = std::atoi(argv[2]);

    int i = 0;
    std::string line;
    while (std::getline(ifs, line)) {
        if (i < cnt) {
            std::cout << line << std::endl;
            ++i;
        } else {
            break;
        }
    }

    return 0;
}
