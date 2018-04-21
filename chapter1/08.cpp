#include <iostream>
#include <cstdio>

void cipher(const std::string& input)
{
    for (std::size_t i = 0; i < input.length(); ++i) {
        if (0x61 <= input[i] && input[i] <= 0x7a) {
            std::fprintf(stdout, "%c", 219 - input[i]);
        } else {
            std::fprintf(stdout, "%c", input[i]);
        }
    }

    std::cout << std::endl;
}

int main()
{
    cipher("Yes We Can.");
    cipher("Yvh Wv Czm.");

    return 0;
}
