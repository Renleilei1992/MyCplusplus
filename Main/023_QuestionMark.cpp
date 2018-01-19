//
//
#include <iostream>

using namespace std;

enum state
{
	eTgroup_01,
	eTgroup_02,
};

int main(int argc, char **argv)
{
	state m_eTgroupState = eTgroup_01;

	int num_01 = (m_eTgroupState == eTgroup_02) ? 1 : 2;

	cout<<num_01<<endl;

	if(!(m_eTgroupState == eTgroup_01))
	{
		cout<<"It's equal!"<<endl;
	}
	return 0;
}
