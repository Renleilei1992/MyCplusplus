
/*
给定一个链表，删除链表的倒数第 nn 个节点并返回链表的头指针
例如，
给出的链表为: 1→2→3→4→5, n=2.
删除了链表的倒数第 n 个节点之后,链表变为1→2→3→5.

备注：
题目保证 n 一定是有效的
请给出请给出时间复杂度为 O(n) 的算法
*/

#include <iostream>
#include <stack>
using namespace std;


struct ListNode {
    int val;
    struct ListNode *next;
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == nullptr || head->next == nullptr) return nullptr;

        std::stack<ListNode*> nStack;
        int count = 0;
        ListNode* tmp = head;
        while (tmp) {       // 获取链表长度
            nStack.push(tmp);
            tmp = tmp->next;
            count++;
        }

        if (n > count) return head;
        if (n == count) {
            ListNode* headPtr = head->next;
            head->next = nullptr;
            return headPtr;
        }

        ListNode* tempPtr = nullptr;
        for (int i = count; i > 0; i--) {
            tempPtr = nStack.top();
            nStack.pop();
        }
        
        ListNode* ptr = nStack.top();
        ptr->next = tempPtr->next;
        tempPtr->next = nullptr;
        
        while (!nStack.empty()) {
            tempPtr = nStack.top();
            nStack.pop();
        }

        return tempPtr;
    }

};

int main() {
    return 0;
}