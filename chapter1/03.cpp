#include <iostream>
#include <sstream>
#include <vector>

void replace(std::string& str, const std::string& from, const std::string& to)
{
    std::size_t pos = str.find(from);
    while (pos != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos = str.find(from);
    }
}

int main()
{
    std::string str = "Now I need a drink, alcoholic of course, after the heavy lectures involving quantum mechanics.";

    replace(str, ",", "");
    replace(str, ".", "");

    std::stringstream ss(str);

    std::string word;
    std::vector<std::size_t> sizeList;
    while (ss >> word) {
        sizeList.push_back(word.length());
    }

    // Output
    for (std::size_t len : sizeList) {
        std::cout << len << " ";
    }
    std::cout << std::endl;

    return 0;
}
