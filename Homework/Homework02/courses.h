/*
Header file with declaration of the Courses class, 
including member functions and private member variables 
*/
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <cstring>
using namespace std;

class Courses {
public:
	Courses();
	Courses(int crn, string dept, string code, string name, string day, string start, string end, string room);
	
	//getters
	int getcrn()
		{return CRN;}
	string getdept()
		{return DEPT;}
	string getcode()
		{return CODE;}
	string getname()
		{return NAME;}
	string getday()
		{return DAY;}
	string getstart()
		{return START;}
	string getend()
		{return END;}
	string getroom()
		{return ROOM;}

	void print();

private:
	int CRN;
	string DEPT;
	string CODE;
	string NAME;
	string DAY;
	string START;
	string END;
	string ROOM;
};

//comparative funtions
bool compare_room(Courses& c1,  Courses& c2);
bool compare_dept(Courses& c1, Courses& c2);

