#pragma once 
#include "University.h"
class Proffesor : public University
{
	string name;
	string surename;
	string patronim;
	int group;
	string subjects;

public:

	

	Proffesor();
	Proffesor(ifstream& fin);
	~Proffesor(); 
	void edit();
	void save(ofstream& fout); 
	void print(ostream& out);

};

