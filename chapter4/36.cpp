#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <array>
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

int main()
{
    using WordMap      = std::vector<std::pair<std::string, std::string>>;
    using WordCountMap = std::vector<std::pair<std::string, std::size_t>>;
    using Sentense     = std::vector<WordMap>;
    using SentenseList = std::vector<Sentense>;

    std::ifstream ifs("neko.txt.mecab");

    SentenseList sentenseList;

    std::string line;
    Sentense sentense;
    while (std::getline(ifs, line)) {
        if (line == "EOS") {
            if (sentense.empty() == false)  {
                sentenseList.push_back(sentense);
                sentense.clear();
            }
            continue;
        }

        std::vector<std::string> result = split(line, '\t');
        std::vector<std::string> cols   = split(result[1], ',');

        WordMap word =
        {
           {"surface", result[0]}
         , {"base", cols[6]}
         , {"pos",  cols[0]}
         , {"pos1", cols[1]}
        };

        sentense.push_back(word);
    }

    WordCountMap wordCountMap;
    for (const Sentense& sentense : sentenseList) {
        for (std::size_t i = 0; i < sentense.size(); ++i) {
            auto itr = wordCountMap.begin();
            while (itr != wordCountMap.end()) {
                if ((*itr).first == sentense[i][0].second) {
                    (*itr).second += 1;
                    break;
                }
                ++itr;
            }
            if (itr == wordCountMap.end()) {
                wordCountMap.push_back(std::make_pair(sentense[i][0].second, 1));
            }
        }
    }

    struct countComp {
        inline bool operator() (const std::pair<std::string, std::size_t>& lhs, const std::pair<std::string, std::size_t>& rhs)
        {
            return (lhs.second > rhs.second);
        }
    };

    std::sort(wordCountMap.begin(), wordCountMap.end(), countComp());

    for (const auto& pair : wordCountMap) {
        std::cout << pair.first << "," << pair.second << std::endl;
    }

    return 0;
}
