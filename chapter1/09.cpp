#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <sentense>" << std::endl;
        return -1;
    }

    std::stringstream ss(argv[1]);
    std::string word;

    while (ss >> word) {
        if (word.length() <= 4) {
            std::cout << word << " ";
        }
        else {
            std::vector<char> characters(word.begin() + 1, word.end() - 1);

            std::random_device seed_gen;
            std::mt19937 engine(seed_gen());
            std::shuffle(characters.begin(), characters.end(), engine);

            std::cout << word[0];
            for (char c : characters) {
                std::cout << c;
            }
            std::cout << word[word.length()-1] << " ";
        }
    }

    std::cout << std::endl;

    return 0;
}
