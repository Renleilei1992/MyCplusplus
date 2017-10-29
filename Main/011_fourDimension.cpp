
#include <iostream>

using namespace std;

int main()
{
	int _sum = 0, _pro = 0;
	for(int a = 1; a <= 9; a++)
	for(int b = 1; b <= 9; b++)
	for(int c = 1; c <= 9; c++)
	for(int d = 1; d <= 9; d++){
		_sum = a + b + c + d;
		_pro = a * b * c * d;
		if(_sum == 25 && _pro == 504){
			cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
		}
	}

	return 0;
}
