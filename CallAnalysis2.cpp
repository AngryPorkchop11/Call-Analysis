// Title: Lab 3 Call Analysis
//
// Purpose: Read through a data base of phone records from a file. The user can enter a prefix for a phone number and the program will display the appropriate phone numbers.
//
// Class: CSC 2430 Winter 2018
//
// Author: Mathew Lister

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <assert.h>
#include <stdlib.h>

using namespace std;

#include "CallDb2.h"
// Printing function
void print(CALLDB& calldb);
int main()
{
	CALLDB record;
	ifstream fin;
	string fileName;

// Opening the file
	cout << "File name: ";
	getline(cin, fileName);
	
	fin.open(fileName);
	if (fin.fail())
	{
		cerr << "Can't open \"" << fileName << "\"" << endl;
		exit(1);
	}
// Loading the call database and tracking failcount
	unsigned int dropped = record.Load(fin);
// Closing the file
	fin.close();
// Displaying how many records successfully added and how many dropped	cout << "Log successfully read into database, " << record.GetCountCalls() << " records added";
	if (dropped > 0)
	{
		cout << ", " << dropped << " records dropped" << endl;
	}
	cout << endl;
//Printing the records in the call database
	print(record);
		return 0;
}

// Function for printing
void print(CALLDB& calldb)
{
	CALL phoneCall;
	string query;
	string start;
	string country;
	string number;
	//unsigned int duration = 0;
	int index;
	int startFrom;
	int totalDuration = 0;
	
	// Printing the header
	cout << setw(25) << left << "Time";
	cout << setw(10) << left << "Country";
	cout << setw(20) << left << "Phone Number";
	cout << "Duration" << endl;
	// Getting the number of records in the database
	unsigned int count = calldb.GetCountCalls();
	// Printing out what is inside of the array
	for (unsigned int i = 0; i < count; i++)
	{
		calldb.GetCall(i, phoneCall);

		phoneCall.GetStart();
		phoneCall.GetE164();
		phoneCall.GetDuration();
		
		
		string start = phoneCall.GetFormattedStart();
		string country = phoneCall.GetCountryCode();
		string number = phoneCall.GetPhoneNumber();
		unsigned int duration = phoneCall.GetDuration();

		totalDuration += duration;

		cout << setw(25) << left << setfill(' ') << start;
		cout << setw(10) << left << setfill(' ') << country;
		cout << setw(20) << left << setfill(' ') << number;
		cout << duration / 60 << ":" << duration % 60 << endl;
	}
	cout << "Total duration of all calls: " << totalDuration / 60 << ":" << totalDuration % 60 << endl;
// Query on the data base
	
	cout << "E164 prefix for query: ";
	getline(cin, query);

	while (query != "")
	{
		
		index = 0;
		startFrom = 0;
		int totalQueryDuration = 0;
		bool flag = false;
		bool header = false;
		//int printCount = 0;
		for(unsigned int i = index; i < count; i++)
		{
			index = calldb.FindByE164Prefix(index, query);
			
			if (index != -1)
			{
				if (header == false)
				{
					cout << setw(25) << left << "Time";
					cout << setw(10) << left << "Country";
					cout << setw(20) << left << "Phone Number";
					cout << "Duration" << endl;
					header = true;
				}
				calldb.GetCall(index, phoneCall);

				string start = phoneCall.GetFormattedStart();
				string country = phoneCall.GetCountryCode();
				string number = phoneCall.GetPhoneNumber();
				unsigned int duration = phoneCall.GetDuration();

				cout << setw(25) << left << setfill(' ') << start;
				cout << setw(10) << left << setfill(' ') << country;
				cout << setw(20) << left << setfill(' ') << number;
				cout << duration / 60 << ":" << duration % 60 << endl;

				totalQueryDuration += duration;
				index++;
				flag = true;
				
			}
			
			else if (flag == false )
			{
				cout << "no records" << endl;
				break;
			}
			else if (flag == true && index == -1)
			{
				cout << "Total duration of all calls: " << totalQueryDuration / 60 << ":" << totalQueryDuration % 60 << endl;
				break;
			}
		}
		
		cout << "E164 prefix for query: ";
		getline(cin, query);
	}

}
// Need To Do:
// Update Comments
// Fix Query