#include <iostream>
#include <string>
#include "department.h"
using namespace std;

Department::Department(int departId, string name, string location, int mgrId, int admrDepartId) {
        this->departId = departId;
	this->name = name;
	this->location = location;
	this->mgrId = mgrId;
	this->admrDepartId = admrDepartId;
}

void Department::SetDepartId(int departId) {
        this->departId = departId;
}

void Department::SetName(string name) {
        this->name = name;
}

void Department::SetLocation(string location) {
        this->location = location;
}

void Department::SetMgrId(int mgrId) {
        this->mgrId = mgrId;
}

void Department::SetAdmrDepartId(int admrDepartId) {
        this->admrDepartId = admrDepartId;
}

int Department::GetDepartId() {
	return departId;
}

string Department::GetName() {
	return name;
}

string Department::GetLocation() {
	return location;
}

int Department::GetMgrId() {
	return mgrId;
}

int Department::GetAdmrDepartId() {
	return admrDepartId;
}
