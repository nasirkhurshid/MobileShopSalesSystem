 #include <iostream>
#include <fstream>
using namespace std;

struct phone {				//structure for storing records
	int id;					//variable for phone's ID
	char maker[20];			//variable for phone's maker
	char model[10];			//variable for phone's model
	int ram, rom;			//variables for phone's RAM and ROM
};

void addphone(phone& p) {													//function for adding a new record to file
	fstream file ("data.bin", ios::app | ios::binary);						//opening file in append and binary mode
	cout << "\nPlease add necessary information about the phone!\n";		//taking inputs from user
	cout << "Enter ID of the phone: ";
	cin >> p.id;
	cout << "Enter Maker of the phone: ";
	cin >> p.maker;
	cout << "Enter Model of the phone: ";
	cin >> p.model;
	cout << "Enter RAM of the phone: ";
	cin >> p.ram;
	cout << "Enter ROM of the phone: ";
	cin >> p.rom;
	file.write((const char*)&p, sizeof(p));									//writing data to file
	file.close();															//closing file
}

void addwhileupdate(phone& p)												//function for updating the record and is
{																			//only called when user is updating a record
	cout << "\nUpdating the phone...\n";
	cout << "Enter new ID of the phone: ";									//taking inputs
	cin >> p.id;
	cout << "Enter new Maker of the phone: ";
	cin >> p.maker;
	cout << "Enter new Model of the phone: ";
	cin >> p.model;
	cout << "Enter new RAM of the phone: ";
	cin >> p.ram;
	cout << "Enter new ROM of the phone: ";
	cin >> p.rom;
}

void display(const phone& p) {											//function for displaying the records stored in file
	cout << "Phone's ID: " << p.id << ", Phone's Maker: " << p.maker << ", Phone's Model: " << p.model <<
		", Phone's RAM: " << p.ram << ", Phone's ROM: " << p.rom << endl;
}

void searchphone(const phone& p)										//function for searching a particular phone using RAM
{
	int i,j=0;															//variables for getting RAM and checking whether record is found or not
	cout << "\nYou can search any phone here by RAM!\n";
	cout << "Enter the value of RAM for which you want to search Mobile Phone: ";
	cin >> i;															//getting value of RAM
	fstream file("data.bin", ios::in | ios::binary);					//opening file in read and binary mode
	while (!file.eof())													//loop for checking end of file
	{
		file.read((char*)&p, sizeof(p));								//reading data from the file
		if (i == p.ram)													//comparing record's RAM and wanted RAM
		{
			j++;														//incrementing when record is found
			if (file.gcount() > 0)										//checking whether bytes read are greater than zero or not
			{
				cout << "Record " << j << ":\n";
				display(p);												//displaying searched record
			}
		}
	}
	if (j == 0)
	{
		cout << "No record found!\n";
	}
	file.close();														//closing file
}

void updatephone (phone& p)												//function for updating record
{
	int i, fp, j = 0;													// i=phone's ID to be updated, fp=filepointer, j=variable for checking
	cout << "Here you can Update phone's record using it's ID!\n";		// whether record to be updated is found or not
	cout << "Enter ID for which you want to Update Phone: ";
	cin >> i;															// getting ID
	fstream file("data.bin", ios::in | ios::out | ios::binary);			//opening file in read, write and binary mode
	while (!file.eof())													//loop for checking end of file
	{
		fp = file.tellg();												//checking current position of file pointer
		file.read((char*)&p, sizeof(phone));							//reading data from file
		if (i == p.id)													//comparing current phone's ID and ID to be updated
		{
			addwhileupdate(p);											//updating the record
			file.seekp(fp);												//moving file pointer to desired location
			file.write((const char*)&p, sizeof(phone));					//writing to the file
			j++;														//incrementing when record is updated
			break;														//breaking the loop after updating record
		}
	}
	if (j == 0)
	{
		cout << "No record found to update associated with given ID!\n";
	}
	else
	{
		cout << "Record updated successfully!\n";
	}

	file.close();														//closing file
}

void deletephone(phone& p)												//function for deleting a particular phone's record from file 
{
	int i, j = 0;														// i=variable for getting ID, j=variable for checking delete operation
	cout << "Here you can Delete record of any phone by using it's ID!\n";
	cout << "Enter ID for which you want to Delete Phone: ";
	cin >> i;															//getitng ID
	fstream file("data.bin", ios::in | ios::binary);					//opening "data.bin" file in read mode
	fstream f("temp.bin", ios::out | ios::binary);						//opening temporary file in write mode
	if (file.is_open())													//check for opened file
	{
		while (!file.eof())												//loop for checking end of file
		{
			file.read((char*)&p, sizeof(phone));						//reading data from "data.bin" file
			if (p.id != i)												//checking that phone's ID is not equal to the ID which is
			{															//desired to be deleted
				if (file.gcount() > 0)									//checking whether bytes read are greater than zero or not
				{
					f.write((const char*)&p, sizeof(phone));			//writing data to temporary file
				}
			}
			else
			{
				j++;													//incrementing if no record is found
			}
		}
	}
	file.close();														//closing "data.bin" file
	remove("data.bin");													//deleting "data.bin"
	f.close();															//closing temporary file
	fstream file2 ("data.bin", ios::out | ios::binary);					//creating new "data.bin" file
	f.open("temp.bin", ios::in | ios::binary);							//opening temporary file in read mode
	if (f.is_open())													//checking whether temporary file is opened or not
	{
		f.seekg(0, ios::beg);											//moving the file pointer to the beginning
		while (!f.eof())												//loop for checking end of temporary file
		{
			f.read((char*)&p, sizeof(phone));							//reading data from temporary file
			if (f.gcount() > 0)											//checking whether bytes read are greater than zero or not
			{
				file2.write((const char*)&p, sizeof(phone));			//writing data to new "data.bin" file
			}
		}
	}
	file2.close();														//closing new "data.bin" file
	f.close();															//closing temporary file
	remove("temp.bin");													//deleting temporary file
	if (j)											
	{
		cout << "Record Deleted successfully!\n";
	}
	else
	{
		cout << "No record found to be deleted!\n";
	}
}

///////////////////////////////////////

int main()
{
	phone p;														//structure for keeping records
	int choice;														//variable for user's operation choice
	char ch;														//variable for number of time the operation is desired
	fstream file("data.bin", ios::in | ios::binary);				//opening file in read and binary mode
	if (file.is_open())												//checking whether file is opened or not
	{
		cout << "File opened successfully!\nDisplaying Data Of Mobile Phones:\n";
		while (!file.eof())											//loop for checking end of file
		{
			file.read((char*)&p, sizeof(p));						//reading data from the file
			if (file.gcount() > 0)									//checking whether bytes read are greater than zero or not
			{
				display(p);											//displaying data stored in file
			}
		}
	}
	else
	{
		file.open("data.bin", ios::app | ios::binary);				//creating file if it is not already available
		cout << "File created successfully!\n";
		cout << "You can perform differernt operations on File here!\n";
		do
		{
			cout << "\n\tSelect one of the following:\n";
			cout << "\t(1) ADD PHONE\n\t(2) SEARCH PHONE\n\t(3) UPDATE PHONE\n\t(4) DELETE PHONE\n\t(5) EXIT PROGRAM\n";
			cout << "Enter your choice: ";
			cin >> choice;								//asking for user's choice
			switch (choice)								//calling different functions through switch statement 
			{											//depending upon user's choice
				case 1: addphone(p); break;
				case 2: searchphone(p); break;
				case 3: updatephone(p); break;
				case 4: deletephone(p); break;
				case 5: exit(1);
				default: cout << "Wrong choice entered!\n";
			}
			cout << "Do you want to perform another operation? (Y/N): ";
			cin >> ch;									//asking user's chooice
		} while (ch == 'y' || ch == 'Y');				//terminating loop depending upon user's choice
	}
	file.close();										//closing file
	return 0;
}