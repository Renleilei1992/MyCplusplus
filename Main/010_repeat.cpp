

#include <iostream>

using namespace std;

int main()
{
	int x , _sum, _pro;
	for(int a = 1; a <= 9; a++)
	for(int b = 1; b <= 9; b++)
	for(int c = 1; c <= 9; c++)
	for(int d = 1; d <= 9; d++)
	for(int e = 1; e <= 9; e++)
	for(int f = 1; f <= 9; f++){
		x = a*100000 + b*10000 + c*1000 + d*100 + e*10 + f;
		_sum = a+b+c+d+e+f;
		_pro = a*b*c*d*e*f;
		if(_sum == 12 && _pro == 64){
			cout<<x<<endl;
		}
	}

	return 0;
}
