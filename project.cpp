#include <iostream>
#include <string>
#include "project.h"
using namespace std;

Project::Project(int projId, int empId, string projName, string startDate, string endDate, double empTime) {
        this->projId = projId;
        this->empId = empId;
        this->projName = projName;
	this->startDate = startDate;
        this->endDate = endDate;
        this->empTime = empTime;
}

void Project::SetProjId(int projId) {
        this->projId = projId;
}

void Project::SetEmpId(int empId) {
        this->empId = empId;
}

void Project::SetProjName(string projName) {
        this->projName = projName;
}

void Project::SetStartDate(string startDate) {
	this->startDate = startDate;
}

void Project::SetEndDate(string endDate) {
        this->endDate = endDate;
}

void Project::SetEmpTime(double empTime) {
        this->empTime = empTime;
}

int Project::GetProjId() {
        return projId;
}

int Project::GetEmpId() {
        return empId;
}

string Project::GetProjName() {
        return projName;
}

string Project::GetStartDate() {
	return startDate;
}

string Project::GetEndDate() {
        return endDate;
}

double Project::GetEmpTime() {
        return empTime;
}

