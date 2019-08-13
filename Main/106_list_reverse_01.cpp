/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：106_list_reverse_01.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年04月26日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

// 节点结构体
struct Node {
	int data;
	Node* next;
	Node(const int& d):data(d),next(NULL){}
};

class List {

public:
	List() { create_list(); }
	~List() { clear(); }

	void create_list();					// 创建头节点
	void insert(const int& d);			// 插入
	void insert_pos(const int& d, const int& d1);	//在指定位置插入
	void erase(const int& d);			// 删除指定数据的节点??
	void update(const int& d, const int& d1);		//修改指定数据
	void reverse_01();						// 反转链表函数
	void reverse_02();						// 反转链表函数
	Node* reverse_03(Node* head);			// 反转链表函数
	void print();						// 打印

public:

	Node* m_head;	// 头节点

private:

	// 清理链表
	void clear() {
		Node *p = m_head;
		// 从头节点开始循环删除
		while(p){
			Node *q = p->next;
			delete p;
			p = q;
		}
	}

	// 查找数据d的上一个节点位置 ,为了后续删除
	Node* find(const int& d) {
		Node *p = m_head;
		for(;p;p=p->next) {
			if(p->next->data == d)
				break;
		}
		return p;
	}
};

// 创建头节点
void List::create_list()
{
	m_head = new Node(0);
}

// 从头插入一个节点
void List::insert(const int &d)
{
	Node *p = new Node(d);
	p->next = m_head->next;
	m_head->next = p;
}

// 打印
void List::print()
{
	for(Node* p = m_head; p; p = p->next) {
		cout << "节点值: [" << p->data << "]"<< endl;
	}
}

// 在d位置之前插入d1
void List::insert_pos(const int& d, const int&d1)
{
	Node *p = find(d);
	Node *q = new Node(d1);
	q->next = p->next;
	p->next = q;
}

// 删除
void List::erase(const int& d)
{
	Node *p = find(d);
	
	// 因为p是上一个节点的位置，用q来保存要删除的节点的地址
	Node *q = p->next;

	// 通过将上一个节点的next指针指向要删除节点的next指针指向的节点实现断开要删除节点的目的
	p->next = q->next;	// p->next = p->next->next;

	delete q;
}

// 修改指定数据
void List::update(const int& d, const int& d1)
{
	Node *p = find(d);
	p->next->data = d1;
}

// 反转链表 方法1(此方法未将头节点反转)
void List::reverse_01()
{
	if(m_head == NULL || m_head->next == NULL || m_head->next->next == NULL || m_head->next->next->next == NULL) { 
		cout << "链表长度不足!" <<endl;
		return;
	}

	Node *p = m_head->next;			// 头节点之后的第1个节点
	Node *q = m_head->next->next;	// 头节点之后的第2个节点
	Node *k = m_head->next->next->next;	// 头节点之后的第3个节点

	p->next = NULL;					// 将头节点之后的第1个节点的next指针置空(断开第1个节点与第2个节点)

	// 根据k是否为空来判断 以此逆序每一个节点
	int i = 0;
	while(k) {
		++i;
		cout << "-----进入" << i << "次循环-----" << endl;
		cout << "循环内部开始的值:  p:" << p->data << " q:" << q->data <<" k:" << k->data << " m_head->next: " << m_head->next->data << endl;
		cout << "循环内部阶段1: q->next:" << q->next->data << "  p:" << p->data << endl; 
		q->next = p;		// 反转一个节点
		cout << "循环内部阶段2: q:" << q->data << "  q->next:" << q->next->data << "  p:" << p->data << endl; 
		p = q;				// 依序后移
		cout << "循环内部阶段3: q:" << q->data << "  q->next:" << q->next->data << "  p:" << p->data << "  p->next:" << p->next->data << endl; 
		q = k;				// 依序后移
		cout << "循环内部阶段4: q:" << q->data;
		if(q->next != NULL) { cout << "  q->next:" << q->next->data; }
		cout << "  p:" << p->data;
		cout << "  p->next:" << p->next->data << endl; 
		k = k->next;		// 依序后移

		if(k != NULL) {
			cout << "循环内部结束的值:  p:" << p->data << " q:" << q->data <<" k:" << k->data << " m_head->next: " << m_head->next->data << endl;
		}

		cout << "-----第" << i << "次循环结束-----" << endl;
	}

	// 将最后一个节点逆序
	q->next = p;

	// 将头节点重新指向新的第一个节点(老链表的最后一个节点)
	m_head->next = q;
}

// 反转链表 方法2: 本质上是浅拷贝, pPre pCur pNex只是每个节点的地址的指针名字,赋值运算不会改变这个节点的任何信息,只是相当于名字更换了
//                                 核心步骤是 pCur->next = pPre, 将节点的next节点置为前置节点而非之前的后置节点; 打印结果如下所示
//------>pPre[10] pCur[20] pPre->next[0] pCur->next[30]
//------>pPre[20] pCur[30] pPre->next[10] pCur->next[40]
//------>pPre[30] pCur[40] pPre->next[20] pCur->next[50]
//------>pPre[40] pCur[50] pPre->next[30] pCur->next[60]
void List::reverse_02()
{
	if(NULL == m_head || NULL == m_head->next){
		cout << "链表长度不足 list length not enough.." << endl;
		return;
	}
	
	Node *pPre = m_head;
	Node *pCur = m_head->next;
	Node *pNex = NULL;

	while(pCur != NULL) {
		pNex = pCur->next;
		pCur->next = pPre;
		pPre = pCur;
		pCur = pNex;
		if (pCur != NULL && pCur->next != NULL) {
			cout << "------>pPre[" << pPre->data << "] pCur[" << pCur->data << "] pPre->next[" << pPre->next->data << "] pCur->next[" << pCur->next->data << "]" << endl;
		}
	}

	m_head->next = NULL;
	m_head = pPre;
}

Node* List::reverse_03(Node* head)
{
	if(head == nullptr || head->next == nullptr) {
		return head;
	}

	cout << "begin" << endl;
	Node* newHead = reverse_03(head->next);
	head->next->next = head;
	head->next = nullptr;
	return newHead;
}

int main()
{
	// insert begin...
	cout << "run..." << endl;
	List list;
	list.insert(60);
	list.insert(50);
	list.insert(40);
	list.insert(30);
	list.insert(20);
	list.insert(10);

/*
	list.insert_pos(10, 5);
	list.print();
	cout << "--------------- 分割线 ---------------" << endl;

	list.erase(10);
	list.print();
	cout << "-------------- 删除元素 10 -----------" << endl;
*/
	cout << "-------------- 反转链表开始 ----------" << endl;
	list.print();
	list.reverse_03(list.m_head);
	cout << "-------------- 反转链表完毕 ----------" << endl;
	list.print();

/*
	list.update(5, 0);
	list.print();
	cout << "-------------- 更新元素5 -------------" << endl;
*/
	return 0;
}

