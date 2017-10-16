
/* 知识点: 双重for循环可看做 两个集合A,B的笛卡尔积 A X B， 笛卡尔积不满足交换律,结合律 */
/* 例子: A={a,b} B={1,2,3} AXB={(a,1),(a,2),(a,3),(b,1),(b,2),(b,3)}                   */
/* 笛卡尔积可运用于数据库  */


#include <stdio.h>

void func_01()
{
	const char* A[] = {"黑桃","红桃","梅花","方块"};
	const char* B[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 13; j++){
			printf("%s %-2s ", A[i], B[j]);
		}
		puts("");
	}
}

void func_02()
{
	const char* A[] = {"黑桃","红桃","梅花","方块"};
	const char* B[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

	for(int j = 0; j < 13; j++){
		for(int i = 0; i < 4; i++){
			printf("%s %-2s ", A[i], B[j]);
		}
		puts("");
	}
}

int main(){
	
	printf("-------func_01----------\n");
	func_01();
	printf("-------func_01----------\n");
	func_02();

	return 0;
}
