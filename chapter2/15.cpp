#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

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

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(ifs, line)) {
        lines.push_back(line);
    }
    
    for (int i = lines.size() - cnt; i < lines.size(); ++i) {
        std::cout << lines[i] << std::endl;
    }

    return 0;
}
