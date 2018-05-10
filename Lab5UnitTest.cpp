//// Title: Lab 5 Call Database Unit Test - Lab5UnitTest.cpp
////
//// Purpose: Runs validation tests on the call database component for Lab 5.
//// 
//// Class: CSC 2430 Winter 2018
////
//// Author: Max Benson
//
//#include <iostream>
//#include <sstream>
//#include <string>
//#include <assert.h>
//
//using namespace std;
//
//#include "CallDb2.h"
//
//int main()
//{
//	CALLDB calldb;
//	CALL call;
//	stringstream inbuffer1;
//	stringstream inbuffer2;
//	stringstream inbuffer3;
//	stringstream inbuffer4;
//	string expected;
//
//	// Check totally empty call database
//	assert(calldb.Load(inbuffer1) == 0);
//	assert(calldb.GetCountCalls() == 0);
//	assert(!calldb.GetCall(0, call));
//	assert(calldb.FindByE164Prefix(0, "+") == -1);
//
//	// Empty file
//	inbuffer1.str("");
//	assert(calldb.Load(inbuffer1) == 0);
//	assert(calldb.GetCountCalls() == 0);
//	assert(!calldb.GetCall(0, call));
//	assert(calldb.FindByE164Prefix(0, "+") == -1);
//
//	// Load some calls
//	inbuffer2.str("20180105110054 +12062812000 5912\n"
//		"20180105110054 +12062812000 xxxx\n"
//		"20171210091233 +33140205990 364\n"
//		"20171129145316 +85223677065 180\n");
//	assert(calldb.Load(inbuffer2) == 1);
//	assert(calldb.GetCountCalls() == 3);
//	assert(calldb.GetCall(0, call));
//	assert(call.GetStart() == "20180105110054");
//	assert(call.GetE164() == "+12062812000");
//	assert(call.GetDuration() == 5912);
//	assert(call.GetFormattedStart() == "01-05-2018 11:00:54");
//	assert(call.GetCountryCode() == "1");
//	assert(call.GetPhoneNumber() == "(206)-281-2000");
//	assert(calldb.GetCall(1, call));
//	assert(call.GetStart() == "20171210091233");
//	assert(call.GetE164() == "+33140205990");
//	assert(call.GetDuration() == 364);
//	assert(call.GetFormattedStart() == "12-10-2017 09:12:33");
//	assert(call.GetCountryCode() == "33");
//	assert(call.GetPhoneNumber() == "01 40 20 59 90");
//	assert(calldb.GetCall(2, call));
//	assert(call.GetStart() == "20171129145316");
//	assert(call.GetE164() == "+85223677065");
//	assert(call.GetDuration() == 180);
//	assert(call.GetFormattedStart() == "11-29-2017 14:53:16");
//	assert(call.GetCountryCode() == "852");
//	assert(call.GetPhoneNumber() == "2367 7065");
//	assert(!calldb.GetCall(3, call));
//	assert(calldb.FindByE164Prefix(0, "") == 0);
//	assert(calldb.FindByE164Prefix(0, "+1") == 0);
//	assert(calldb.FindByE164Prefix(1, "+1") == -1);
//	assert(calldb.FindByE164Prefix(0, "+33") == 1);
//	assert(calldb.FindByE164Prefix(0, "+8") == 2);
//	assert(calldb.FindByE164Prefix(0, "+9") == -1);
//
//	// Load some more calls
//	inbuffer3.str("20180105110054 +12062812000 5912\n"
//		"20171210091233 +33140205990 364\n"
//		"20171129145316 +85223677065 180\n");
//	assert(calldb.Load(inbuffer3) == 0);
//	assert(calldb.GetCountCalls() == 6);
//	assert(calldb.GetCall(3, call));
//	assert(call.GetStart() == "20180105110054");
//	assert(call.GetE164() == "+12062812000");
//	assert(call.GetDuration() == 5912);
//	assert(calldb.GetCall(4, call));
//	assert(call.GetStart() == "20171210091233");
//	assert(call.GetE164() == "+33140205990");
//	assert(call.GetDuration() == 364);
//	assert(calldb.GetCall(5, call));
//	assert(call.GetStart() == "20171129145316");
//	assert(call.GetE164() == "+85223677065");
//	assert(call.GetDuration() == 180);
//	assert(!calldb.GetCall(6, call));
//	assert(calldb.FindByE164Prefix(0, "+1") == 0);
//	assert(calldb.FindByE164Prefix(1, "+1") == 3);
//	assert(calldb.FindByE164Prefix(4, "+1") == -1);
//
//	// Load some more calls
//	inbuffer4.str("20180105110054 +12062812000 5912\n"
//		"20171210091233 +33140205990 364\n"
//		"20171129145316 +85223677065 180\n"
//		"20171210091233 +33140205990 364\n"
//		"20171129145316 +85223677065 180\n"
//		"20171210091233 +33140205990 364\n"
//		"20171129145316 +85223677065 180\n"
//		"20171210091233 +33140205990 364\n"
//		"20171129145316 +85223677065 180\n"
//		"20171210091233 +33140205990 364\n"
//		"20171129145316 +85223677065 180\n");
//	assert(calldb.Load(inbuffer4) == 2);
//	assert(calldb.GetCountCalls() == 15);
//
//	// Congratulate 
//	cerr << "Good work, you passed the unit tests." << endl;
//
//    return 0;
//}
