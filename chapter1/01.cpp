#include <iostream>
#include <cstdint>

std::string getUTF8Char(const std::string& str, std::size_t index)
{
    std::size_t pos = 0;
    std::size_t cnt = 0;
    std::string ret;

    while (pos < str.size()) {
        uint8_t head = str[pos];

        // 1 byte
        if (head <= 0x7f) {
            if (index == cnt) {
                ret += head;
                return ret;
            } else {
                pos += 1;
                ++cnt;
            }
        }
        // 2 byte
        else if (0xc2 <= head && head <=0xdf) {
            if (index == cnt) {
                ret += head;
                ret += str[pos+1];
                return ret;
            } else {
                pos += 2;
                ++cnt;
            }
        }
        // 3 byte
        else if (0xe0 <= head && head <=0xef) {
            if (index == cnt) {
                ret += head;
                ret += str[pos+1];
                ret += str[pos+2];
                return ret;
            } else {
                pos += 3;
                ++cnt;
            }
        }

        // 4 byte
        else if (0xf0 <= head && head <=0xf7) {
            if (index == cnt) {
                ret += head;
                ret += str[pos+1];
                ret += str[pos+2];
                ret += str[pos+3];
                return ret;
            } else {
                pos += 4;
                ++cnt;
            }
        }
    }

    return "Error";
}

int main()
{
    std::string str = "パタトクカシー";

    std::string catStr;
    catStr += getUTF8Char(str, 0);
    catStr += getUTF8Char(str, 2);
    catStr += getUTF8Char(str, 4);
    catStr += getUTF8Char(str, 6);

    std::cout << catStr << std::endl;

    return 0;
}
