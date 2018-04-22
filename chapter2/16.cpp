#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <fileName> <lineNum>" << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << "Failed to open file" << std::endl;
        return -1;
    }

    int lineNum = atoi(argv[2]);
    int cnt = 0;
    int fileNum = 0;
    std::ofstream ofs;
    std::string line;

    while (std::getline(ifs, line)) {
        if (cnt % lineNum == 0) {
            char buf[32];
            std::snprintf(buf, sizeof(buf), "file%d.txt", fileNum++);
            ofs.open(buf);
            ofs << line << std::endl;
        }
        else if (cnt % (lineNum) == (lineNum - 1)) {
            ofs << line << std::endl;
            ofs.close();
        }
        else {
            ofs << line << std::endl;
        }

        ++cnt;
    }

    return 0;
}
