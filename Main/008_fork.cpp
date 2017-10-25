
/* 测试循环fork的进程数量及pid号 */

#include <iostream>
#include <unistd.h>

extern "C"

using namespace std;

int main(int argc,char **argv)
{
	pid_t pid_num = 0;
	int count = 0;

	for(int i = 1; i < 4; i++){
		pid_num = fork();
		if(pid_num < 0){
			cout<<"error in fork!"<<endl;
		}else if(pid_num == 0){
			cout<<"I'm the child process, my process id is ["<<getpid()<<"]"<<endl;
			count++;
		}else{
			cout<<"I'm the father process, my process id is ["<<getpid()<<"]"<<endl;
		}
		
	//	cout<<"第"<<i<<"次pid = ["<<pid_num<<"]"<<endl;
    //  cout<<"---------------------------"<<endl;
	//	sleep(1);
	}
	return 0;
}
