#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using namespace std;

class Employee {
	public:
		bool empty_ss = true;
		bool empty_ar = false;
		Employee(int empId, string firstName, string lastName, double phone, double salary, string job, string email, int departId);
		void SetEmpId(int empId);
		void SetFirstName(string firstName);
		void SetLastName(string lastName);
		void SetPhone(double phone);
		void SetSalary(double salary);
		void SetJob(string job);
		void SetEmail(string email);
		void SetDepartId(int departId);
		int GetEmpId();
		string GetFirstName();
		string GetLastName();
		double GetPhone();
		double GetSalary();
		string GetJob();
		string GetEmail();
		int GetDepartId();

	private:
		int empId;
		string firstName;
		string lastName;
		double phone;
		double salary;
		string job;
		string email;
		int departId;
};
#endif
