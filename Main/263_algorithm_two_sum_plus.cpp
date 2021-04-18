

/* 有序列表 vec1 vec2, 找出和为 N 的数字对 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

#define LOG(...)                                                     \
do {                                                                 \
  std::cerr << red << "(" << __LINE__ << ")" << ""#__VA_ARGS__" = "; \
  _debug(__VA_ARGS__);                                               \
  std::cerr << white;                                                \
} while (false)                                                      \

class Solution {
public:
    /**
     * 
     * @param v1 std::vector
     * @param v2 std::vector
     * @param target 目标和
     * @return std::vector
     */
    std::vector<std::pair<int, int>> twoSumPlus(std::vector<int>& vec1, std::vector<int>& vec2, int target) {
        // std::cout << __func__ << "::[1] be called!" << std::endl;
        std::unordered_map<int, int> u_map;
        std::vector<std::pair<int, int>> retVec;
        for (int i = 0; i < vec1.size(); i++) {
            u_map[vec1[i]] = i;
        }

        for (auto iVec : vec2) {
            auto it = u_map.find(target - iVec);
            if (it != u_map.end()) {
                retVec.emplace_back(std::pair<int, int>(it->first, iVec));
            }
        }
        
        return retVec;
    }
};

int main() {

    std::vector<int> vec1{2, 3, 5, 7, 9, 11};
    std::vector<int> vec2{1, 4, 6, 8, 13, 10};
    int target = 15;
    Solution obj;
    std::vector<std::pair<int, int>> retVec = obj.twoSumPlus(vec1, vec2, target);
    for (auto iVec : retVec) {
        std::cout << iVec.first << " + " << iVec.second << " = " << target << std::endl;
    }
    
    return 0;
}