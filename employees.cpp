//  Modulo Hashing
//  Quadratic Collision

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <regex>
#include "employee.h"
#include "employees.h"
using namespace std;

int Employees::Hash(int key) {  // Modulo Hashing function
	return key % 10;
}

void Employees::Input(string emps_file, string emps_name) {
	for(int i = 0; i<10; ++i) {  // Fills hash table with empty objects
		employeeTable[i] = new Employee(-1,"none","none",-1,-1,"none","none",-1);
	}

	Employee* temp;  // Initial variable creation for temporary objects
	int empId;
	string firstName;
	string lastName;
	double phone;
	double salary;
	string job;
	string email;
	int departId;

	int pos;  // Initial variable creation for inserting objects
	int origPos;
	int probed;
	int cont;

	ifstream empFile;  // Opens employees file
	empFile.open(emps_file);

	getline(empFile, key_type, '\n');  // Reads in the key type for the database
	empFile.ignore(256, '\n');

	while(empFile.peek()!=EOF) {
		empFile >> empId;  // Reads in variables for each object
		empFile.ignore();
		getline(empFile, firstName, ',');
		getline(empFile, lastName, ',');
		empFile >> phone;
		empFile.ignore();
		empFile >> salary;
		empFile.ignore();
		getline(empFile, job, ',');
		getline(empFile, email, ',');
		empFile >> departId;
		empFile.ignore();

		temp = new Employee(empId, firstName, lastName, phone, salary, job, email, departId);  // Creates temporary object

		if(key_type == "empId") {  // Calls hash function depending on key type
			pos = Hash(empId);
			origPos = Hash(empId);
		}
		else if(key_type == "firstName") {
			pos = Hash(atoi(firstName.c_str()));
			origPos = Hash(atoi(firstName.c_str()));
		}
		else if(key_type == "lastName") {
			pos = Hash(atoi(lastName.c_str()));
			origPos = Hash(atoi(lastName.c_str()));
		}
		else if(key_type == "phone") {
			pos = Hash(phone);
			origPos = Hash(phone);
		}
		else if(key_type == "salary") {
			pos = Hash(salary);
			origPos = Hash(salary);
		}
		else if(key_type == "job") {
			pos = Hash(atoi(job.c_str()));
			origPos = Hash(atoi(job.c_str()));
		}
		else if(key_type == "email") {
			pos = Hash(atoi(email.c_str()));
			origPos = Hash(atoi(email.c_str()));
		}
		else if(key_type == "departId") {
			pos = Hash(departId);
			origPos = Hash(departId);
		}
		else {
			cout << "Key type not recognized.";
			return;
		}
		probed = 0;
		cont = 0;
		while (cont == 0) {  // Inserts object using Quadratic Collision
			if(employeeTable[pos]->empty_ss) {
				employeeTable[pos] = temp;
				employeeTable[pos]->empty_ss = false;
				cout << "Inserted (" << empId << "," << firstName << "," << lastName << "," << setprecision(0) << fixed << phone << "," << setprecision(2) << fixed << salary << "," << job << "," << email << "," << setprecision(0) << departId << ") into " << emps_name << endl;
				cont = 1;
			}
			probed++;
			pos = (origPos + 1 * probed + 1 * (probed * probed)) % 10;
		}
	}

	empFile.close();
}

void Employees::Display(string emps_name) {  // Displays information for every employee in a table
	cout << "------------------------------------------------------------------- " << emps_name << " -------------------------------------------------------------------" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "empId               firstName           lastName            phone               salary              job                 email               departId" << endl;
	for (int i = 0; i < 10; ++i) {
		if (!employeeTable[i]->empty_ss && !employeeTable[i]->empty_ar) {
			cout << left << setw(19) << employeeTable[i]->GetEmpId() << " " << setw(19) << employeeTable[i]->GetFirstName() << " " << setw(19) << employeeTable[i]->GetLastName() << " " << setprecision(0) << fixed << setw(19) << employeeTable[i]->GetPhone() << " " << setprecision(2) << fixed << setw(19) << employeeTable[i]->GetSalary() << " " << setw(19) << employeeTable[i]->GetJob() << " " << setw(19) << employeeTable[i]->GetEmail() << " " << setprecision(0) << setw(19) << employeeTable[i]->GetDepartId() << endl;
		}
	}
	cout << endl;
}

//INSERT
void Employees::Insert(string query, string emps_name) {

	Employee* temp;			//necessary variables declared
	int empId;
	string firstName;
	string lastName;
	double phone;
	double salary;
	string job;
	string email;
	int departId;

	int pos;
	int origPos;
	int probed;
	int cont;

	smatch matcher;		//matcher object
	regex data("\\(\\((.*),(.*),(.*),(.*),(.*),(.*),(.*),(.*)\\).*\\)");
	regex_search(query, matcher, data);

	empId = stoi(matcher[1]);		//string conversions
	firstName = matcher[2];
	lastName = matcher[3];
	phone = stod(matcher[4]);
	salary = stod(matcher[5]);
	job = matcher[6];
	email = matcher[7];
	departId = stoi(matcher[8]);

	for (int i=0; i<10; i++) {			//reject entry
		if (empId == employeeTable[i]->GetEmpId()) {
			cout << "Failed to insert (" << empId << "," << firstName << "," << lastName << "," << setprecision(0) << fixed << phone << "," << setprecision(2) << fixed << salary << "," << job << "," << email << "," << setprecision(0) << departId << ") into " << emps_name << endl;
			return;
		}
	}

	temp = new Employee(empId, firstName, lastName, phone, salary, job, email, departId);

	if(key_type == "empId") {		//checks key type
		pos = Hash(empId);
		origPos = Hash(empId);
	}
	else if(key_type == "firstName") {
		pos = Hash(atoi(firstName.c_str()));
		origPos = Hash(atoi(firstName.c_str()));
	}
	else if(key_type == "lastName") {
		pos = Hash(atoi(lastName.c_str()));
		origPos = Hash(atoi(lastName.c_str()));
	}
	else if(key_type == "phone") {
		pos = Hash(phone);
		origPos = Hash(phone);
	}
	else if(key_type == "salary") {
		pos = Hash(salary);
		origPos = Hash(salary);
	}
	else if(key_type == "job") {
		pos = Hash(atoi(job.c_str()));
		origPos = Hash(atoi(job.c_str()));
	}
	else if(key_type == "email") {
		pos = Hash(atoi(email.c_str()));
		origPos = Hash(atoi(email.c_str()));
	}
	else if(key_type == "departId") {
		pos = Hash(departId);
		origPos = Hash(departId);
	}
	else {
		cout << "Key type not recognized.";
		return;
	}
	probed = 0;
	cont = 0;
	while (cont == 0) {
		if (employeeTable[pos]->empty_ss) {		//Collision strategy for hash table insert
			employeeTable[pos] = temp;
			employeeTable[pos]->empty_ss = false;
			cout << "Inserted (" << empId << "," << firstName << "," << lastName << "," << setprecision(0) << fixed << phone << "," << setprecision(2) << fixed << salary << "," << job << "," << email << "," << setprecision(0) << departId << ") into " << emps_name << endl;
			cont = 1;
		}
		probed++;
		pos = (origPos + 1 * probed + 1 * (probed * probed)) % 10;
		if (probed == 10) {
			cout << "Failed to insert (" << empId << "," << firstName << "," << lastName << "," << setprecision(0) << fixed << phone << "," << setprecision(2) << fixed << salary << "," << job << "," << email << "," << setprecision(0) << departId << ") into " << emps_name << endl;
			cont = 1;
		}
	}
}

//UPDATE
void Employees::Update(string query, string emps_name) {

	int empId;				//necessary variables declared
	string firstName;
	string lastName;
	double phone;
	double salary;
	string job;
	string email;
	int departId;

	int pos;
	int origPos;
	int probed;

	smatch matcher;		//matcher object
	regex data("\\(\\((.*),(.*),(.*),(.*),(.*),(.*),(.*),(.*)\\).*\\)");
	regex_search(query, matcher, data);

	empId = stoi(matcher[1]);			//string conversions
	firstName = matcher[2];
	lastName = matcher[3];
	phone = stod(matcher[4]);
	salary = stod(matcher[5]);
	job = matcher[6];
	email = matcher[7];
	departId = stoi(matcher[8]);

	if(key_type == "empId") {			//checks key type
		pos = Hash(empId);
		origPos = Hash(empId);
	}
	else if(key_type == "firstName") {
		pos = Hash(atoi(firstName.c_str()));
		origPos = Hash(atoi(firstName.c_str()));
	}
	else if(key_type == "lastName") {
		pos = Hash(atoi(lastName.c_str()));
		origPos = Hash(atoi(lastName.c_str()));
	}
	else if(key_type == "phone") {
		pos = Hash(phone);
		origPos = Hash(phone);
	}
	else if(key_type == "salary") {
		pos = Hash(salary);
		origPos = Hash(salary);
	}
	else if(key_type == "job") {
		pos = Hash(atoi(job.c_str()));
		origPos = Hash(atoi(job.c_str()));
	}
	else if(key_type == "email") {
		pos = Hash(atoi(email.c_str()));
		origPos = Hash(atoi(email.c_str()));
	}
	else if(key_type == "departId") {
		pos = Hash(departId);
		origPos = Hash(departId);
	}
	else {
		cout << "Key type not recognized.";
		return;
	}

	probed = 0;
	while (probed != 10) {
		if (!employeeTable[pos]->empty_ss) {
			if (employeeTable[pos]->GetEmpId() == empId) {		//checks for matching key value and updates
				employeeTable[pos]->SetEmpId(empId);
				employeeTable[pos]->SetFirstName(firstName);
				employeeTable[pos]->SetLastName(lastName);
				employeeTable[pos]->SetPhone(phone);
				employeeTable[pos]->SetSalary(salary);
				employeeTable[pos]->SetJob(job);
				employeeTable[pos]->SetEmail(email);
				employeeTable[pos]->SetDepartId(departId);
				cout << "Updated (" << empId << "," << firstName << "," << lastName << "," << setprecision(0) << fixed << phone << "," << setprecision(2) << fixed << salary << "," << job << "," << email << "," << setprecision(0) << departId << ") into " << emps_name << endl;
				return;
			}
			else if (employeeTable[pos]->GetEmpId() != empId) {
				probed++;
				pos = (origPos + 1 * probed + 1 * (probed * probed)) % 10;
			}
		}
		else {
			probed++;
			pos = (origPos + 1 * probed + 1 * (probed * probed)) % 10;
		}

	}
	cout << "Failed to Update (" << empId << "," << firstName << "," << lastName << "," << setprecision(0) << fixed << phone << "," << setprecision(2) << fixed << salary << "," << job << "," << email << "," << setprecision(0) << departId << ") into " << emps_name << endl;
}

//SELECT
void Employees::Select(string query, string emps_name) {

	int searchNum = 0;
	int matches;
	bool matchFound = false;

	smatch matcher;
	regex data("\\(\\((.*),(.*),(.*),(.*),(.*),(.*),(.*),(.*)\\).*\\)");
	regex_search(query, matcher, data);

	for (int i=1; i<=8; i++) {
		if (matcher[i] != "*") {
			searchNum++;
		}
	}

	for (int i=0; i<10; i++) { //checks for match with query
		matches = 0;
		if (matcher[1] != "*") {		//checks each component of query for a match
			if (employeeTable[i]->GetEmpId() == stoi(matcher[1])) {
				matches++;
			}
		}
		if (matcher[2] != "*") {
			if (employeeTable[i]->GetFirstName() == matcher[2]) {
				matches++;
			}
		}
		if (matcher[3] != "*") {
			if (employeeTable[i]->GetLastName() == matcher[3]) {
				matches++;
			}
		}
		if (matcher[4] != "*") {
			if (employeeTable[i]->GetPhone() == stod(matcher[4])) {
				matches++;
			}
		}
		if (matcher[5] != "*") {
			if (employeeTable[i]->GetSalary() == stod(matcher[5])) {
				matches++;
			}
		}
		if (matcher[6] != "*") {
			if (employeeTable[i]->GetJob() == matcher[6]) {
				matches++;
			}
		}
		if (matcher[7] != "*") {
			if (employeeTable[i]->GetEmail() == matcher[7]) {
				matches++;
			}
		}
		if (matcher[8] != "*") {
			if (employeeTable[i]->GetDepartId() == stoi(matcher[8])) {
				matches++;
			}
		}
		if (!employeeTable[i]->empty_ss) {
			if (matches == searchNum) {
				cout << "Found (" << employeeTable[i]->GetEmpId() << "," << employeeTable[i]->GetFirstName() << "," << employeeTable[i]->GetLastName() << "," << setprecision(0) << fixed <<
				employeeTable[i]->GetPhone() << "," << setprecision(2) << fixed << employeeTable[i]->GetSalary() << "," << employeeTable[i]->GetJob() << "," <<
				employeeTable[i]->GetEmail() << "," << setprecision(0) << employeeTable[i]->GetDepartId() << ") in " << emps_name << endl;
				matchFound = true;
			}
		}
	}

	smatch output;
	regex testLine("\\((.*)\\).*\\)");
	regex_search(query, output, testLine);

	if (!matchFound) {
		cout << "No entries match query " << output[1] << ") in " << emps_name << endl;
	}

}

//DELETE
void Employees::Delete(string query, string emps_name) {

	int searchNum = 0;
	int matches;
	bool matchFound = false;

	smatch matcher;
	regex data("\\(\\((.*),(.*),(.*),(.*),(.*),(.*),(.*),(.*)\\).*\\)");
	regex_search(query, matcher, data);

	for (int i=1; i<=8; i++) {
		if (matcher[i] != "*") {
			searchNum++;
		}
	}
//Like the select function, the delete function searches for a match and deletes
	for (int i=0; i<10; i++) {
		matches = 0;
		if (matcher[1] != "*") {
			if (employeeTable[i]->GetEmpId() == stoi(matcher[1])) {
				matches++;
			}
		}
		if (matcher[2] != "*") {
			if (employeeTable[i]->GetFirstName() == matcher[2]) {
				matches++;
			}
		}
		if (matcher[3] != "*") {
			if (employeeTable[i]->GetLastName() == matcher[3]) {
				matches++;
			}
		}
		if (matcher[4] != "*") {
			if (employeeTable[i]->GetPhone() == stod(matcher[4])) {
				matches++;
			}
		}
		if (matcher[5] != "*") {
			if (employeeTable[i]->GetSalary() == stod(matcher[5])) {
				matches++;
			}
		}
		if (matcher[6] != "*") {
			if (employeeTable[i]->GetJob() == matcher[6]) {
				matches++;
			}
		}
		if (matcher[7] != "*") {
			if (employeeTable[i]->GetEmail() == matcher[7]) {
				matches++;
			}
		}
		if (matcher[8] != "*") {
			if (employeeTable[i]->GetDepartId() == stoi(matcher[8])) {
				matches++;
			}
		}
		if (!employeeTable[i]->empty_ss) {
			if (matches == searchNum) {
				cout << "Deleted (" << employeeTable[i]->GetEmpId() << "," << employeeTable[i]->GetFirstName() << "," << employeeTable[i]->GetLastName() << "," << setprecision(0) << fixed <<
				employeeTable[i]->GetPhone() << "," << setprecision(2) << fixed << employeeTable[i]->GetSalary() << "," << employeeTable[i]->GetJob() << "," <<
				employeeTable[i]->GetEmail() << "," << setprecision(0) << employeeTable[i]->GetDepartId() << ") in " << emps_name << endl;
				matchFound = true;
				employeeTable[i]->empty_ar = true;
				employeeTable[i]->empty_ss = false;
			}
		}
	}

	smatch output;
	regex testLine("\\((.*)\\).*\\)");
	regex_search(query, output, testLine);

	if (!matchFound) {
		cout << "Failed to delete " << output[1] << ") in " << emps_name << endl;
	}
}

//WRITE
void Employees::Write() {
	ofstream outFile("employee_out.csv"); 		//writes information to file

	outFile << key_type << endl;
	outFile << "empId               firstName           lastName            phone               salary              job                 email               departId" << endl;
	for (int i = 0; i < 10; ++i) {
		if (!employeeTable[i]->empty_ss && !employeeTable[i]->empty_ar) {
			outFile << left << setw(19) << employeeTable[i]->GetEmpId() << " " << setw(19) << employeeTable[i]->GetFirstName() << " " << setw(19) << employeeTable[i]->GetLastName() << " " << setprecision(0) << fixed << setw(19) << employeeTable[i]->GetPhone() << " " << setprecision(2) << fixed << setw(19) << employeeTable[i]->GetSalary() << " " << setw(19) << employeeTable[i]->GetJob() << " " << setw(19) << employeeTable[i]->GetEmail() << " " << setprecision(0) << setw(19) << employeeTable[i]->GetDepartId() << endl;
		}
	}
	outFile << endl;
}

void Employees::Cleanup() {
        for(auto it = employeeTable.begin(); it != employeeTable.end(); ++it) {
                delete *it; //deletes data from every object
        }
        employeeTable.clear(); //clears database
}
