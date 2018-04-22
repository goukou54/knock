#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

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

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <fileName>" << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << "Failed to open file" << std::endl;
        return -1;
    }

    std::vector<std::string> words;
    std::string line;
    while (std::getline(ifs, line)) {
        std::vector<std::string> cols = split(line, '\t');
        words.push_back(cols[0]);
    }

    std::sort(words.begin(), words.end());
    auto result = std::unique(words.begin(), words.end());
    auto itr = words.begin();
    while (itr != result) {
        std::cout << *itr << std::endl;
        ++itr;
    }
#if 0
    for (auto itr = words.begin(); itr != std::unique(words.begin(), words.end()); ++itr) {
        std::cout << *itr << std::endl;
    }
#endif

    return 0;
}
