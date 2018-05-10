#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <assert.h>

using namespace std;

#include "CallDb2.h"
// Validation functions
// This functions purpose is to check for a string that is exactly 14 characters long. If it can't find one it will fail the function and give the user an error message. If the function is able to find the right string it will formatt it and set it under the time header.
bool TimeCheck(string& read)
{
	bool timeCondition;
	if (read.length() == 14)
	{
		timeCondition = true;
	}
	else
	{
		timeCondition = false;
	}

	return timeCondition;
}

// This functions purpose is to check for a string that is exactly 12 characters long. If it can't find one it will fail the function and give the user an error message. If the function is able to find the right string it will formatt it and set it under the time header.
bool NumberCheck(string& read)
{
	bool numberCondition;
	string america = "+1";
	string france = "+33";
	string hongKong = "+852";

	if (read.length() == 12)
	{
		numberCondition = true;
	}
	else if (read.substr(0, 2) == america)
	{
		numberCondition = true;
	}
	else if (read.substr(0, 3) == france)
	{
		numberCondition = true;
	}
	else if (read.substr(0, 4) == hongKong)
	{
		numberCondition = true;
	}
	else
	{
		numberCondition = false;
	}

	return numberCondition;
}

// This funcations purpose is to varify that the duration of the call has at least 1 character and no more than 10.
bool DurationCheck(string& read)
{
	int pos = read.find_first_not_of("0123456789");
	if (pos == -1)
	{
		return true;
	}
	return false;
}
//******************************************************************************************************************************************************************************************
// Getters
string CALL::GetStart() const
{
	return start;
}

string CALL::GetE164() const
{
	return e164;
}

int CALL::GetDuration() const
{
	return duration;
}
//******************************************************************************************************************************************************************************************
// Formatted Getters
// Get formatted start time of call
string CALL::GetFormattedStart() const
{
	string formattedStart = start.substr(4, 2) + "-" + start.substr(6, 2) + "-" + start.substr(0, 4) + " " + start.substr(8, 2) + ":" + start.substr(10, 2) + ":" + start.substr(12, 2);
	return formattedStart;
}

// Get country code of call
string CALL::GetCountryCode() const
{
	string formatCountry;
	string america = "+1";
	string france = "+33";
	string hongKong = "+852";

	if (america == e164.substr(0, 2))
	{
		formatCountry = e164.substr(1, 1);
	}
	if (france == e164.substr(0, 3))
	{
		formatCountry = e164.substr(1, 2);
	}
	if (hongKong == e164.substr(0, 4))
	{
		formatCountry = e164.substr(1, 3);
	}
	return formatCountry;
}

// Get phone number of call
string CALL::GetPhoneNumber() const
{
	string local;
	string america("+1");
	string france = "+33";
	string hongKong = "+852";

	if (america == e164.substr(0, 2))
	{
		local = "(" + e164.substr(2, 3) + ")-" + e164.substr(5, 3) + "-" + e164.substr(8, 4);
	}
	if (france == e164.substr(0, 3))
	{
		local = "0" + e164.substr(3, 1) + " " + e164.substr(4, 2) + " " + e164.substr(6, 2) + " " + e164.substr(8, 2) + " " + e164.substr(10, 2);
	}
	if (hongKong == e164.substr(0, 4))
	{
		local = e164.substr(4, 4) + " " + e164.substr(8, 4);
	}
	return local;
}
 //******************************************************************************************************************************************************************************************
 // Setters
void CALL::SetStart(string& unSetStart)
{
	assert(TimeCheck(unSetStart));
	start = unSetStart;	
}

void CALL::SetE164(string& unSetE164)
{
	assert(NumberCheck(unSetE164));
	e164 = unSetE164;
}

 void CALL::SetDuration(string& stringDuration)
 {
	 assert(DurationCheck(stringDuration));
	 duration = stoi(stringDuration);
 }
 //******************************************************************************************************************************************************************************************
// Load database with calls stored in a file
unsigned int CALLDB::Load(istream& fin)
{
	unsigned int failCount = 0;
	string readStart;
	string readE164;
	string readDuration;

	fin >> readStart >> readE164 >> readDuration;
	while (!fin.eof())
	{
		
		if (TimeCheck(readStart) == true && NumberCheck(readE164) == true && DurationCheck(readDuration) == true && numCalls < MAXCALLS)
		{
			callLog[numCalls].SetStart(readStart);
			callLog[numCalls].SetE164(readE164);
			callLog[numCalls].SetDuration(readDuration);
			numCalls++;
		}
		else
		{
			failCount++;
		}
		fin >> readStart >> readE164 >> readDuration;
	}

	return failCount;
}
// Get count of call records
unsigned int CALLDB::GetCountCalls() const
{
	//cout << endl << "calldb.numCalls = " << calldb.numCalls << endl << endl;
	return numCalls;
}
// Retrieve call records
bool CALLDB::GetCall( unsigned int index, CALL& call) const
{
	bool condition;

	if (index < numCalls)
	{
		condition = true;
		call = callLog[index];
	}
	else
	{
		condition = false;
	}
	return condition;
}
// Return first index >= of call w/ matching E164 prefix, or -1
int CALLDB::FindByE164Prefix(unsigned int startIndex, string prefix) const
{
	int condition = -1;
	CALL search;
	for (int i = startIndex; i < MAXCALLS; i++)
	{
		GetCall(i, search);
		if (search.e164.substr(0, prefix.length()) == prefix)
		{
			condition = i;
			return condition;
		}
	}
	return condition;
}