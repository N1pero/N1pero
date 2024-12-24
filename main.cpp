#include <iostream> 
#include "Keeper.h" 
#include "windows.h" 
using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Keeper Konten;
	int menu;
	do
	{

		system("cls");

		cout << "Data in array - " << Konten.getSize() << endl

			<< "1 - add" << endl
			<< "2 - delete" << endl
			<< "3 - save to file" << endl
			<< "4 - load from file" << endl
			<< "5 - change" << endl
			<< "6 - output" << endl
			<< "0 - exit" << endl;
		cin >> menu;
		system("cls");
		switch (menu)
		{
		case 1:

			Konten.add();
			break;
		case 2:

			Konten.del();
			break;

		case 3:

			Konten.save();
			break;

		case 4:

			Konten.load();
			break;


		case 5:

			Konten.edit();
			break;


		case 6:

			cout << Konten;
			break;



		case 0:
			return 0;

		default:
			break;

		}
	} while (true);
}