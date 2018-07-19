/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：068_calculate_24.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年07月17日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include<bits/stdc++.h>

using namespace std;

#define judge fabs(sum-vaule)<1e-8||fabs(sum+vaule)<1e-8||fabs(sum-1.0/vaule)<1e-8||fabs(sum+1.0/vaule)<1e-8

double a[6];
double sum=0;
int num,vaule;

bool dfs(int i,int b){
	if(i<num){
		if(b==1)sum+=a[i];
		if(b==2)sum-=a[i];
		if(b==3)sum*=a[i];
		if(b==4)sum/=a[i];
	
		for(int j=1;j<=4;j++){
			if(dfs(i+1,j)){
				return true;
			}
		}

		if(b==1)sum-=a[i];
		if(b==2)sum+=a[i];
		if(b==3)sum/=a[i];
		if(b==4)sum*=a[i];
	}
	else if(judge){
		return true;
	}
	return false;
}

int main(){
	int N;
	cout << "please input the number of you will input: ";
	cin>>N;
	cout << "you will input [" << N << "] number!" << endl;

	while(N--){
		cin>>num>>vaule;
		for(int i=0;i<num;i++)cin>>a[i];
		sort(a,a+num);
		int flag=0;

		do{
			sum=a[0];
			if(flag)break;
			for(int i=1;i<=4;i++){
				if(dfs(1,i)){
					cout<<"Yes"<<endl;
					flag=1;
					break;
				}
			}
		}while(next_permutation(a,a+num));

		if(!flag)cout<<"No"<<endl;
	}

	return 0;
}
