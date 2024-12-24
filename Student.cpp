#include "Student.h"

Student::Student()
{

	cout << "Student" << endl;
	cout << "Enter student details:" << endl;
	try
	{

		setType(1);

		cin.ignore(256, '\n');
		cout << "Surname: ";
		getline(cin, this->surename);
		cout << "First name: ";
		getline(cin, this->name);
		cout << "Middle name: ";
		getline(cin, this->patronim);
		cout << "Major: ";
		getline(cin, this->specialtyName);

		cout << "Group: ";
		cin >> this->group;

		cout << "Year: ";
		cin >> this->year;

		cout << "Average grade: ";
		cin >> this->score;

		setError(false);
	}

	catch (string err)
	{

		cout << "ERROR: " + err << endl; setError(true);
	}
}



Student::Student(ifstream& fin)
{

	setType(1);
	fin >> this->year
		>> this->group
		>> this->score;

	fin.ignore(256, '\n');
	getline(fin, name);
	getline(fin, surename);
	getline(fin, patronim);
	getline(fin, specialtyName);
}



Student::~Student()
{

	cout << "Destructor" << endl;
	system("pause");
}



void Student::edit()
{


	try
	{
		int index;
		int iTmp;
		string sTmp;
		cout << "Select a parameter to change" << endl
			<< "1 - name" << endl
			<< "2 - last name" << endl
			<< "3 - middle name" << endl

			<< "4 - Specialty" << endl
			<< "5 - Year of study" << endl
			<< "6 - GPA" << endl
			<< " "; cin >> index;
		if (index < 1 || index > 6)
		{

			throw (string)"No such parameter";
		}

		cout << "Current value: ";
		switch (index)
		{
		case 1:

			cout << name << endl;
			cout << "New value: ";
			cin.ignore(256, '\n');
			getline(cin, sTmp);
			name = sTmp;
			break;

		case 2:
			cout << surename << endl;
			cout << "New value: ";
			cin.ignore(256, '\n');
			getline(cin, sTmp);
			surename = sTmp;
			break;
		case 3:

			cout << patronim << endl;
			cout << "New value: ";
			cin.ignore(256, '\n');
			getline(cin, sTmp);
			patronim = sTmp;
			break;

		case 4:

			cout << specialtyName << endl;
			cout << "New value: ";
			cin.ignore(256, '\n');
			getline(cin, sTmp);
			specialtyName = sTmp;
			break;
		case 5:

			cout << year << endl;
			cout << "New value: ";
			cin >> iTmp;

			year = iTmp;
			break;

		case 6:
			cout << score << endl;
			cout << "New value: ";
			cin >> iTmp;

			score = iTmp;
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



void Student::save(ofstream& fout)
{

	fout << getType() << endl
		<< this->year << endl
		<< this->group << endl
		<< this->score << endl
		<< this->name << endl
		<< this->surename << endl
		<< this->patronim << endl
		<< this->specialtyName << endl;
}

void Student::print(ostream& out)
{

	out << "Student" << endl
		<< "Full name " << surename << " " << name << " " << patronim << endl
		<< "Specialty: " << specialtyName << endl
		<< "Group: " << group << endl
		<< "Course: " << year << endl
		<< "Average score: " << score << endl;
}