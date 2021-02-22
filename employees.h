#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <vector>
#include <string>
#include "employee.h"
using namespace std;

class Employees {
	public:
		int Hash(int key);
		void Input(string emps_file, string emps_name);
		void Display(string emps_name);
		//INSERT
		void Insert(string query, string emps_name);
		//UPDATE
		void Update(string query, string emps_name);
		//SELECT
		void Select(string query, string emps_name);
		//DELETE
		void Delete(string query, string emps_name);
		//WRITE
		void Write();
		//Cleanup
		void Cleanup();

	private:
		typedef vector<Employee*> employeeType;
		employeeType employeeTable = employeeType(10);
		string key_type;
};
#endif
