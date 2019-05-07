/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：120_binary_tree.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月07日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// 节点的结构体
struct Node {
	int value;
	Node *left;
	Node *right;
	Node(int value):value(value),left(nullptr),right(nullptr){}
};

// 构建二叉树
void insertNode(Node *node, int value)
{
	if(node == nullptr) { return; }
	if(value <= node->value) {				// 此处的判断条件是节点的值若小于根节点则插入到左侧反之则插入到右侧
		if(!node->left) {
			node->left = new Node(value);
		} else {
			insertNode(node->left, value);	// 递归添加到node的left节点后	
		}
	} else {
		if(!node->right){
			node->right = new Node(value);
		} else {
			insertNode(node->right, value); // 递归添加到node的right节点后
		}
	}
}

// 前序遍历的特点: 先根节点，同级先左后右
// 前序遍历递归实现
void preOrder(Node *node)
{
	if(node) {
		cout << node->value << " ";
		preOrder(node->left);
		preOrder(node->right);
	}
}

// 前序遍历非递归实现
void preOrder_01(Node *node)
{
	if (nullptr == node) { return; }

	std::stack<Node *> nStack;
	nStack.push(node);
	while(!nStack.empty()) {
		Node *tmp = nStack.top();
		cout << tmp->value << " ";
		nStack.pop();

		if(tmp->right) {
			nStack.push(tmp->right);
		}

		if(tmp->left) {
			nStack.push(tmp->left);
		}
	}
}

// 中序遍历的特点: 先左后根再右
// 中序遍历的递归实现
void inOrder(Node *node)
{
	if (node) {
		inOrder(node->left);
		cout << node->value << " ";
		inOrder(node->right);
	}
}

// 中序遍历的非递归实现
void inOrder_01(Node *node)
{
	if (nullptr == node) { return; }
	std::stack<Node *> nStack;
	Node* tmp = node;
	while(tmp || !nStack.empty()) {
		if (tmp) {
			nStack.push(tmp);
			tmp = tmp->left;
		} else {
			tmp = nStack.top();
			cout << tmp->value << " ";
			nStack.pop();
			tmp = tmp->right;
		}
	}
}

// 后序遍历的特点: 先左后右再根
// 后序遍历的递归实现
void posOrder(Node *node)
{
	if (node) {
		posOrder(node->left);
		posOrder(node->right);
		cout << node->value << " ";
	}
}

// 后序遍历的非递归实现
void posOrder_01(Node *node)
{
	if (nullptr == node) { return; }
	std::stack<Node *> nStack1, nStack2;
	nStack1.push(node);

	while(!nStack1.empty()) {
		Node *tmp = nStack1.top();
		nStack1.pop();
		nStack2.push(tmp);
		if(tmp->left) {
			nStack1.push(tmp->left);
		}

		if(tmp->right) {
			nStack1.push(tmp->right);
		}
	}

	while(!nStack2.empty()) {
		cout << nStack2.top()->value << " ";
		nStack2.pop();
	}
}

//广度优先遍历
void broadOrder(Node *node){
    if(!node){
        return;
    }
    std::queue<Node *> qnodes;
    qnodes.push(node);
    while(!qnodes.empty()){
        Node * temp=qnodes.front();
        std::cout<<temp->value;
        qnodes.pop();
        if(temp->left){
            qnodes.push(temp->left);
        }
        if(temp->right){
            qnodes.push(temp->right);
        }

    }
}

int main(){
    int n;
    while(std::cin>>n){
        n--;
        int value;
        std::cin>>value;
        Node root(value);
        while(n--){
            int newValue;
            std::cin>>newValue;
            insertNode(&root,newValue);
        }
        std::cout<<"preOrder is:";
        preOrder(&root);
        std::cout<<std::endl;
        std::cout<<"inOrder is:";
        inOrder(&root);
        std::cout<<std::endl;
        std::cout<<"PosOrder is:";
        posOrder(&root);
        std::cout<<std::endl;
        std::cout<<"PreOrder without recursion is:";
        preOrder_01(&root);
        std::cout<<std::endl;
        std::cout<<"inOrder without recursion is:";
        inOrder_01(&root);
        std::cout<<std::endl;
        std::cout<<"PosOrder without recursion is:";
        posOrder_01(&root);
        std::cout<<std::endl;
        std::cout<<"BroadOrder is:";
        broadOrder(&root);
    }

}
