#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

std::vector<std::vector<std::string>> makeWordNgram(const std::string& str, std::size_t n)
{
    std::stringstream ss(str);

    std::string word;
    std::vector<std::string> wordList;
    while (std::getline(ss, word, ' ')) {
        wordList.push_back(word);
    }

    std::vector<std::vector<std::string>> ret;

    for (std::size_t i = 0; i < wordList.size() - n + 1; ++i) {

        std::vector<std::string> element;
        for (std::size_t j = i; j < i + n; ++j) {
            element.push_back(wordList[j]);
        }

        ret.push_back(element);
    }

    return ret;
}

void replace(std::string& str, std::string from, std::string to)
{
    std::size_t pos = str.find(from);
    while (pos != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
        pos = str.find(from);
    }
}

std::vector<std::vector<char>> makeCharNgram(const std::string& str, std::size_t n)
{
    std::string chars = str;
    replace(chars, " ", "");

    std::vector<std::vector<char>> ret;
    for (std::size_t i = 0; i < chars.length() - n + 1; ++i) {

        std::vector<char> elem;
        for (std::size_t j = i; j < i + n; ++j) {
            elem.push_back(chars[j]);
        }
        ret.push_back(elem);
    }

    return ret;
}

int main()
{
    std::string str = "I am an NLPer";

    auto wordBigram = makeWordNgram(str, 2);
    auto charBigram = makeCharNgram(str, 2);

    // Output
    std::cout << "Word bi-gram: ";
    for (std::size_t i = 0; i < wordBigram.size(); ++i) {
        std::cout << "{" << wordBigram[i][0] << ", " << wordBigram[i][1] << "}";
        if (i != (wordBigram.size() - 1)) {
            std::cout << ", ";
        } else {
            std::cout << std::endl;
        }
    }

    std::cout << "Char bi-gram: ";
    for (std::size_t i = 0; i < charBigram.size(); ++i) {
        std::cout << "{" << charBigram[i][0] << ", " << charBigram[i][1] << "}";
        if (i != (charBigram.size() - 1)) {
            std::cout << ", ";
        } else {
            std::cout << std::endl;
        }
    }

    return 0;
}
