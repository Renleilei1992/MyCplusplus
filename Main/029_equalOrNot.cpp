

#include <iostream>

using namespace std;

int main()
{
  const char *a = "abc";
  const char *b = "abc";

  if(a == b){
    cout<<"a == b"<<endl;
  }else{
    cout<<"a != b"<<endl;
  }

  cout<<"a = "<<a<<" &a = "<<&a<<endl;
  cout<<"b = "<<b<<" &b = "<<&b<<endl;

  return 0;
}
