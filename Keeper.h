#pragma once
#include "Stuff.h" 
#include "Student.h" 
#include "Proffesor.h" 
#include <iostream>

class Keeper
{
	University** data; 
	int size;

public:
		
	Keeper();
	~Keeper(); 
	int getSize(); 
	void add();
	void add(int _type, ifstream& fin); 
	void edit();
	void del(); void save(); 
	void load();
	friend ostream& operator<<(ostream& out, Keeper& obj);
};

