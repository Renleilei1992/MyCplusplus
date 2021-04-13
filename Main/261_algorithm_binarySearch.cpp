

/*
请实现有重复数字的升序数组的二分查找
给定一个 元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1
*/

#include <vector>
#include <iostream>

using namespace std;

static int count = 0;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 如果目标值存在返回下标，否则返回 -1
     * @param nums int整型vector 
     * @param target int整型 
     * @return int整型
     */
    int search(vector<int>& nums, int target) {
        // write code here
        return partition(nums, 0, nums.size() - 1, target);
    }
    
    int partition(vector<int>& nums, int start, int end, const int target) {
        int middle1 = (start + end) / 2;
        std::cout << __func__ << "::[1] be called! start: " << start << " end: " << end << " middle: " << middle1 << " nums[middle]: " << nums[middle1] << std::endl;
        if (count > 20) {
            return -1;
        }
        count++;
        
        if (start > end || nums[start] > target || nums[end] < target) {
            return -1;    // 边界检查, 避免死循环.
        }
        if (nums[start] == target) {
            return start;    // 检查区间的左侧是否为目标值.
        }
        
        // 二分
        int middle = (start + end) / 2;
        std::cout << __func__ << "::[2] middle: " << middle << " nums[middle]=" << nums[middle] << std::endl;

        if (nums[middle] < target) {
            // 直接向右找
            return partition(nums, middle + 1, end, target);
        }

        // 当发现中值比 target 大时往左找
        return partition(nums, start, middle, target);
    }
};

int main() {

    Solution obj;
    std::vector<int> vec1{1,2,2,4,5,6,8,10,20,20,88,189};
    std::vector<int> vec2{1,4,4,4,5};
    std::vector<int> vec3{1,1,2,3,7,7,7,9,9,10};
    int target = 2;
    int result = obj.search(vec3, target);
    std::cout << "result is: " << result << std::endl;

    return 0;
}