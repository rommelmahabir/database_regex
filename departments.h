#ifndef DEPARTMENTS_H
#define DEPARTMENTS_H

#include <vector>
#include <string>
#include "department.h"
using namespace std;

class Departments {
  public:
    int Hash(int key);
    void Input(string deps_file, string deps_name);
    void Display(string deps_name);
    //INSERT
    void Insert(string query, string deps_name);
    //UPDATE
    void Update(string query, string deps_name);
    //SELECT
    void Select(string query, string deps_name);
    //DELETE
    void Delete(string query, string deps_name);
    //WRITE
    void Write();
    //CLEANUP
		void Cleanup();

   private:
     typedef vector<Department*> departmentType;
     departmentType departmentTable = departmentType(10);
     string key_type;
};
#endif
