
/*
*
* 要求: 9个数字，组合成三组三位数，无重复数字且满足1:2:3
*
*/

#include <cstdio>

extern "C"

int main()
{
	int count = 0;
	int x = 0, y = 0, z = 0, _sum = 0, _pro = 0;
	for(int a = 1; a < 4; a++)
	for(int b = 1; b <= 9; b++)
	for(int c = 1; c <= 9; c++)
	for(int d = 2; d <= 9; d++)
	for(int e = 1; e <= 9; e++)
	for(int f = 1; f <= 9; f++)
	for(int g = 3; g <= 9; g++)
	for(int h = 1; h <= 9; h++)
	for(int i = 1; i <= 9; i++){
		count++;
		x = a*100 + b*10 + c;
		y = d*100 + e*10 + f;
		z = g*100 + h*10 + i;
		_sum = a+b+c+d+e+f+g+h+i;
		_pro = a*b*c*d*e*f*g*h*i;
		if(y==2*x && z==3*x && _sum==45 && _pro==362880){
			printf("%d:%d:%d\n", x, y, z);
		}
	}

	printf("loop times: %d\n", count);
	return 0;
}
