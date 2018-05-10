#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>

class Morph
{
public:
    Morph(
        const std::string& surface
      , const std::string& base
      , const std::string& pos
      , const std::string& pos1
    )
    {
        this->surface = surface;
        this->base    = base;
        this->pos     = pos;
        this->pos1    = pos1;
    }

    const std::string toString() const
    {
        std::stringstream ss;
        ss << "surface=[" << this->surface << "],";
        ss << "base=["    << this->base    << "],";
        ss << "pos=["     << this->pos     << "],";
        ss << "pos1=["    << this->pos1    << "],";

        return ss.str();
    }

private:
    std::string surface;
    std::string base;
    std::string pos;
    std::string pos1;
};

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
    using Sentense     = std::vector<Morph>;
    using SentenseList = std::vector<Sentense>;

    std::ifstream ifs("neko.txt.cabocha");


    SentenseList sentenseList;
    Sentense sentense;
    std::string line;
    while (std::getline(ifs, line)) {
        if (line == "EOS") {
            if (sentense.empty() == false) {
                sentenseList.push_back(sentense);
                sentense.clear();
            }
            continue;
        } else if (line[0] == '*') {
            continue;
        }

        std::vector<std::string> result = split(line, '\t');
        std::vector<std::string> cols   = split(result[1], ',');

        sentense.push_back(Morph(result[0], cols[6], cols[0], cols[1]));
    }


    for (const Morph& m : sentenseList[2]) {
        std::cout << m.toString() << std::endl;
    }

    return 0;
}
