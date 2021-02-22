#ifndef PROJECTS_H
#define PROJECTS_H

#include <vector>
#include <string>
#include "project.h"
using namespace std;

class Projects {
  public:
    int Hash(int key);
    void Input(string pros_file, string pros_name);
    void Display(string pros_name);
    //INSERT
    void Insert(string query, string pros_name);
    //UPDATE
    void Update(string query, string pros_name);
    //SELECT
    void Select(string query, string pros_name);
    //DELETE
    void Delete(string query, string pros_name);
    //WRITE
    void Write();
    //Cleanup
		void Cleanup();

  private:
    typedef vector<vector<Project*>> projectType;
		projectType projectTable = projectType(10);
		string key_type;
};
#endif
