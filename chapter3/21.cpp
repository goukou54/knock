#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
    while (std::getline(ss, line)) {
        if (line.find("Category") != std::string::npos) {
            std::cout << line << std::endl;
        }
    }

    return 0;
}
