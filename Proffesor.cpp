#include "Proffesor.h"

Proffesor::Proffesor()
{

	cout << "Professor" << endl;
	try
	{

		setType(3);

		cin.ignore(256, '\n');
		cout << "Surname: ";
		getline(cin, this->surename);
		cout << "First name: ";
		getline(cin, this->name);
		cout << "Middle name: ";
		getline(cin, this->patronim);
		cout << "Subject that leads: ";
		getline(cin, this->subjects);
		cout << "Group that leads: ";
		cin >> this->group;
		setError(false);
	}

	catch (string err)
	{

		cout << "ERROR: " + err << endl; setError(true);
	}
}



Proffesor::Proffesor(ifstream& fin)
{

	setType(3);
	fin >> this->group;

	fin.ignore(256, '\n');
	getline(fin, name);
	getline(fin, surename);
	getline(fin, patronim);
	getline(fin, subjects);
}



Proffesor::~Proffesor()
{

}



void Proffesor::edit()
{

	try
	{

		int index;
		int iTmp;
		string sTmp;

		cout << "Select what you want to change:" << endl
			<< "1 - Last Name" << endl
			<< "2 - First Name" << endl
			<< "3 - Middle Name" << endl
			<< "4 - Group" << endl
			<< "5 - Subject" << endl
			<< " "; cin >> index;
		if (index < 1 || index > 5)
		{

			throw (string)"No such parameter";
		}

		cout << "Current value: ";
		switch (index)
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
			cin >> iTmp;
			patronim = iTmp;
			break;

		case 4:
			cout << group << endl;
			cout << "New value: ";
			cin >> iTmp;
			group = iTmp;
			break;

		case 5:

			cout << subjects << endl;
			cout << "New value:: ";
			cin >> iTmp;
			subjects = iTmp;
			break;
		default:
			break;

		}
		setError(false);
	}

	catch (string err)
	{

		cout << "ERROR: " + err << endl;
		setError(true);
	}
}

void Proffesor::save(ofstream& fout)
{

	fout << getType() << endl
		<< this->group << endl
		<< this->name << endl
		<< this->surename << endl
		<< this->patronim << endl
		<< this->subjects << endl;

}

void Proffesor::print(ostream& out)
{

	out << "Professor" << endl;
	out << "Full name: " << surename << " " << name << " " << patronim << " " << endl
		<< "Group: " << this->group << endl
		<< "Subject: " << this->subjects << endl;
}