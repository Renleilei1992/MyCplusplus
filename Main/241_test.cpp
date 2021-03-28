
#include <iostream>


int main()
{
 char sc = 0x81;
 unsigned char uc = 0x81;

 int sn = sc;
 unsigned int un = uc;

 if (sn == un) {
  std::cout << "equal" << std::endl;
 } else {
  std::cout << "not equal" << std::endl;
 }

 std::cout << "sn:" << sn << std::endl;
 std::cout << "un:" << un << std::endl;

	return 0;
}
