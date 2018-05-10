// Class definitions
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>



class CALL
{
	friend class CALLDB;	
public: 
	CALL() {

	}
	// Getters
	string GetStart() const;
	string GetE164() const;
	int GetDuration() const;

	// Formatted Getters
	string GetFormattedStart() const;
	string GetCountryCode() const;
	string GetPhoneNumber() const;
private:
	// Private Members
	string start;
	string e164;
	int duration;
	
	// Setters
	void SetStart(string& unSetStart);
	void SetE164(string& unSetE164);
	void SetDuration(string& stringDuration);
};

// Validation Functions
bool TimeCheck(string& read);
bool NumberCheck(string& read);
bool DurationCheck(string& read);


const int MAXCALLS = 15;
class CALLDB
{
public:
	CALLDB() 
	{
		numCalls = 0;
	}// Initialize the # of records to 0 
	
	// Loads records from file into database. Return # of records that can't be added
	unsigned int Load(istream& fin);

	// Get count of call records
	unsigned int GetCountCalls() const;

	//Retrieve call record
	bool GetCall(unsigned int index, CALL& call) const;

	// Return first index >= of call w/ matching E164 prefix or -1
	int FindByE164Prefix(unsigned int startIndex, string prefix) const;

private:
	CALL callLog[MAXCALLS];		// Stores calls in database
	unsigned int numCalls; 		// Number of calls stored
};

