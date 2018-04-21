#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

std::string format(int x, const std::string& y, double z)
{
    char buf[30];
    std::snprintf(buf, sizeof(buf), "%d時の%sは%.1lf", x, y.c_str(), z);

    return std::string(buf);
}

int main()
{
    std::cout << format(12, "気温", 22.4) << std::endl;

    return 0;
}
