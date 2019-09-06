#include <iostream>
#include <vector>

using namespace std;

// 简单工厂模式


void mergeArr(int arr1[], int n, int arr2[], int k);

int main()
{
    cout << "Hello World!" << endl;

    int arr1[5] = {1, 2, 2, 4, 5};
    int arr2[6] = {3, 4, 4, 7, 8, 9};
    mergeArr(arr1, 5, arr2, 6);
    return 0;
}

// 给定有序数组 int arr1[], 长度n
// 给定有序数组 int arr2[], 长度k
// 合并为一个有序数组,并避免元素重复

// 初步答案
void mergeArr(int arr1[], int n, int arr2[], int k)
{
    std::vector<int> vec;
    int idx1 = 0;
    int idx2 = 0;

    do
    {
        if (arr1[idx1] < arr2[idx2])
        {
            vec.push_back(arr1[idx1]);
            idx1++;
        } else if (arr1[idx1] == arr2[idx2])
        {
            vec.push_back(arr1[idx1]);
            idx1++;
            idx2++;
        } else {
            vec.push_back(arr2[idx2]);
            idx2++;
        }
        
        
    } while (idx1 < n && idx2 < k);

    if ( n == idx1 )
    {
        // 证明arr1已经结束
        for (int i = idx2; i < k; ++i)
        {
            vec.push_back(arr2[idx2]);
        }
    }

    if ( k == idx2 )
    {
        // 证明arr1已经结束
        for (int i = idx1; i < n; ++i)
        {
            vec.push_back(arr1[idx1]);
        }
    }

    // 结束后打印结果
    for (auto iVec : vec) {
        cout << iVec << " ";
    }
    cout << endl;
    
}