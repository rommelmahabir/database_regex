#ifndef PROJECT_H
#define PROJECT_H

#include <string>
using namespace std;

class Project {
	public:
		Project(int projId, int empId, string projName, string startDate, string endDate, double empTime);
		void SetProjId(int projId);
		void SetEmpId(int empId);
		void SetProjName(string projName);
		void SetStartDate(string startDate);
		void SetEndDate(string endDate);
		void SetEmpTime(double empTime);
		int GetProjId();
		int GetEmpId();
		string GetProjName();
		string GetStartDate();
		string GetEndDate();
		double GetEmpTime();

	private:
		int projId;
		int empId;
		string projName;
		string startDate;
		string endDate;
		double empTime;
};
#endif
