// 编译方法: gcc -o main 024_stringLengthAndSize.cpp -lstdc++
// 编译方法: g++ -o main 024_stringLengthAndSize.cpp

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	string strInput;
	cout<<"Plz input the string: ";
	cin>>strInput;

	// c++
	string strHead = strInput.substr(0, strInput.size() - 3);
	string strTail = strInput.substr(1, strInput.size());

//	string strHead = strInput.substr(0, strInput.length() - 3);
//	string strTail = strInput.substr(1, strInput.length());

	// java
//	string strHead = strInput.substr(0, strInput.GetBytes().length - 3);
//	string strTail = strInput.substr(1, strInput.GetBytes().length);

	cout << strHead+","+strTail << endl;

	return 0;
}
