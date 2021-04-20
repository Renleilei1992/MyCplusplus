
/* 右旋链表  https://leetcode-cn.com/problems/rotate-list/ */

#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0) return head;
        int count = 1;
        ListNode* tmp = head;
        // 找到尾巴结点并得到链表的结点数.
        while (tmp->next) {
            tmp = tmp->next;
            count++;
        }

        // 取模是为了避免重复多次循环整个链表, 即K远远大于count
        // 比如 count = 5, k = 12 的场景. 其实应该是 第2个结点和第3个结点处断开.
        k = count - (k % count);
        if (k == 0) return head;    // 当k等于0时不需要旋转.

        // 需要旋转时先将链表头尾连起来.
        ListNode* tail = tmp;
        tail->next = head;

        // 在合适的地方断开链表.
        ListNode* pNewHead = nullptr;
        for (int i = 0; i < k - 1; i++) {
            head = head->next;
        }
        pNewHead = head->next;
        head->next = nullptr;

        return pNewHead;
    }
};

void unitTest() {
    ListNode* arr = new ListNode[5]{};
    for (int i = 0; i < 5; i++) {
        arr[i].val = i + 1;
        if (i + 1 < 5) {
            arr[i].next = &arr[i+1];
        }
    }

    auto printArr = [=](ListNode A[], int length) -> void {
        for (int i = 0; i < length; i++) {
            std::cout << A[i].val << " ";
        }
        std::cout << std::endl;
    };

    auto printNext = [=](ListNode* head) -> void {
        while (head != nullptr) {
            std::cout << head->val << " ";
            head = head->next;
        }
        std::cout << std::endl;
    };
    
    std::cout << "原始数组为: " << std::endl;;
    printArr(arr, 5);
    std::cout << "右旋数组为: " << std::endl;;
    Solution obj;
    ListNode* pHead = obj.rotateRight(&arr[0], 12);
    printNext(pHead);
}

int main() {

    unitTest();
    return 0;
}