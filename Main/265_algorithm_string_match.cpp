
/* 从源字符串中匹配子字符串，并给出起始位置 */

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// #define _USE_BRUTE_
#define _USE_KMP_

// 算是暴力匹配，复杂度是 O(n*m)
void bruteMatch(const char* src, const char* pat, std::vector<int>& ansVec) {
    int N = strlen(src);
    int M = strlen(pat);

    if (M == 0 || N < M) return;
    
    int i = 0, j = 0;
    while (i <= N - M) {
        j = 0;
        while (j < M && src[i] == pat[j]) {     // 一个字符一个字符的匹配
            i++; j++;
        }
        
        if (j == M) {                   // 匹配的子字符串长度一致, 表明找到了子字符串.
            ansVec.push_back(i - M);
        }
        i = i - j + 1;                  // i回到匹配开始的下一个位置
    }
}

void kmp_match(const std::string& src, const std::string& pat, vector<int>& ansVec) {
    std::cout << __func__ << "---------> be called!" << std::endl;
    auto getNext = [](const std::string& pat, vector<int>& nextVec) -> void {
        int i = 0, j = -1;
        int pLen = pat.length();
        nextVec[0] = -1;
        while (i < pLen) {
            if (j == -1 || pat[i] == pat[j]) {
                i++; j++;
                // if (pat[i] != pat[j]) {
                //     nextVec[i] = j;
                //     std::cout << "[2] pat[" << i << "] = " << pat[i] << " pat[" << j << "] = " << pat[j] << " nextVec[" << i << "] = " << nextVec[i] << std::endl;
                // } else {
                //     nextVec[i] = nextVec[j];
                //     std::cout << "[3] pat[" << i << "] = " << pat[i] << " pat[" << j << "] = " << pat[j] << " nextVec[" << i << "] = " << nextVec[i] << std::endl;
                // }
                nextVec[i] = j;
                std::cout << "[4] pat[" << i << "] = " << pat[i] << " pat[" << j << "] = " << pat[j] << " nextVec[" << i << "] = " << nextVec[i] << std::endl;
            } else {
                // j = nextVec[j];
                j--;
            }
        }
    };

    auto printVec = [=](const std::vector<int>& vec) -> void {
        for (auto iVec : vec) {
            std::cout << " " << iVec;
        }
        std::cout << std::endl;
    };

    // std::vector<int> nextVec;
    // nextVec.resize(src.length() + 2);
    // std::fill(nextVec.begin(), nextVec.end(), 0);
    // getNext(src, nextVec);
    // std::cout << "[5] nextVec content is:";
    // for (auto iVec : nextVec) {
    //     std::cout << " " << iVec;
    // }
    // std::cout << std::endl;
    
    // 开始 KMP
    int i = -1, j = -1;
    int len1 = src.length();
    int len2 = pat.length();
    vector<int> next(len2+2, 0);
    getNext(pat, next);
    printVec(next);
    while (i < len1) {
        if (j == -1 || src[i] == pat[j]) {
            i++; j++;
            if (j == len2) {
                ansVec.push_back(i - len2);
            }
        } else {
            j = next[j];
        }
    }
}

void unittest() {
    auto printFunc = [=](const std::vector<int>& vec) -> void {
        for (auto iVec : vec) {
            std::cout << " " << iVec;
        }
        std::cout << std::endl;
    };

    std::vector<int> retVec;
    std::string srcStr = "Hello World! Hello C++!";
    std::string patStr1 = "World";
    std::string patStr2 = "Hello";
    std::string srcStr1 = "abababca";
    std::string patStr3 = "ababca";


#ifdef _USE_BRUTE_
    std::cout << "Origin String is: [" << srcStr << "]" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "[1] find child string: [" << patStr1 << "]" << std::endl;
    retVec.clear();
    bruteMatch(srcStr.c_str(), patStr1.c_str(), retVec);
    std::cout << "[1] find result: " << retVec.size() << std::endl;
    printFunc(retVec);
    

    std::cout << "-----------------" << std::endl;
    std::cout << "[2] find child string: [" << patStr2 << "]" << std::endl;
    retVec.clear();
    bruteMatch(srcStr.c_str(), patStr2.c_str(), retVec);
    std::cout << "[2] find result: " << retVec.size() << std::endl;
    printFunc(retVec);
#endif
#ifdef _USE_KMP_
    kmp_match(srcStr1, patStr3, retVec);
    printFunc(retVec);
#endif
}

int main() {

    unittest();
    return 0;
}