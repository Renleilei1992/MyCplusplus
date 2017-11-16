#ifndef _018_STUDENT_H
#define _018_STUDENT_H

#include <string>
#include <iostream>

using namespace std;

class Student
{
private:
	int		id;
	string 	name;
public:
//	Student(const char& name, int id);
	int getID()const{ return id; }

	void introduce()const{
		cout<<"ID: "<<id<<" Name: "<<name<<endl;
	}
};

#endif
