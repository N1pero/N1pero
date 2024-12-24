#include "Stuff.h"

Stuff::Stuff()
{

	cout << "Staff" << endl; try
	{

		setType(2);

		cin.ignore(256, '\n');
		cout << "Last name: ";
		getline(cin, this->surename);
		cout << "First name: ";
		getline(cin, this->name);
		cout << "Middle name: ";
		getline(cin, this->patronim);
		cout << "Job title: ";
		getline(cin, this->role);
		cout << "Phone: ";
		getline(cin, this->phone);
		cout << "Responsibility: ";
		getline(cin, this->expertise);
		setError(false);
	}

	catch (string err)
	{

		cout << "ERROR: " + err << endl; setError(true);
	}
}



Stuff::Stuff(ifstream& fin)
{

	setType(2);
	fin.ignore(256, '\n');
	getline(fin, surename);
	getline(fin, name);
	getline(fin, patronim);
	getline(fin, role);
	getline(fin, phone);
	getline(fin, expertise);
}



Stuff::~Stuff()
{

	cout << "Destructor" << endl; system("pause");
}



void Stuff::edit()
{


	try
	{

		int index;
		int iTmp;
		string sTmp;
		cout << "Select the parameter to change:" << endl
			<< "1 - Last name" << endl
			<< "2 - First name" << endl
			<< "3 - Middle name" << endl
			<< "4 - Position" << endl
			<< "5 - Phone" << endl
			<< "6 - Responsibility" << endl
			<< ": "; cin >> index;

		if (index < 1 || index > 6)
		{

			throw (string)"No such parameter";
		}

		cout << "Current value: "; switch (index)
		{
		case 1:
			cout << surename << endl;
			cout << "New value: ";
			cin.ignore(256, '\n');
			getline(cin, sTmp);

			surename = sTmp;
			break;
		case 2:
			cout << name << endl;
			cout << "New value: ";
			cin.ignore(256, '\n');
			getline(cin, sTmp);
			name = sTmp;
			break;

		case 3:
			cout << patronim << endl;
			cout << "New value: ";
			cin.ignore(256, '\n');
			getline(cin, sTmp);
			patronim = sTmp;
			break;

		case 4:

			cout << role << endl;
			cout << "New value: ";
			cin.ignore(256, '\n');
			getline(cin, sTmp);
			role = sTmp;
			break;

		case 5:

			cout << phone << endl;
			cout << "New value: ";
			cin.ignore(256, '\n');
			getline(cin, sTmp);
			phone = sTmp;
			break;


		case 6:

			cout << expertise << endl;
			cout << "New value: ";
			cin.ignore(256, '\n');
			getline(cin, sTmp);
			expertise = sTmp;
			break;
		default:
			break;

		}
		setError(false);
	}

	catch (string err)
	{

		cout << "ERROR: " + err << endl; setError(true);
	}
}



void Stuff::save(ofstream& fout)
{

	fout << getType() << endl
		<< this->name << endl
		<< this->surename << endl
		<< this->patronim << endl
		<< this->role << endl
		<< this->phone << endl
		<< this->expertise << endl;
}



void Stuff::print(ostream& out)
{

	out << "Employee" << endl
		<< "Full name: " << surename << " " << name << " " << patronim << endl
		<< "Position: " << this->role << endl;
	out << "Phone: " << this->phone << endl
		<< "Responsibility: " << this->expertise << endl;
}