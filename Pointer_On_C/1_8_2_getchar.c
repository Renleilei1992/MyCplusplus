
#include <iostream>
#include <cstdio>

using namespace std;

extern "C"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main()
{
	int ch;		//此处ch被声明为int型，实际接收字符型，因为EOF是一个整型值，它的位数比字符类型的多，使用整型声明可以防止从输入读取的字符意外地被解释为EOF
	/* 意味着接收字符的 ch 必须足够大，足以容纳 EOF，所以此处声明ch为整型类型，字符只是小整型数，所以用一个整型变量容纳字符值完全足够*/
	int line = 0;
	int at_begining = 1;

	while((ch = getchar()) != EOF){
		if(at_begining == 1){
			line += 1;
			at_begining = 0;
			printf("%d ", line);
		}
		putchar(ch);
		if(ch == '\n'){
			at_begining = 1;
		}else if( ch == '0' ){		//手动添加了一个 '0' 作为停止的标志
			printf("\n");
			break;
		}
	}

	return EXIT_SUCCESS;
}
