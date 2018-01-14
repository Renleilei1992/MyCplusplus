//
//
// 
// 将时间格式的变量转换为字符串格式
#include <iostream>

using namespace std;

int main(int argc,char** argv)
{
	time_t t = time(0);

	char timeCh[64];

	strftime(timeCh, sizeof(timeCh), "%Y-%m-%d %H:%M:%S", localtime(&t));

	cout<<timeCh<<endl;

	return 0;
}
