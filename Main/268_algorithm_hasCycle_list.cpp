

/* 判断链表是否有环  https://www.nowcoder.com/practice/650474f313294468a4ded3ce0f7898b9 */

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
    bool hasCycle(ListNode *head) {
        // 快慢指针判断是否有环
        if (head == nullptr || head->next == nullptr) return false;

        bool bHasCycle = false;
        ListNode* slowPtr = head;
        ListNode* fastPtr = head;
        while (fastPtr && fastPtr->next) {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
            if (slowPtr == fastPtr) {
                bHasCycle = true;
                break;
            }
        }

        // 找到环的起点
        ListNode* entryNode = nullptr;
        if (bHasCycle) {
            ListNode* slowPtr2 = head;
            while (slowPtr != slowPtr2) {
                slowPtr = slowPtr->next;
                slowPtr2 = slowPtr2->next;
            }
            entryNode = slowPtr;
        }
        
        return bHasCycle;
    }
};

static const auto io_sync_off=[](){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {

    return 0;
}