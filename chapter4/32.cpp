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

    // Output
    for (const Sentense& sentense : sentenseList) {
        for (const WordMap& wordMap : sentense) {
            if (wordMap[2].second == "動詞") {
                std::cout << wordMap[1].second << std::endl;
            }
        }
    }
    return 0;
}