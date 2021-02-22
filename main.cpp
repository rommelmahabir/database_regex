//  CSCE 2110
//  Group 33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <regex>
#include "employee.h"
#include "employees.h"
#include "department.h"
#include "departments.h"
#include "project.h"
#include "projects.h"
using namespace std;

Employees employees;
Departments departments;
Projects projects;

int main() {
	string file_name;  // Initial variable creation for input file/table names
	string table_file;
        string table_name;
        vector<string> files;
        vector<string> names;
	string emps_name;
	string deps_name;
	string pros_name;
	string query;

	cout << "Please enter the main file’s name: ";  // Reads in the file name from the user
	getline(cin, file_name);

	ifstream mainFile;  // Opens the input file
	mainFile.open(file_name);

	if(!mainFile.is_open()) {  // Checks if file was properly opened
		cout << "INPUT FILE DOES NOT EXIST...... EXITING" << endl;
		return 0;
	}

	for(int i=0; i<3; ++i) {  // Reads in file and table names
		mainFile >> table_file;
		mainFile >> table_name;
		files.push_back(table_file);
		names.push_back(table_name);
	}

	for(int i=0; i<3; ++i) {  // Determines which file name corresponds to each database type
		cout << files[i] << " " << names[i] << endl;
                cout << "Processing " << names[i] << " table." << endl;
		if(names[i] == "employee") {  // Calls function the process input data from the employees file into the database
			employees.Input(files[i], names[i]);
			emps_name = names[i];
		}
		else if(names[i] == "department") {  // Calls function the process input data from the departments file into the database
			departments.Input(files[i], names[i]);
			deps_name = names[i];
		}
		else if(names[i] == "project") {  // Calls function the process input data from the projects file into the database
			projects.Input(files[i], names[i]);
			pros_name = names[i];
		}
	}

	cout << endl;

		// QUERIES

	while(mainFile.peek()!=EOF) {
		mainFile >> query;

		// DISPLAY
		if(regex_match(query, regex("(DISPLAY)(.*)"))) {
			cout << "DISPLAY" << endl;
			employees.Display(emps_name);
			departments.Display(deps_name);
			projects.Display(pros_name);
		}

		// INSERT
		else if(regex_match(query, regex("(INSERT)(.*)"))) {
			//Employees
			if (regex_match(query, regex(".*employee.*"))) {
				employees.Insert(query, emps_name);
			}
			//Departments
			else if (regex_match(query, regex(".*department.*"))) {
				departments.Insert(query, deps_name);
			}
			//Projects
			else if (regex_match(query, regex(".*project.*"))) {
				projects.Insert(query, pros_name);
			}
		}
		// UPDATE
		else if(regex_match(query, regex("(UPDATE)(.*)"))) {
			//Employees
			if (regex_match(query, regex(".*employee.*"))) {
				employees.Update(query, emps_name);
			}
			//Departments
			else if (regex_match(query, regex(".*department.*"))) {
				departments.Update(query, deps_name);
			}
			//Projects
			else if (regex_match(query, regex(".*project.*"))) {
				projects.Update(query, pros_name);
			}
		}

		// SELECT
		else if(regex_match(query, regex("(SELECT)(.*)"))) {
			//Employees
			if (regex_match(query, regex(".*employee.*"))) {
				employees.Select(query, emps_name);
			}
			//Departments
			else if (regex_match(query, regex(".*department.*"))) {
				departments.Select(query, deps_name);
			}
			//Projects
			else if (regex_match(query, regex(".*project.*"))) {
				projects.Select(query, pros_name);
			}
		}

		// DELETE
		else if(regex_match(query, regex("(DELETE)(.*)"))) {
			//Employees
			if (regex_match(query, regex(".*employee.*"))) {
				employees.Delete(query, emps_name);
			}
			//Departments
			else if (regex_match(query, regex(".*department.*"))) {
				departments.Delete(query, deps_name);
			}
			//Projects
			else if (regex_match(query, regex(".*project.*"))) {
				projects.Delete(query, pros_name);
			}
		}

		// WRITE
		else if(regex_match(query, regex("(WRITE)(.*)"))) {
			cout << "WRITE" << endl;
			//Employees
			employees.Write();
			//Departments
			departments.Write();
			//Projects
			projects.Write();
		}
	}

	cout << endl;
	cout << "Processing Complete!" << endl;

	mainFile.close();

	employees.Cleanup();  // Calls cleanup functions for each database
	departments.Cleanup();
	projects.Cleanup();

	return 0;
}
