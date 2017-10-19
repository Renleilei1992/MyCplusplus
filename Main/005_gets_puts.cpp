

/* 简单实用gets puts函数 */


#include <cstdio>


extern "C"

#define MAX_LEN 100

int main()
{
	char input[MAX_LEN];
	char output[MAX_LEN];

	gets(input);
	printf("Original input: %s\n", input);

	//memset(input, 0x00, sizeof(input));
	fgets(input, MAX_LEN, stdin);

	printf("fgets input: %s\n", input);

	return 0;
}
