/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：168_sharedPtr.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月15日
*   描    述：实现一个自己的智能指针 shared_ptr
*   版    本: Version 1.00
================================================================*/

#ifndef __SHARED_PTR
#define __SHARED_PTR

template <typename T>
class shared_ptr {
public:
	// 指针构造函数: 保存指针,初始化引用计数为1
	shared_ptr(T* p) : count(new int(1)), _ptr(p) {}
	
	// 析构函数, 引用计数-1, 检查是否需要delete
	~Shared_ptr() {
		if(_ptr != nullptr && --*useCount == 0) {
			delete useCount;
			delete _ptr;
			useCount = nullptr;
			_ptr = nullptr;
		}
	}
	
	// 拷贝构造函数: 保存指针,保存引用计数并+1
	shared_ptr(shared_ptr<T>& other) : useCount(&(++*other.useCount)), _ptr(other._ptr) {}
	
	// 重载->操作符
	T* operator->() { return _ptr; }
	
	// 重载*操作符
	T& operator*() { return *_ptr; }
	
	// 重载赋值运算符: 自身引用计数-1, 并检查是否delete
	// 保存其他指针, 保存引用计数并+1
	shared_ptr<T>& operator=(shared_ptr<T>& other) {
		++*other.useCount;
		if (this->_ptr && 0 == --*this->useCount) {
			delete useCount;
			delete _ptr;
			count = nullptr;
			_ptr = nullptr;
		}
		
		this->_ptr = other._ptr;
		this->useCount = other.count;
		return *this;
	}
	
	// 返回当前计数
	int getRef() { return *count; }
	
private:
	// 引用计数必须为指针,这样多个对象共享同一个引用计数
	int *useCount;
	// 保存目标指针
	T* _ptr;
};

#endif // __SHARED_PTR

/**
unique_ptr<int> uPtr1(new int(1));
unique_ptr<int> uPtr2 = uPtr1; // error, no copy.
unique_ptr<int> uPtr3 = std::move(uPtr1);	// ok.
uPtr3.reset();

shared_ptr<int> sPtr(new int(1));
shared_ptr<int> sPtr1 = sPtr;
weak_ptr<int> wPtr = sPtr;
*/
