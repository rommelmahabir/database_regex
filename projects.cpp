//  Base-10 Hashing
//  Chaining

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <regex>
#include "project.h"
#include "projects.h"
using namespace std;

int Projects::Hash(int key) {  // Base-10 Hashing function
  int pos = key * key;
	string spos = to_string(pos);
	int rDigits = (spos.size() - 1) / 2;
	spos.erase(spos.size() - rDigits, rDigits);
	int lDigits = spos.size() - 1;
	spos.erase(0, lDigits);
	return atoi(spos.c_str()) % 10;
}

void Projects::Input(string pros_file, string pros_name) {
	Project* temp;  // Initial variable creation for temporary objects
	int projId;
	int empId;
	string projName;
	string startDate;
	string endDate;
	double empTime;

	int pos;  // Initial variable creation for inserting objects

	ifstream proFile;  // Opens projects file
	proFile.open(pros_file);

	getline (proFile, key_type, '\n');  // Reads in the key type for the database
	proFile.ignore(256, '\n');

	while (proFile.peek()!=EOF) {
		proFile >> projId;  // Reads in variables for each object
		proFile.ignore();
		proFile >> empId;
		proFile.ignore();
		getline(proFile, projName, ',');
		getline(proFile, startDate, ',');
		getline(proFile, endDate, ',');
		proFile >> empTime;
		proFile.ignore();

		temp = new Project (projId, empId, projName, startDate, endDate, empTime);  // Creates temporary object

		if(key_type == "projId") {  // Calls hash function depending on key type
			pos = Hash(projId);
		}
		else if(key_type == "empId") {
			pos = Hash(empId);
		}
		else if(key_type == "projName") {
			pos = Hash(atoi(projName.c_str()));
		}
		else if(key_type == "startDate") {
			pos = Hash(atoi(startDate.c_str()));
		}
		else if(key_type == "endDate") {
			pos = Hash(atoi(endDate.c_str()));
		}
		else if(key_type == "empTime") {
			pos = Hash(empTime);
		}
		else {
			cout << "Key type not recognized.";
			return;
		}
		projectTable[pos].push_back(temp);  // Inserts object using Chaining
		cout << "Inserted (" << projId << "," << empId << "," << projName << "," << startDate << "," << endDate << setprecision(1) << fixed << empTime << ") into " << pros_name << endl;
	}

	proFile.close();
}

void Projects::Display(string pros_name) {  // Displays information for each project in a table
	cout << "------------------------ " << pros_name << " ------------------------" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "projId    empId     projName  startDate endDate   empTime" << endl;
	for (int i = 0; i < 10; ++i) {
		if (!projectTable[i].empty()) {
			for (int j = 0; j < projectTable[i].size(); ++j) {
				cout << left << setw(9) << projectTable[i][j]->GetProjId() << " " << setw(9) << projectTable[i][j]->GetEmpId() << " " << setw(9) << projectTable[i][j]->GetProjName() << " " << setw(9) << projectTable[i][j]->GetStartDate() << " " << setw(9) << projectTable[i][j]->GetEndDate() << " " << setprecision(1) << fixed << setw(9) << projectTable[i][j]->GetEmpTime() << endl;
			}
		}
	}
	cout << endl;
}

//INSERT
void Projects::Insert(string query, string pros_name){ //Inserts the information for the project table

	Project* temp;
	int projId;
	int empId;
	string projName;
	string startDate;
	string endDate;
	double empTime;
	int pos;

	smatch matcher;
	regex data("\\(\\((.*),(.*),(.*),(.*),(.*),(.*)\\).*\\)");
	regex_search(query, matcher, data);

	projId = stoi(matcher[1]);
	empId = stoi(matcher[2]);
	projName = matcher[3];
	startDate = matcher[4];
	endDate = matcher[5];
	empTime = stod(matcher[6]);
	
	

	temp = new Project (projId, empId, projName, startDate, endDate, empTime);

	if(key_type == "projId") {
		pos = Hash(projId);
	}
	else if(key_type == "empId") {
		pos = Hash(empId);
	}
	else if(key_type == "projName") {
		pos = Hash(atoi(projName.c_str()));
	}
	else if(key_type == "startDate") {
		pos = Hash(atoi(startDate.c_str()));
	}
	else if(key_type == "endDate") {
		pos = Hash(atoi(endDate.c_str()));
	}
	else if(key_type == "empTime") {
		pos = Hash(empTime);
	}
	else {
		cout << "Key type not recognized.";
		return;
	}
	for (int j = 0; j < projectTable[pos].size(); ++j) {
		if (projectTable[pos][j]->GetProjId() == projId) {
			cout << "Failed to insert (" << projId << "," << empId << "," << projName << "," << startDate << "," << endDate << "," << setprecision(1) << fixed << empTime << ") into " << pros_name << endl;
			return;
		}
	}

	projectTable[pos].push_back(temp);
	cout << "Inserted (" << projId << "," << empId << "," << projName << "," << startDate << "," << endDate << "," << setprecision(1) << fixed << empTime << ") into " << pros_name << endl;
}

//UPDATE
void Projects::Update(string query, string proj_name) { //Updates the information for the project table
	int projId;
	int empId;
	string projName;
	string startDate;
	string endDate;
	double empTime;
	int pos;
	int cont;

	smatch matcher;
	regex data("\\(\\((.*),(.*),(.*),(.*),(.*),(.*)\\).*\\)");
	regex_search(query, matcher, data);

	projId = stoi(matcher[1]);
	empId = stoi(matcher[2]);
	projName = matcher[3];
	startDate = matcher[4];
	endDate = matcher[5];
	empTime = stod(matcher[6]);

	if(key_type == "projId") {
		pos = Hash(projId);
	}
	else if(key_type == "empId") {
		pos = Hash(empId);
	}
	else if(key_type == "projName") {
		pos = Hash(atoi(projName.c_str()));
	}
	else if(key_type == "startDate") {
		pos = Hash(atoi(startDate.c_str()));
	}
	else if(key_type == "endDate") {
		pos = Hash(atoi(endDate.c_str()));
	}
	else if(key_type == "empTime") {
		pos = Hash(empTime);
	}
	else {
		cout << "Key type not recognized.";
		return;
	}

	if (!projectTable[pos].empty()) {
		for (int j = 0; j < projectTable[pos].size(); ++j) {
			if (projectTable[pos][j]->GetProjId() == projId) {
				//cout << left << setw(9) << projectTable[i][j]->GetProjId() << " " << setw(9) << projectTable[i][j]->GetEmpId() << " " << setw(9) << projectTable[i][j]->GetProjName() << " " << setw(9) << projectTable[i][j]->GetStartDate() << " " << setw(9) << projectTable[i][j]->GetEndDate() << " " << setprecision(1) << fixed << setw(9) << projectTable[i][j]->GetEmpTime() << endl;
				projectTable[pos][j]->SetProjId(projId);
				projectTable[pos][j]->SetEmpId(empId);
				projectTable[pos][j]->SetProjName(projName);
				projectTable[pos][j]->SetStartDate(startDate);
				projectTable[pos][j]->SetEndDate(endDate);
				projectTable[pos][j]->SetEmpTime(empTime);
				cout << "Updated (" << projId << "," << empId << "," << projName << "," << startDate << "," << endDate << "," << setprecision(1) << fixed << empTime << ") into " << proj_name << endl;
				return;
			}
		}
	}
	else {
		cout << "Failed to Update (" << projId << "," << empId << "," << projName << "," << startDate << "," << endDate << "," << setprecision(1) << fixed << empTime << ") into " << proj_name << endl;
	}
}

//SELECT
void Projects::Select(string query,string proj_name) { //Selects the information for the project table
	//SELECT((40,1,updatedDb,1/1/20,6/1/21,0.4),project)

	int searchNum = 0;
	int matches;
	bool matchFound = false;

	smatch matcher;
	regex data("\\(\\((.*),(.*),(.*),(.*),(.*),(.*)\\).*\\)");
	regex_search(query, matcher, data);

	for (int i=1; i<=6; i++) {
		if (matcher[i] != "*") {
			searchNum++;
		}
	}

	for (auto i = 0; i < 10; i++) {
		for (auto j = 0; j < projectTable[i].size(); j++) {
			matches = 0;
			if (matcher[1] != "*") {
				if (projectTable[i][j]->GetProjId() == stoi(matcher[1])) {
					matches++;
				}
			}
			if (matcher[2] != "*") {
				if (projectTable[i][j]->GetEmpId() == stoi(matcher[2])) {
					matches++;
				}
			}
			if (matcher[3] != "*") {
				if (projectTable[i][j]->GetProjName() == matcher[3]) {
					matches++;
				}
			}
			if (matcher[4] != "*") {
				if (projectTable[i][j]->GetStartDate() == matcher[4]) {
					matches++;
				}
			}
			if (matcher[5] != "*") {
				if (projectTable[i][j]->GetEndDate() == matcher[5]) {
					matches++;
				}
			}
			if (matcher[6] != "*") {
				if (projectTable[i][j]->GetEmpTime() == stod(matcher[6])) {
					matches++;
				}
			}
			if (matches == searchNum) {
				cout << "Found (" << projectTable[i][j]->GetProjId() << "," << projectTable[i][j]->GetEmpId() << "," << projectTable[i][j]->GetProjName() << "," << setprecision(0) << fixed <<
				projectTable[i][j]->GetStartDate() << "," << setprecision(2) << fixed << projectTable[i][j]->GetEndDate() << "," << projectTable[i][j]->GetEmpTime() << ") in " << proj_name << endl;
				matchFound = true;
			}
		}
	}

	smatch output;
	regex testLine("\\((.*)\\).*\\)");
	regex_search(query, output, testLine);

	if (!matchFound) {
		cout << "No entries match query " << output[1] << ") in " << proj_name << endl;
	}
}

//DELETE
void Projects::Delete(string query, string proj_name) { //Deletes the information for the project table
	int searchNum = 0;
	int matches;
	bool matchFound = false;

	smatch matcher;
	regex data("\\(\\((.*),(.*),(.*),(.*),(.*),(.*)\\).*\\)");
	regex_search(query, matcher, data);

	for (int i=1; i<=6; i++) {
		if (matcher[i] != "*") {
			searchNum++;
		}
	}

	for (auto i = 0; i < 10; i++) {
		for (auto j = 0; j < projectTable[i].size(); j++) {
			matches = 0;
			if (matcher[1] != "*") {
				if (projectTable[i][j]->GetProjId() == stoi(matcher[1])) {
					matches++;
				}
			}
			if (matcher[2] != "*") {
				if (projectTable[i][j]->GetEmpId() == stoi(matcher[2])) {
					matches++;
				}
			}
			if (matcher[3] != "*") {
				if (projectTable[i][j]->GetProjName() == matcher[3]) {
					matches++;
				}
			}
			if (matcher[4] != "*") {
				if (projectTable[i][j]->GetStartDate() == matcher[4]) {
					matches++;
				}
			}
			if (matcher[5] != "*") {
				if (projectTable[i][j]->GetEndDate() == matcher[5]) {
					matches++;
				}
			}
			if (matcher[6] != "*") {
				if (projectTable[i][j]->GetEmpTime() == stod(matcher[6])) {
					matches++;
				}
			}
			if (matches == searchNum) {
				cout << "Deleted (" << projectTable[i][j]->GetProjId() << "," << projectTable[i][j]->GetEmpId() << "," << projectTable[i][j]->GetProjName() << "," << setprecision(0) << fixed <<
				projectTable[i][j]->GetStartDate() << "," << setprecision(2) << fixed << projectTable[i][j]->GetEndDate() << "," << projectTable[i][j]->GetEmpTime() << ") in " << proj_name << endl;
				projectTable[i].erase(projectTable[i].begin()+j);
				matchFound = true;
			}
		}
	}

	smatch output;
	regex testLine("\\((.*)\\).*\\)");
	regex_search(query, output, testLine);

	if (!matchFound) {
		cout << "Failed to delete " << output[1] << ") in " << proj_name << endl;
	}
}

//WRITE
void Projects::Write() { ////Writes the information for the project table into a .csv file
  ofstream outFile("project_out.csv");

  outFile << key_type << endl;
  outFile << "projId    empId     projName  startDate endDate   empTime" << endl;
  for (int i = 0; i < 10; ++i) {
    if (!projectTable[i].empty()) {
      for (int j = 0; j < projectTable[i].size(); ++j) {
        outFile << left << setw(9) << projectTable[i][j]->GetProjId() << " " << setw(9) << projectTable[i][j]->GetEmpId() << " " << setw(9) << projectTable[i][j]->GetProjName() << " " << setw(9) << projectTable[i][j]->GetStartDate() << " " << setw(9) << projectTable[i][j]->GetEndDate() << " " << setprecision(1) << fixed << setw(9) << projectTable[i][j]->GetEmpTime() << endl;
      }
    }
  }
  outFile << endl;
}

void Projects::Cleanup() {
  for(auto it = projectTable.begin(); it != projectTable.end(); ++it) {
  		for(auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
  	     delete *it2; //deletes data from every object
  		}
  }
  projectTable.clear(); //clears database
}
