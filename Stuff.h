#pragma once 
#include "University.h"


class Stuff : public University
{
	string name;
	string surename;
	string patronim;
	string role;
	string phone;
	string expertise;

public:

	

	Stuff();
	Stuff(ifstream& fin);
	~Stuff(); void edit();
	void save(ofstream& fout); 
	void print(ostream& out);
};
