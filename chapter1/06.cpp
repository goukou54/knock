#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <array>
#include <sstream>

std::set<std::vector<char>> makeCharNgramSet(const std::string& str, std::size_t n)
{
    std::string chars = str;
    std::set<std::vector<char>> ret;
    for (std::size_t i = 0; i < chars.length() - n + 1; ++i) {

        std::vector<char> elem;
        for (std::size_t j = i; j < i + n; ++j) {
            elem.push_back(chars[j]);
        }
        ret.insert(elem);
    }

    return ret;
}

int main()
{
    std::array<std::string, 2> strs = {"paraparaparadise", "paragraph"};

    std::set<std::vector<char>> X = makeCharNgramSet(strs[0], 2);
    std::set<std::vector<char>> Y = makeCharNgramSet(strs[1], 2);

    std::set<std::vector<char>> uni;
    std::set_union(X.begin(), X.end(), Y.begin(), Y.end(), std::inserter(uni, uni.end()));

    std::set<std::vector<char>> intersection;
    std::set_intersection(X.begin(), X.end(), Y.begin(), Y.end(), std::inserter(intersection, intersection.end()));

    std::set<std::vector<char>> diff;
    std::set_difference(X.begin(), X.end(), Y.begin(), Y.end(), std::inserter(diff, diff.end()));

    // Output
    std::cout << "X    : ";
    auto itr = X.begin();
    {
        while (itr != X.end()) {
            std::cout << "{" << (*itr)[0] << ", " << (*itr)[1] << "}";
            if (++itr != X.end()) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
    }

    std::cout << "Y    : ";
    {
        auto itr = Y.begin();
        while (itr != Y.end()) {
            std::cout << "{" << (*itr)[0] << ", " << (*itr)[1] << "}";
            if (++itr != Y.end()) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
    }

    std::cout << "X + Y: ";
    {
        auto itr = uni.begin();
        while (itr != uni.end()) {
            std::cout << "{" << (*itr)[0] << ", " << (*itr)[1] << "}";
            if (++itr != uni.end()) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
    }

    std::cout << "X * Y: ";
    {
        auto itr = intersection.begin();
        while (itr != intersection.end()) {
            std::cout << "{" << (*itr)[0] << ", " << (*itr)[1] << "}";
            if (++itr != intersection.end()) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
    }

    std::cout << "X - Y: ";
    {
        auto itr = diff.begin();
        while (itr != diff.end()) {
            std::cout << "{" << (*itr)[0] << ", " << (*itr)[1] << "}";
            if (++itr != diff.end()) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
    }

    std::vector<char> target = {'s', 'e'};
    {
        auto itr = X.find(target);
        if (itr != X.end()) {
            std::cout << "Found s,e in X" << std::endl;
        } else {
            std::cout << "NOT Found s,e in X" << std::endl;
        }
    }

    {
        auto itr = Y.find(target);
        if (itr != Y.end()) {
            std::cout << "Found s,e in Y" << std::endl;
        } else {
            std::cout << "NOT Found s,e in Y" << std::endl;
        }
    }

    return 0;
}
