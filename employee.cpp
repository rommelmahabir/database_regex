#include <iostream>
#include <string>
#include "employee.h"
using namespace std;

Employee::Employee(int empId, string firstName, string lastName, double phone, double salary, string job, string email, int departId) {
	this->empId = empId;
	this->firstName = firstName;
	this->lastName = lastName;
	this->phone = phone;
	this->salary = salary;
	this->job = job;
	this->email = email;
	this->departId = departId;
}

void Employee::SetEmpId(int empId) {
	this->empId = empId;
}

void Employee::SetFirstName(string firstName) {
        this->firstName = firstName;
}

void Employee::SetLastName(string lastName) {
        this->lastName = lastName;
}

void Employee::SetPhone(double phone) {
        this->phone = phone;
}

void Employee::SetSalary(double salary) {
        this->salary = salary;
}

void Employee::SetJob(string job) {
        this->job = job;
}

void Employee::SetEmail(string email) {
        this->email = email;
}

void Employee::SetDepartId(int departId) {
        this->departId = departId;
}

int Employee::GetEmpId() {
	return empId;
}

string Employee::GetFirstName() {
        return firstName;
}

string Employee::GetLastName() {
        return lastName;
}

double Employee::GetPhone() {
        return phone;
}

double Employee::GetSalary() {
        return salary;
}

string Employee::GetJob() {
        return job;
}

string Employee::GetEmail() {
        return email;
}

int Employee::GetDepartId() {
        return departId;
}


