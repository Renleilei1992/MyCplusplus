/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：077_compareVersion.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年10月31日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;

int compareVersion(string v1, string v2);
int compareVersion_LeetCode(string version1, string version2);

int main(int argc, char** argv)
{

	string ver1 = "7.3.4.1";
	string ver2 = "7.3.5.1";
	
	cout << "Plz input the version 1 : " << endl;
	cin >> ver1;
	cout << "Plz input the version 2 : " << endl;
	cin >> ver2;

//	int ret_val = compareVersion(ver1, ver2);
	int ret_val = compareVersion_LeetCode(ver1, ver2);
	if ( ret_val == 0 ) {
		cout << ver1 << " is equal to " << ver2 << endl;
	} else if ( ret_val == 1 ) {
		cout << ver1 << " is greater than " << ver2 << endl;
	} else if ( ret_val == -1 ) {
		cout << ver1 << " is smaller than " << ver2 << endl;
	}

	return 0;
}

int compareVersion(string v1, string v2)
{
	// version format: 7.1.3.4
	if (v1 == v2) return 0;

	int len1 = v1.length();
	int len2 = v2.length();

	int i = 0, j = 0;
	while( i < len1 && j < len2) {
		int p1 = 0, p2 = 0;
		while( i < len1 && v1[i] != '.') {
			p1 = 10 * p1 + v1[i] - '0';
			i++;
		}

		while( j < len2 && v2[j] != '.') {
			p2 = 10 * p2 + v2[j] - '0';
			j++;
		}

		if ( p1 < p2 ) return -1;
		else if ( p1 > p2 ) return 1;
		else{
			i++;
			j++;
			if ( i >= len1 && j >= len2 ) return 0;
		}
	}

	// handle the equal version like "1.0.0.0" and "1.0"
	while( i < len1 ){
		int p1 = 0;
		while( i < len1 && v1[i] != '.') {
			// any value is greater than 0, v1 is larger
			p1 = 10 * p1 + v1[i] - '0';
			if ( p1 > 0 ) return 1;
			i++;
		}

		// the remain part is all 0, so two versions are equal
		if( i >= len1 && p1 == 0 ) return 0;
		else i++;
	}

	while( j < len2 ){
		int p2 = 0;
		while( j < len2 && v2[j] != '.') {
			// any value is greater than 0, v2 is larger
			p2 = 10 * p2 + v2[j] - '0';
			if ( p2 > 0 ) return -1;
			j++;
		}

		// the remain part is all 0, so two versions are equal
		if( j >= len2 && p2 == 0 ) return 0;
		else j++;
	}

	return 0;
}

int compareVersion_LeetCode(string version1, string version2) {
        
	//string exact the same
	if (version1 == version2 ) return 0;
	
	int len1 = version1.length(); int len2 = version2.length();
	int i = 0, j = 0 ;

	while ( i < len1 && j < len2){
		
		int p1 = 0, p2 = 0 ;
		
		while( i < len1  && version1[i] != '.' ){
			p1 = 10 * p1 + version1[i] - '0';
			i++;
		}
		
		while( j < len2 && version2[j] != '.' ){
			p2 = 10 * p2 + version2[j] - '0';
			j++;
		}
		
		if ( p1 < p2 ) return -1;
		else if ( p1 > p2 ) return 1;
		
		else{
			i++; j++;
			//both reach the end of the string and their values always equal
			if ( i >= len1 && j >= len2 ) return 0;
		}
	}
	
	// verison1 has some remain part to check, it is still possible they are equal, for example:
	// version1="1.0.0.0.0" and version2 = "1.0"
	while ( i < len1 ){
		
		int p1 = 0;
		while( i < len1 && version1[i] != '.'){
			
			//any value is greater than 0, version1 is larger
			p1 = 10 * p1 + version1[i] - '0';
			if ( p1 > 0 ) return 1;
			i++;
		}
					
		//the remain part is all 0, so two verisons are equal
		if ( i >= len1 && p1 == 0 ) return 0;
		else i++;
		
	}
	
	//verison1 has some remain part to check, similarly it is still possible they are equal
	while ( j < len2 ){
		
		int p2 = 0;
		while( j < len2 && version2[j] != '.'){
			//any value is greater than 0, version2 is larger
			p2 = 10 * p2 + version2[j] - '0';
			if ( p2 > 0 ) return -1;
			j++;
		}
		//the remain part is all 0, so two verisons are equal
		if ( j >= len2 && p2 == 0 ) return 0;
		else j++;
		
	}

	return 0;
}
