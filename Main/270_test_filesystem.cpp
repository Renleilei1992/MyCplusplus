
/* 编译指令: g++ -o main 270_test_filesystem.cpp -std=c++17 -lstdc++fs */

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main()
{
    std::string path = "/root/Repo/MyCplusplus/Main";
    std::filesystem::path fsPath = std::filesystem::path(path);
    std::cout << "[1]: fs: " << fsPath.u8string() << std::endl;

    for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;

    return 0;
}