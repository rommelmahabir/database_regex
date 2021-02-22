#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <string>
using namespace std;

class Department {
        public:
		bool empty_ss = true;
		bool empty_ar = false;
		Department(int departId, string name, string location, int mgrId, int admrDepartId);
		void SetDepartId(int departId);
		void SetName(string name);
		void SetLocation(string location);
		void SetMgrId(int mgrId);
		void SetAdmrDepartId(int admrDepartId);
		int GetDepartId();
		string GetName();
		string GetLocation();
		int GetMgrId();
		int GetAdmrDepartId();

	private:
		int departId;
		string name;
		string location;
		int mgrId;
		int admrDepartId;
};
#endif
