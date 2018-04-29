#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <regex>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <rapidjson/document.h>

std::vector<std::string> decompressGzipFileToVector(const std::string& gzipFilePath)
{
    std::ifstream file(gzipFilePath, std::ios_base::in | std::ios_base::binary);

    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    in.push(boost::iostreams::gzip_decompressor());
    in.push(file);

    std::stringstream ss;
    boost::iostreams::copy(in, ss);

    std::string line;
    std::vector<std::string> ret;
    while (std::getline(ss, line)) {
        ret.push_back(line);
    }

    return std::move(ret);
}

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

void replace(std::string& str, const std::string& from, const std::string& to)
{
    std::size_t pos = str.find(from);
    while (pos != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos = str.find(from);
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filePath>" << std::endl;
        return -1;
    }

    std::vector<std::string> lines = decompressGzipFileToVector(argv[1]);

    std::string britain;
    for (const std::string& str : lines) {
        rapidjson::Document document;
        document.Parse(str.c_str());

        if (std::string(document["title"].GetString()) == "イギリス") {
            britain =  document["text"].GetString();
            break;
        }
    }

    std::stringstream ss(britain);


    std::string line;
    std::map<std::string, std::string> fundMap;

    std::regex start(R"(.*基礎情報.*)");
    std::regex end(R"(^}}$)");
    std::regex keystart(R"(^\|.*)");
    std::regex bold(R"('{2,4}([^']*)'{2,4})");
    std::string key;

    bool flag = false;
    std::vector<std::string> values;
    while (std::getline(ss, line)) {
        if (flag == false && std::regex_match(line, start)) {
            flag = true;
            continue;
        }
        if (flag == true) {
            if (std::regex_match(line, end)) {
                if (!values.empty()) {
                    std::string val;
                    for (const std::string& str : values) {
                        val += str;
                    }
                    fundMap[key] = std::regex_replace(val, bold, "$1");
                    values.clear();
                }
                break;
            }

            if (std::regex_match(line, keystart)) {
                if (!values.empty()) {
                    std::string val;
                    for (const std::string& str : values) {
                        val += str;
                    }
                    fundMap[key] = std::regex_replace(val, bold, "$1");
                    values.clear();
                }

                std::vector<std::string> kv = split(line, '=');
                key = kv[0];
                for (std::size_t i = 1; i < kv.size(); ++i) {
                    values.push_back(kv[i]);
                }
            }
            else {
                values.push_back(line);
            }
        }
    }

    auto itr = fundMap.begin();
    while (itr != fundMap.end()) {
        std::cout << itr->first << " => " << itr->second << std::endl;
        ++itr;
    }

    return 0;
}
