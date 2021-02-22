//  Base-2 Hashing
//  Linear Collision

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <regex>
#include "department.h"
#include "departments.h"
using namespace std;

int Departments::Hash(int key) {  // Base-2 Hashing function
	int pos = key * key;
	int lbits = (32 - 4) / 2;
	int ebits = pos >> lbits;
	ebits = ebits & (0xFFFFFFFF >> (32 - 4));
	return ebits % 10;
}

void Departments::Input(string deps_file, string deps_name) {
	for(int i = 0; i<10; ++i) {  // Fills hash table with empty objects
        departmentTable[i] = new Department(-1,"none","none",-1,-1);
    }

	Department* temp;  // Initial variable creation for temporary objects
	int departId;
	string name;
	string location;
	int mgrId;
	int admrDepartId;

	int pos;  // Initial variable creation for inserting objects
	int cont;

	ifstream depFile;  // Opens departments file
	depFile.open (deps_file);

	getline(depFile, key_type, '\n');  // Reads in the key type for the database
	depFile.ignore(256, '\n');

	while (depFile.peek()!=EOF) {
		depFile >> departId;  // Reads in variables for each object
		depFile.ignore();
		getline(depFile, name, ',');
		getline(depFile, location, ',');
		depFile >> mgrId;
		depFile.ignore();
		depFile >> admrDepartId;
		depFile.ignore();

		temp = new Department(departId, name, location, mgrId, admrDepartId);  // Creates temporary object

		if(key_type == "departId") {  // Calls hash function depending on key type
			pos = Hash(departId);
		}
		else if(key_type == "name") {
			pos = Hash(atoi(name.c_str()));
		}
		else if(key_type == "location") {
			pos = Hash(atoi(location.c_str()));
		}
		else if(key_type == "mgrId") {
			pos = Hash(mgrId);
		}
		else if(key_type == "admrDepartId") {
			pos = Hash(admrDepartId);
		}
		else {
			cout << "Key type not recognized.";
			return;
		}
		cont = 0;
		while (cont == 0) {  // Inserts object using Linear Collision
			if (departmentTable[pos]->empty_ss) {
				departmentTable[pos] = temp;
				departmentTable[pos]->empty_ss = false;
				cout << "Inserted (" << departId << "," << name << "," << location << "," << mgrId << "," << admrDepartId << ") into " << deps_name << endl;
				cont = 1;
			}
			pos = (pos + 1) % 10;
		}
	}

	depFile.close();
}

void Departments::Display(string deps_name) {  // Displays information for every department in a table
	cout << "---------------------------------- " << deps_name << " ----------------------------------" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "departId         name             location         mgrId            admrDepartId" << endl;
	for (int i = 0; i < 10; ++i) {
		if (!departmentTable[i]->empty_ss && !departmentTable[i]->empty_ar) {
			cout << left << setw(16) << departmentTable[i]->GetDepartId() << " " << setw(16) << departmentTable[i]->GetName() << " " << setw(16) << departmentTable[i]->GetLocation() << " " << setw(16) << departmentTable[i]->GetMgrId() << " " << setw(16) << departmentTable[i]->GetAdmrDepartId() << endl;
		}
	}
	cout << endl;
}

//INSERT
void Departments::Insert(string query, string deps_name){

  Department* temp;//Variables are declared
  int departId;
  string name;
  string location;
  int mgrId;
  int admrDepartId;

  int pos;
  int cont;
  int probed;

  smatch matcher;
  regex data("\\(\\((.*),(.*),(.*),(.*),(.*)\\).*\\)");
  regex_search(query, matcher, data);

  departId = stoi(matcher[1]);
  name = matcher[2];
  location = matcher[3];
  mgrId = stod(matcher[4]);
  admrDepartId = stod(matcher[5]);
  
  for (int i=0; i<10; i++) {
		if (departId == departmentTable[i]->GetDepartId()) {
			cout << "Failed to insert (" << departId << "," << name << "," << location << "," << mgrId << "," << admrDepartId << ") into " << deps_name << endl;
			return;
		}
	}

  temp = new Department(departId, name, location, mgrId, admrDepartId);

  if(key_type == "departId") { //Checks key type
    pos = Hash(departId);
  }
  else if(key_type == "name") {
    pos = Hash(atoi(name.c_str()));
  }
  else if(key_type == "location") {
    pos = Hash(atoi(location.c_str()));
  }
  else if(key_type == "mgrId") {
    pos = Hash(mgrId);
  }
  else if(key_type == "admrDepartId") {
    pos = Hash(admrDepartId);
  }
  else {
    cout << "Key type not recognized.";
    return;
  }
  cont = 0;
  probed = 0;
  while (cont == 0) {
    if (departmentTable[pos]->empty_ss) {//If index is empty, info is inserted
      departmentTable[pos] = temp;
      departmentTable[pos]->empty_ss = false;
      cout << "Inserted (" << departId << "," << name << "," << location << "," << mgrId << "," << admrDepartId << ") into " << deps_name << endl;
      cont = 1;
    }
    pos = (pos + 1) % 10;
	probed++;
	if (probed == 10) {
		cout << "Failed to insert (" << departId << "," << name << "," << location << "," << mgrId << "," << admrDepartId << ") into " << deps_name << endl;
		cont = 1;
	}
  }

}

//UPDATE
void Departments::Update(string query, string deps_name){

  int departId;//Variables are declared
  string name;
  string location;
  int mgrId;
  int admrDepartId;

  int pos;
  int probed;

  smatch matcher;
  regex data("\\(\\((.*),(.*),(.*),(.*),(.*)\\).*\\)");
  regex_search(query, matcher, data);

  departId = stoi(matcher[1]);//Assigns values from query into temp vars
  name = matcher[2];
  location = matcher[3];
  mgrId = stod(matcher[4]);
  admrDepartId = stod(matcher[5]);

  if(key_type == "departId") {//checks key type
    pos = Hash(departId);
  }
  else if(key_type == "name") {
    pos = Hash(atoi(name.c_str()));
  }
  else if(key_type == "location") {
    pos = Hash(atoi(location.c_str()));
  }
  else if(key_type == "mgrId") {
    pos = Hash(mgrId);
  }
  else if(key_type == "admrDepartId") {
    pos = Hash(admrDepartId);
  }
  else {
    cout << "Key type not recognized.";
    return;
  }
  probed = 0;
  while (probed != 10) {
    if(!departmentTable[pos]->empty_ss && !departmentTable[pos]->empty_ar){
      if(departmentTable[pos]->GetDepartId() == departId){//if key value matches, then values are updated
        departmentTable[pos]->SetDepartId(departId);
        departmentTable[pos]->SetName(name);
        departmentTable[pos]->SetLocation(location);
        departmentTable[pos]->SetMgrId(mgrId);
        departmentTable[pos]->SetAdmrDepartId(admrDepartId);
        cout << "Updated (" << departId << "," << name << "," << location << "," << mgrId << "," << admrDepartId << ") into " << deps_name << endl;
        return;
      }
      else if(departmentTable[pos]->GetDepartId() != departId){
        pos = (pos + 1) % 10;
		probed++;
      }
    }
	else {
		pos = (pos + 1) % 10;
		probed++;
	}
    
  }
  cout << "Failed to Update (" << departId << "," << name << "," << location << "," << mgrId << "," << admrDepartId << ") into " << deps_name << endl;

}

//SELECT
void Departments::Select(string query, string deps_name){

  int searchNum = 0;
  int matches;
  bool matchFound = false;

  smatch matcher;
  regex data("\\(\\((.*),(.*),(.*),(.*),(.*)\\).*\\)");
  regex_search(query, matcher, data);

  for (int i=1; i<=5; i++) {
    if (matcher[i] != "*") {
      searchNum++;
    }
  }
  for (int i=0; i<10; i++) {//matches with query
    matches = 0;
    if (matcher[1] != "*") {//finds total number of matches needed to find a match
      if (departmentTable[i]->GetDepartId() == stoi (matcher[1])) {
        matches++;
      }
    }
    if (matcher[2] != "*") {
      if (departmentTable[i]->GetName() == matcher[2]) {
        matches++;
      }
    }
    if (matcher[3] != "*") {
      if (departmentTable[i]->GetLocation() == matcher[3]) {
        matches++;
      }
    }
    if (matcher[4] != "*") {
      if (departmentTable[i]->GetMgrId() == stod (matcher[4])) {
        matches++;
      }
    }
    if (matcher[5] != "*") {
      if (departmentTable[i]->GetAdmrDepartId() == stod (matcher[5])) {
        matches++;
      }
    }
  	if (!departmentTable[i]->empty_ss && !departmentTable[i]->empty_ar) {
  		if (matches == searchNum) {
  		  cout << "Found (" << departmentTable[i]->GetDepartId() << "," << departmentTable[i]->GetName() << "," << departmentTable[i]->GetLocation() << "," <<
  		  departmentTable[i]->GetMgrId() << "," << departmentTable[i]->GetAdmrDepartId() << ") in " << deps_name << endl;
  		  matchFound = true;
  		}
  	}
  }

  smatch output;
  regex testLine("\\((.*)\\).*\\)");
  regex_search(query, output, testLine);

  if (!matchFound) {
    cout << "No entries match query " << output[1] << ") in " << deps_name << endl;
  }

}

//DELETE
void Departments::Delete(string query, string deps_name) {
  int searchNum = 0;
  int matches;
  bool matchFound = false;

  smatch matcher;
  regex data("\\(\\((.*),(.*),(.*),(.*),(.*)\\).*\\)");
  regex_search(query, matcher, data);

  for (int i=1; i<=5; i++) {
    if (matcher[i] != "*") {
      searchNum++;
    }
  }
  for (int i=0; i<10; i++) {
    matches = 0;
    if (matcher[1] != "*") {
      if (departmentTable[i]->GetDepartId() == stoi (matcher[1])) {
        matches++;
      }
    }
    if (matcher[2] != "*") {
      if (departmentTable[i]->GetName() == matcher[2]) {
        matches++;
      }
    }
    if (matcher[3] != "*") {
      if (departmentTable[i]->GetLocation() == matcher[3]) {
        matches++;
      }
    }
    if (matcher[4] != "*") {
      if (departmentTable[i]->GetMgrId() == stod (matcher[4])) {
        matches++;
      }
    }
    if (matcher[5] != "*") {
      if (departmentTable[i]->GetAdmrDepartId() == stod (matcher[5])) {
        matches++;
      }
    }
  	if (!departmentTable[i]->empty_ss && !departmentTable[i]->empty_ar) {
  		if (matches == searchNum) {
  		  cout << "Deleted (" << departmentTable[i]->GetDepartId() << "," << departmentTable[i]->GetName() << "," << departmentTable[i]->GetLocation() << "," <<
  		  departmentTable[i]->GetMgrId() << "," << departmentTable[i]->GetAdmrDepartId() << ") in " << deps_name << endl;
		  departmentTable[i]->empty_ar = true;
		  departmentTable[i]->empty_ss = false;
  		  matchFound = true;
  		}
  	}
  }

  smatch output;
  regex testLine("\\((.*)\\).*\\)");
  regex_search(query, output, testLine);

  if (!matchFound) {
    cout << "Failed to delete " << output[1] << ") in " << deps_name << endl;
  }
}

//WRITE
void Departments::Write() {
  ofstream outFile("department_out.csv");

  outFile << key_type << endl;
  outFile << "departId         name             location         mgrId            admrDepartId" << endl;
	for (int i = 0; i < 10; ++i) {
		if (!departmentTable[i]->empty_ss && !departmentTable[i]->empty_ar) {
			outFile << left << setw(16) << departmentTable[i]->GetDepartId() << " " << setw(16) << departmentTable[i]->GetName() << " " << setw(16) << departmentTable[i]->GetLocation() << " " << setw(16) << departmentTable[i]->GetMgrId() << " " << setw(16) << departmentTable[i]->GetAdmrDepartId() << endl;
		}
	}
	outFile << endl;
}

void Departments::Cleanup() {
        for(auto it = departmentTable.begin(); it != departmentTable.end(); ++it) {
                delete *it; //deletes data from every object
        }
        departmentTable.clear(); //clears database

}
