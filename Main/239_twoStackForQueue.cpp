/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：239_twoStackForQueue.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年06月21日
*   描    述：两个栈实现一个队列. 剑指offer原题, 
*   版    本: Version 1.00
*   编译指令: g++ -o main 239_twoStackForQueue.cpp -std=c++11
*   参考链接: [LeetCode剑指offer原题自己的解答](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)
================================================================*/

#include <iostream>
#include <stack>

using namespace std;

class CQueque {
private:
	std::stack<int> stack_a;
	std::stack<int> stack_b;
public:
	CQueque() {}

	// like push (尾部插入)
	void appendTail(int value) {
		stack_a.push(value);
	}

	// like pop (头部删除)
	int deleteHead() {
		if (stack_b.empty()) {
			if (stack_a.empty()) {
				// 两个栈均为空, 代表整个队列为空, 返回 -1
				return -1;
			} else {
				// a栈非空, b栈为空, 将a栈中的数据保存到b栈中
				stack_b.push(stack_a.top());
				stack_a.pop();
			}
		}

		int ret = stack_b.top();
		stack_b.pop();
		return ret;
	}
};

int main()
{
	CQueque que;
	que.appendTail(10);
	que.appendTail(11);
	
	cout << "delete 1: " << que.deleteHead() << endl;
	cout << "delete 2: " << que.deleteHead() << endl;
	cout << "delete 3: " << que.deleteHead() << endl;
	return 0;
}
