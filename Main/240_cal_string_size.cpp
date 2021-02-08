/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：240_cal_string_size.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年07月08日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <string.h>

using namespace std;

#define VT_STR 1

class BaseA
{
public:
	std::string m_str1;
	std::string m_str2;

public:
	void setData(const char* data1, const char* data2) {
		m_str1 = std::string(data1);
		m_str2 = std::string(data2);
	}

	void show() {
		std::cout << __func__ << ":: m_str1: " << m_str1 << " m_str2: " << m_str2 << std::endl; 
	}

	int getSize() const {
		return m_str1.length() + m_str2.length();
	}

	const unsigned char* getData() const {
		size_t length = this->getSize() + 8 + 8;	// 算出这个流的总长度 (初步计划流组成结构: 类型1+长度1+值1+类型2+长度2+值2)
		std::cout << __func__ << ":: be called! size: " << length << " str1: " << m_str1 << " str2: " << m_str2 << std::endl;
		unsigned char* buffer = new unsigned char[length];
		
		const char* cstr1 = m_str1.c_str();
		std::cout << __func__ << " cstr1: " << cstr1 << std::endl;
		const char* cstr2 = m_str2.c_str();
		std::cout << __func__ << " cstr2: " << cstr2 << std::endl;
		const char* cstr3 = (m_str1 + m_str2).c_str();
		//std::string str3 = m_str1 + m_str2;
		std::cout << __func__ << " cstr3: " << cstr3 /*<< " str3: " << str3*/ << std::endl;
		
		// 写入类型1
		int offset = 0;
		//*((int*)buffer) = VT_STR;
		memcpy(buffer, (unsigned char*)VT_STR, sizeof(VT_STR));
		offset += sizeof(VT_STR);
		std::cout << __func__ << " type1 write end! " << reinterpret_cast<const char*>(buffer) << std::endl;
		// 写入长度1
		//*((int*)buffer);

		//strcpy(buffer + offset, m_str1.c_str(), m_str1.length());
		//offset += m_str1.length();
		std::cout << __func__ << " buffer: " << std::string(reinterpret_cast<const char*>(buffer)) << std::endl;
		return buffer;
	}

};


int main()
{
/*
	BaseA obj1;
	obj1.setData("Hello World!", "Hello C++!");
	std::cout << "BaseA'size: " << sizeof(BaseA) << " sizeof(obj): " << sizeof(obj1) << " actual size: " << obj1.getSize() << std::endl;

	const unsigned char* buf = obj1.getData();
	int len = obj1.getSize();

	std::string str(reinterpret_cast<const char*>(buf));
	std::cout << "str: " << str << " len: " << len << std::endl;
*/
	//std::string str1 = "helllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll";
	std::string str1 = "StubCallbackRequest";
	std::cout << "sizeof(str1): " << sizeof(str1) << " str1.size: " << str1.size() << " " << strlen(str1.c_str())  << std::endl;

/*
	std::string s1 = "nihao!";
	std::string s2 = "???111";
	const char* s12 = (s1+s2).c_str();
	std::cout << "test: s1+s2 = " << s12 << std::endl;
*/

	return 0;
}
