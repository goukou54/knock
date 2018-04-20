#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>

int main()
{
    std::stringstream ss("Hi He Lied Because Boron Could Not Oxidize Fluorine. New Nations Might Also Sign Peace Security Clause. Arthur King Can.");

    std::map<std::string, std::size_t> wordIndex;
    std::size_t index = 1;

    std::string word;
    while (ss >> word) {
        switch (index) {
            case 1:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 15:
            case 16:
            case 19: {
                wordIndex[word.substr(0, 1)] = index;
                break;
            }
            default: {
                wordIndex[word.substr(0, 2)] = index;
                break;
            }
        }
        ++index;
    }

    // Output
    auto itr = wordIndex.begin();
    while (itr != wordIndex.end()) {
        std::cout << std::left << std::setw(2) << itr->first << " => " << itr->second << std::endl;
        ++itr;
    }

    return 0;
}
