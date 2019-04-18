/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：096_DNShiJack_Windows.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年03月11日
*   描    述：此文件用于windows劫持dns解析, 编译使用VS2015测试通过并能正常使用
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <list>
#include <io.h>
using namespace std;

class DNS_Hijack {
private:
	list<string> interface_using;                   //获取本地可用网卡
	list<string> last_get_interface_using;
private:
	string str;                             //存储文件读取后的内容
	string DNS;

private:
	void Get_using_interface()
	{
		system("netsh interface show interface > interface_info.txt");

		FILE* fp = fopen("interface_info.txt", "rb");
		const int file_size = filelength(fileno(fp));
		char* buff = (char*)malloc(sizeof(char)*file_size);
		if (fp) {
			fread(buff, 1, file_size, fp);
			str = buff;
			free(buff);
			replaceA_to_B(str, "-------------------------------------------------------------------------\r\n", "");
			Split(str, "\r\n", interface_using);
			Spilt_space(interface_using);
		}
	}

private:
	void Spilt_space(list<string> list_str) {
		for (list<string>::iterator itor = list_str.begin(); itor != list_str.end(); itor++) {
			cout << *itor << endl;
			string::size_type first_variable = (*itor).find("已启用");
			string::size_type second_variable = (*itor).find("已连接");
			string::size_type third_variable = (*itor).find("专用");
			if (first_variable != string::npos && second_variable != string::npos && third_variable != string::npos) {
				string info = *itor;
				last_get_interface_using.push_back(info.substr(55, info.length()));
			}
		}

	}

private:
	void replaceA_to_B(std::string& S, const std::string A, const std::string B) {
		std::size_t found = S.find(A);
		while (std::string::npos != found) {
			S.replace(found, A.length(), B);
			found = S.find(A, found + 1);
		}
	}

private:
	void Split(const string& src, const string& separator, list<string>& dest)
	{
		string str = src;
		string substring;
		string::size_type start = 0, index;
		dest.clear();
		index = str.find_first_of(separator, start);
		do
		{
			if (index != string::npos)
			{
				substring = str.substr(start, index - start);
				dest.push_back(substring);
				start = index + separator.size();
				index = str.find(separator, start);
				if (start == string::npos) break;
			}
		} while (index != string::npos);

		//the last part
		substring = str.substr(start);
		dest.push_back(substring);
	}

public:
	DNS_Hijack(string DNS = "192.168.1.233")
	{
		Get_using_interface();
		for (list<string>::iterator itor = last_get_interface_using.begin(); itor != last_get_interface_using.end(); itor++)
		{
			string str = "netsh interface ip set dns \"" + (*itor) + "\" static " + DNS;
			cout << str << endl;
			system(str.c_str());
		}
	}

};

int main()
{
	DNS_Hijack* one = new DNS_Hijack("223.5.5.5");
	system("pause");
	return 0;
}
