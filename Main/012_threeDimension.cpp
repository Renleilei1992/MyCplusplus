
#include <iostream>

using namespace std;

int main()
{
	int _sum = 0, _pro = 0;
	for(int a = 1; a <= 99; a++)
	for(int b = 1; b <= 99; b++)
	for(int c = 1; c <= 99; c++){
		_sum = a + b + c;
		_pro = a * b * c;
		if(_sum == 103 && _pro == 20592){
			cout<<a<<" "<<b<<" "<<c<<" "<<endl;
		}
	}

	return 0;
}
