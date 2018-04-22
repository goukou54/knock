#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>

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
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }

    std::vector<std::string> cols;
    std::string line;
    while (std::getline(ifs, line)) {
        cols.push_back(line);
    }

    struct strCompare {
        inline bool operator() (const std::string& lhs, const std::string& rhs) {
            std::vector<std::string> lhscols = split(rhs, '\t');
            std::vector<std::string> rhscols = split(lhs, '\t');

            double lhsVal = std::stod(lhscols[2]);
            double rhsVal = std::stod(rhscols[2]);

            return (lhsVal > rhsVal);
        }
    };

    std::sort(cols.begin(), cols.end(), strCompare());

    // Output
    for (const auto& col : cols) {
        std::cout << col << std::endl;
    }

    return 0;
}
