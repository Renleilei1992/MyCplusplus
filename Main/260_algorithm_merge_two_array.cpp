
/*
给出两个有序的整数数组 和 ，请将数组 A 合并到数组 B 中，变成一个有序的数组
注意：
可以假设 A 数组有足够的空间存放 B 数组的元素，A 和  B 中初始的元素数目分别为 m 和 n 
*/

#include <iostream>
#include <array>
using namespace std;

class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        // 需要从末端开始往前
        int indexA = m - 1;
        int indexB = n - 1;
        int count = m + n - 1;
        
        while (indexA >= 0 && indexB >= 0) {
            if (A[indexA] < B[indexB]) {
                A[count] = B[indexB];
                indexB--;
            } else if (A[indexA] == B[indexB]) {
                A[count] = A[indexA];
                count--;
                A[count] = B[indexB];
                indexA--;
                indexB--;
            } else {    // A[indexA > B[indexB]
                A[count] = A[indexA];
                indexA--;
            }
            count--;
        }
        
        // 处理未合并完成的数组.直接追加到头部
        if (indexA < 0 && indexB >= 0 && count >= 0) { // A数组已合并完成, B数组未合并完成.
            for (int j = indexB; j >= 0; j--) {
                A[count] = B[j];
                count--;
            }
        }
        
        if (indexB < 0 && indexA >= 0 && count >= 0) { // B数组已合并完成, A数组未合并完成
            for (int j = indexA; j >= 0; j--) {
                A[count] = A[j];
                count--;
            }
        }
    }

    //归并排序的思想，只不过这里按照题目的意思不要申请额外的空间。
    //把A后面剩余的空间当额外空间。
    //这里和剑指offer上的面试题5，替换空格思想一样，从后面开始往前放就可以避免大量移动
    //那后面从哪里开始呢？A长m，B长n，两个合并完之后必定长m+n，所在A的A[m+n-1]开始往前放
    void merge_2(int A[], int m, int B[], int n){
        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;
        while (i >= 0 && j >= 0) {
            if (A[i] > B[j]) {
                A[k--] = A[i--];
            } else {
                A[k--] = B[j--];
            }
        }

        while (i >= 0) {
            A[k--] = A[i--];
        }
        while (j >= 0) {
            A[k--] = B[j--];
        }
    }
};

int main() {

    int arrA[7] = {1,4,7,0,0,0,0};
    int arrB[4] = {2,3,5,6};

    Solution obj;
    obj.merge_2(arrA, 3, arrB, 4);

    // 打印结果
    std::cout << "结果是: ";
    for (int i = 0; i < 7; i++)
    {
        std::cout << " " << arrA[i];
    }
    std::cout << std::endl;
    

    return 0;
}