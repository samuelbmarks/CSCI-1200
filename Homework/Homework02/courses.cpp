/*
Implementation file for the Courses class.
*/
#include <cstring>
#include "courses.h"

Courses::Courses(){
	CRN = 00000;
	DEPT = "";
	CODE = "";
	DAY = "";
	START = "";
	END = "";
	ROOM = "";
}

Courses::Courses(int crn, string dept, string code, string name, string day, string start, string end, string room){
	CRN = crn;
	DEPT = dept;
	CODE = code;
	NAME = name;
	DAY = day;
	START = start;
	END = end;
	ROOM = room;
}

//comparative function that sorts by course code, then day of the week (earliest first), then by the classes start time (earliest first)
bool compare_dept (Courses& c1, Courses& c2){
	if (c1.getcode()<c2.getcode())
		return true;
	else if (c1.getcode() == c2.getcode()){	
		int a;
		int b;
		if (c1.getday() == "Monday")
			a = 1;
		else if (c1.getday() == "Tuesday")
			a = 2;
		else if (c1.getday() == "Wednesday")
			a = 3;
		else if (c1.getday() == "Thursday")
			a = 4;
		else if (c1.getday() == "Friday")
			a = 5;

		if (c2.getday() == "Monday")
			b = 1;
		else if (c2.getday() == "Tuesday")
			b = 2;
		else if (c2.getday() == "Wednesday")
			b = 3;
		else if (c2.getday() == "Thursday")
			b = 4;
		else if (c2.getday() == "Friday")
			b = 5;

		if (a < b)
			return true;
		else if (a == b){
			string c1hour = c1.getstart().substr(0,2);
			int c1hr = stoi(c1hour);
			string c1minute = c1.getstart().substr(3,2);
			int c1min = stoi(c1minute);
			bool c1am = false;
			if (c1.getstart()[5] == 'A')
				c1am = true;

			string c2hour = c2.getstart().substr(0,2);
			int c2hr = stoi(c2hour);
			string c2minute = c2.getstart().substr(3,2);
			int c2min = stoi(c2minute);
			bool c2am = false;
					if (c2.getstart()[5] == 'A')
						c2am = true;

			if (c1hr == 12){
				c1hr = 0;
			}
			if (c2hr == 12){
				c2hr = 0;
			}

			bool check = false;
			if (c1am == c2am){
				if (c1hr == c2hr){
					if (c1min == c2min){
						if (c1.getcode()<c2.getcode())
							return true;
						else 
							return false;
					}
						
					else if (c1min < c2min)
						check = true;
					else
						check = false;	
				}
				else if (c1hr < c2hr)
					check = true;
				
				else 
					check = false;
			}
			else if (c1am == true && c2am == false)
				check = true;
			
			return check;
		}	
		else
			return false;
	}
	else
		return false;
}

//comparative function that sorts by day of the week (earliest first), then by the classes start time (earliest first), then by course code 
bool compare_room (Courses& c1, Courses& c2){
	int a;
	int b;
	if (c1.getday() == "Monday")
		a = 1;
	else if (c1.getday() == "Tuesday")
		a = 2;
	else if (c1.getday() == "Wednesday")
		a = 3;
	else if (c1.getday() == "Thursday")
		a = 4;
	else if (c1.getday() == "Friday")
		a = 5;

	if (c2.getday() == "Monday")
		b = 1;
	else if (c2.getday() == "Tuesday")
		b = 2;
	else if (c2.getday() == "Wednesday")
		b = 3;
	else if (c2.getday() == "Thursday")
		b = 4;
	else if (c2.getday() == "Friday")
		b = 5;

	if (a < b)
		return true;
	else if (a == b){
		string c1hour = c1.getstart().substr(0,2);
		int c1hr = stoi(c1hour);
		string c1minute = c1.getstart().substr(3,2);
		int c1min = stoi(c1minute);
		bool c1am = false;
		if (c1.getstart()[5] == 'A')
			c1am = true;

		string c2hour = c2.getstart().substr(0,2);
		int c2hr = stoi(c2hour);
		string c2minute = c2.getstart().substr(3,2);
		int c2min = stoi(c2minute);
		bool c2am = false;
				if (c2.getstart()[5] == 'A')
					c2am = true;

		if (c1hr == 12){
			c1hr = 0;
		}
		if (c2hr == 12){
			c2hr = 0;
		}

		bool check = false;
		if (c1am == c2am){
			if (c1hr == c2hr){
				if (c1min == c2min){
					if (c1.getcode()<c2.getcode())
						return true;
					else 
						return false;
				}
					
				else if (c1min < c2min)
					check = true;
				else
					check = false;	
			}
			else if (c1hr < c2hr)
				check = true;
			
			else 
				check = false;
		}
		else if (c1am == true && c2am == false)
			check = true;
		
		return check;
	}	
	else
		return false;
}