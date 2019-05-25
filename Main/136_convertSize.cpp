/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：136_convertSize.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月23日
*   描    述：输入大小(bytes)，转为KB或者MB或者GB
*   版    本: Version 1.00
*	编译指令: g++ -o mian 136_convertSize.cpp -std=c++11
================================================================*/

#include <string>
#include <sstream>		// std::ostringstream 's header
#include <iomanip>		// std::setprecision 's header  此函数用来控制保留n位有效数字,最后一位是四舍五入后的结果
#include <iostream>

using namespace std;

long MB_LIMITATION = 1024 * 1024 * 1024;		// 此处有坑: 倘若使用整数相乘,过程中的临时结果会使用int类型存储,相乘过程中会溢出int最大值!!
long GB_LIMITATION = MB_LIMITATION * 1024;		// 解决措施: 可以将中间变量均使用long类型进行接收,避免超过int类型的最大值

string convertSize(long size);

int main()
{
	long lSize = 10241231411;

	cout << lSize << " B is " << convertSize(lSize) << endl;

	return 0;
}

string convertSize(long size)
{
	auto convertByteToMByte = [](long bytes) -> string {
        std::ostringstream str;

		cout << "bytes: " << bytes << " str: " << str.str() << endl;
        if (bytes < 1024) {
            str << bytes << "B";
        } else if (bytes < 1024 * 1024) {
            str << std::setprecision(3) << bytes / 1024 << "KB";
        } else if (bytes < 1024 * 1024 * 1024) {
            str << std::setprecision(3) << bytes / (1024 * 1024) << "MB";
        } else if (bytes < GB_LIMITATION) {
            str << std::setprecision(3) << bytes / (1024 * 1024 * 1024) << "GB";
		}
        return str.str().c_str();
    };

	string sizeStr = convertByteToMByte(size);

	return sizeStr;
}
