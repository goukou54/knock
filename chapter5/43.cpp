#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>

class Morph {
public:
    Morph(
        const std::string& i_surface
      , const std::string& i_base
      , const std::string& i_pos
      , const std::string& i_pos1
    )
      : surface(i_surface)
      , base(i_base)
      , pos(i_pos)
      , pos1(i_pos1)
    {
    }

    const std::string& getSurface() const
    {
        return this->surface;
    }

    const std::string& getPos() const
    {
        return this->pos;
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

class Chunk {
public:
    Chunk(const std::vector<Morph>& i_morphs, int i_dst)
        : morphs(i_morphs)
        , dst(i_dst)
        , srcs()
    {
    }

    void addSrc(int src)
    {
        this->srcs.push_back(src);
    }

    int getDst() const
    {
        return this->dst;
    }

    int getVecVal() const
    {
        return this->srcs[0];
    }

    const std::vector<Morph>& getMorphs() const
    {
        return this->morphs;
    }

    bool hasNoun() const
    {
        for (const Morph& morph : this->morphs) {
            if (morph.getPos() == "名詞") {
                return true;
            }
        }
        return false;
    }

    bool hasVerb() const
    {
        for (const Morph& morph : this->morphs) {
            if (morph.getPos() == "動詞") {
                return true;
            }
        }
        return false;
    }

    const std::string toString() const
    {
        std::stringstream ss;
        ss << "Dst=[" << this->dst << "],";
        ss << "Srcs=[";
        for (std::size_t i = 0; i < this->srcs.size(); ++i) {
            ss << this->srcs[i];
            if (i != (this->srcs.size() - 1)) {
                ss << ",";
            }
        }
        ss << "]" << std::endl;

        for (const Morph& m : this->morphs) {
            ss << m.toString() << std::endl;
        }

        return ss.str();
    }

private:
    std::vector<Morph> morphs;
    int dst;
    std::vector<int> srcs;
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
    using Sentense     = std::vector<Chunk>;
    using SentenseList = std::vector<Sentense>;

    std::ifstream ifs("neko.txt.cabocha");

    SentenseList sentenses;
    Sentense chunks;
    std::string line;
    std::vector<int> dstList;

    std::vector<Morph> morphs;
    int dst = 0;
    while (std::getline(ifs, line)) {
        if (line == "EOS") {
            if (morphs.empty() == false) {
                chunks.push_back(Chunk(morphs, dst));
                morphs.clear();

                sentenses.push_back(chunks);
                chunks.clear();
            }
        } else if (line[0] == '*') {
            if (morphs.empty() == false) {
                chunks.push_back(Chunk(morphs, dst));
                morphs.clear();
            }

            std::vector<std::string> result = split(line, ' ');
            std::string dstStr = result[2];
            dstStr.replace(dstStr.find('D'), 1, "");
            dst = std::stoi(dstStr);
        } else {
            std::vector<std::string> result = split(line, '\t');
            std::vector<std::string> cols   = split(result[1], ',');

            morphs.push_back(Morph(result[0], cols[6], cols[0], cols[1]));
        }
    }

    for (Sentense& sentense : sentenses) {
        for (std::size_t i = 0; i < sentense.size(); ++i) {
            int index = sentense[i].getDst();
            if (0 <= index) {
                sentense[index].addSrc(i);
            }
        }
    }

    for (const Sentense& sentense : sentenses) {
        for (const Chunk& chunk : sentense) {
            if (0 <= chunk.getDst()
             && chunk.hasNoun()
             && sentense[chunk.getDst()].hasVerb()
            ) {
                for (const Morph& morph : chunk.getMorphs()) {
                    if (morph.getPos() != "記号") {
                        std::cout << morph.getSurface();
                    }
                }
                std::cout << '\t';

                for (const Morph& morph : sentense[chunk.getDst()].getMorphs()) {
                    if (morph.getPos() != "記号") {
                        std::cout << morph.getSurface();
                    }
                }
                std::cout << std::endl;
            }
        }
    }

    return 0;
}
