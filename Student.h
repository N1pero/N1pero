#pragma once 
#include "University.h"

class Student : public University
{
 
	float score; 
	int year;
	int group;
	string name;
	string surename;
	string patronim;
	string specialtyName;


public:



	Student();
	Student(ifstream& fin);
	~Student();
	void edit();
	void save(ofstream& fout); 
	void print(ostream& out);

};





