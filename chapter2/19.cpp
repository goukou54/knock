#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

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

    std::vector<std::string> words;
    std::string line;
    while (std::getline(ifs, line)) {
        words.push_back(split(line, '\t')[0]);
    }

    std::map<std::string, std::size_t> wordCountMap;
    for (const auto& word : words) {
        auto itr = wordCountMap.find(word);
        if (itr == wordCountMap.end()) {
            wordCountMap[word] = 1;
        } else {
            wordCountMap[word] = wordCountMap[word] + 1;
        }
    }

    std::vector<std::pair<std::string, std::size_t>> wordCountVector;
    auto itr = wordCountMap.begin();
    while (itr != wordCountMap.end()) {
        wordCountVector.push_back(*itr);
        ++itr;
    }

    struct countCmp {
        inline bool operator() (const std::pair<std::string, std::size_t>& lhs, const std::pair<std::string, std::size_t>& rhs)
        {
            return (lhs.second > rhs.second);
        }
    };

    std::sort(wordCountVector.begin(), wordCountVector.end(), countCmp());

    // Output
    for (const auto& pair : wordCountVector) {
        std::cout << pair.first << " => " << pair.second << std::endl;
    }

    return 0;
}
