#pragma once
#include "transportation.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
bool expectedInformation(const Vehicle v1, string& issuesFeildInitialization);
//testing class Vehicle
bool testingVehicle() {   
	bool allGood = true;
	Vehicle v1(1234, "Honda", "Pilot", 6, true, 4, new string[4]{ "AC","DVD","GPS" ,"Sunroof" });
	bool initialization = true;
	string issuesFeildInitialization = "";

	//testing constructor
	if (!expectedInformation(v1, issuesFeildInitialization)) {
		cout << "Initialization Process: Failed!" << endl;
		cout << "You have problems in the following fields: " << issuesFeildInitialization << ".\n";
		allGood = false;
	}
	issuesFeildInitialization = "";
	
	{ //test for copy constructor
		Vehicle myCopyVehicle(v1);
		if (expectedInformation(myCopyVehicle, issuesFeildInitialization)) {
			cout << "Copy Constructor, test 1:....... Passed!\n";
		}
		else
		{
			cout << "Copy Constructor is not properly working, Test 1:....... Failed!\n";
			cout << "You have problems in the following fields: " << issuesFeildInitialization << ".\n";
			allGood = false;
		}
		cout << "Printing  myCopyVehicle" << endl;
		cout << myCopyVehicle << endl;

	}

	issuesFeildInitialization = "";
	cout << "\n Testing the original Vehicle object v1, after erasing the local object" << endl;
	if (expectedInformation(v1, issuesFeildInitialization)) {
		cout << "Copy Constructor, test 2:....... Passed!\n";
	}
	else
	{
		cout << "Copy Constructor is not properly working, Test 2:....... Failed!\n";
		cout << "You have problems in the following fields: " << issuesFeildInitialization << ".\n";
		allGood = false;
	}
	cout << "Printing  v1" << endl;
	cout << v1 << endl;

	issuesFeildInitialization = "";

	{ //test for assignment overloading
		Vehicle v2(2222, "Jeep", "Cherokee", 5, true, 7, new string[7]{ "AC","DVD","GPS" ,"Sunroof","911", "Interent","USB-C"  });
		
		cout << "Printing  v2 before the assignment" << endl;
		cout << v2 << endl;

		v2 = v1;
		if (expectedInformation(v2, issuesFeildInitialization)) {
			cout << "Assignment overloading , test 1:....... Passed!\n";
		}
		else
		{
			cout << "Assignment overloading is not properly working, Test 1:....... Failed!\n";
			cout << "You have problems in the following fields: " << issuesFeildInitialization << ".\n";
			allGood = false;
		}
		cout << "Printing  v2 after the assignment" << endl;
		cout << v2 << endl;

	}

	issuesFeildInitialization = "";
	cout << "\n Testing the original Vehicle object v1, after erasing the local object" << endl;
	if (expectedInformation(v1, issuesFeildInitialization)) {
		cout << "Assignment overloading , test 2:....... Passed!\n";
	}
	else
	{
		cout << "Assignment overloading  is not properly working, Test 2:....... Failed!\n";
		cout << "You have problems in the following fields: " << issuesFeildInitialization << ".\n";
		allGood = false;
	}
	cout << "Printing  v1" << endl;
	cout << v1 << endl;
	return allGood;
}

bool expectedInformation(const Vehicle v1, string& issuesFeildInitialization) {
	bool initialization = true;

	if (!(v1.getID() == 1234)) {
		initialization = false;
		issuesFeildInitialization.append(", vehicleID");
	}
	if (!(v1.getmake() == "Honda")) {
		initialization = false;
		issuesFeildInitialization.append(", make");
	}
	if (!(v1.getmodel() == "Pilot")) {
		initialization = false;
		issuesFeildInitialization.append(", model");
	}
	if (!v1.status()) {
		initialization = false;
		issuesFeildInitialization.append("available");
	}
	if (!(v1.getSeats() == 6)) {
		initialization = false;
		issuesFeildInitialization.append(", seats");
	}
	if (!(v1.getextarFeatures() == 4)) {
		initialization = false;
		issuesFeildInitialization.append(", extarFeatures");
	}
	bool sameFeatures = true;

	string* featuresList = v1.getFeaturesList();
	//,, ,
	if (!(featuresList[0] == "AC" && featuresList[1] == "DVD" && featuresList[2] == "GPS" && featuresList[3] == "Sunroof")) {
		initialization = false;
		issuesFeildInitialization.append(", otherFeaturesList");
	}

	return initialization;
}