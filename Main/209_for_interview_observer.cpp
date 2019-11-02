/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：209_for_interview_observer.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年11月02日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <vector>
using namespace std;

class IMessageObserver
{
public:
	virtual void onRsp(int a, int b, const char* lpStr) = 0;
	virtual void onNtf(int a, int b, const char* lpStr) = 0;
};

class IMessage
{
public:
	int RegisterMessageObserver(IMessageObserver* observer) { 
		if(observer != nullptr) {
			cout << __func__ << endl;
			m_vecMsgObservers.emplace_back(observer);
		}
	}

	int DeRegisterMessageObserver(IMessageObserver* observer) {
		for (std::vector<IMessageObserver*>::iterator it = m_vecMsgObservers.begin(); it != m_vecMsgObservers.end(); ++it) {
	//		if (it == observer) {
				cout << __func__ << endl;
				m_vecMsgObservers.erase(it);
	//		}
		}
	}

	void notify(int a, int b, const char* lpStr) {
		cout << "IMessage::" << __func__ << " a=" << a << " b=" << b << " lpStr: " << lpStr << endl;
		for (auto iVec : m_vecMsgObservers) {
			iVec->onRsp(a, b, lpStr);
			iVec->onNtf(a, b, lpStr);
		}
	}

private:
	std::vector<IMessageObserver*> m_vecMsgObservers;
};

static IMessage* s_Message_ptr = new IMessage();

class A : public IMessageObserver
{
public:
	A() {
		cout << __func__ << endl;
		s_Message_ptr->RegisterMessageObserver(this);
	}

	~A() {
		cout << __func__ << endl;
		s_Message_ptr->DeRegisterMessageObserver(this);
	}

	void show() { cout << "A::" << __func__ << " hello A" <<endl; }

	virtual void onRsp(int a, int b, const char* lpStr) {
		cout << "A::" << __func__ << " a=" << a << " b=" << b << " lpStr: " << lpStr << endl;
	}
	virtual void onNtf(int a, int b, const char* lpStr) {
		cout << "A::" << __func__ << " a=" << a << " b=" << b << " lpStr: " << lpStr << endl;
	}
};

int main()
{
	A* a_ptr = new A();
	a_ptr->show();

	// 遍历观察者通知
	s_Message_ptr->notify(5, 10, "hello observers!!");

	delete a_ptr;
	return 0;
}
