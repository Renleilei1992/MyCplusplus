
/*
题目描述
给出一个整数数组，请在数组中找出两个加起来等于目标值的数，
你给出的函数twoSum 需要返回这两个数字的下标（index1，index2），需要满足 index1 小于index2.。注意：下标是从1开始的
假设给出的数组中只存在唯一解
例如：
给出的数组为 {20, 70, 110, 150},目标值为90
输出 index1=1, index2=2


示例1
输入
复制
[3,2,4],6
返回值
复制
[2,3]
*/

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {

public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        unordered_map<int, int> u_map;
        for (int i = 0; i < numbers.size(); i++) {
            auto it = u_map.find(target - numbers[i]);
            if (it != u_map.end()) {
                return vector<int>{ it->second, i+1};
            }

            u_map[numbers[i]] = i + 1;
        }
        return vector<int>();        
    }

};

int main()
{
    Solution obj;

    vector<int> vec{2,4,5,7,10};
    int targetNum = 12;

    vector<int> resultVec = obj.twoSum(vec, targetNum);
    std::cout << "结果: ";
    for (auto iVec : resultVec) {
        std::cout << iVec << " ";
    }
    std::cout << std::endl;
    
    return 0;
}