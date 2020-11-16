#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "courses.h"
using namespace std;

string getDOTW(char c){ 
	if (c == 'M')
		return "Monday";
	else if (c == 'T')
		return "Tuesday";
	else if (c == 'W')
		return "Wednesday";
	else if (c == 'R')
		return "Thursday";
	else if (c == 'F')
		return "Friday";
}

int max_name_length(vector<Courses> vect_course){
	int max = 0;
	for (unsigned int i = 0; i < vect_course.size(); i++){
		if (vect_course[i].getname().length() > max)
			max = vect_course[i].getname().length();
	}
	return max;
}

int max_dept_length(vector<Courses> vect_course){
	int max = 0;
	for (int i = 0; i < vect_course.size(); i++){
		if (vect_course[i].getdept().length() > max)
			max = vect_course[i].getdept().length();
	}
	return max;
}

int day_length(string day){
	if (day == "Monday")
		return 6;
	else if (day == "Tuesday")
		return 7;
	else if (day == "Wednesday")
		return 9;
	else if (day == "Thursday")
		return 8;
	else if (day== "Friday")
		return 6;
}

int max_day_length(vector<Courses> vect_course){
	vector<int> day_lengths;
	for (unsigned int i = 0; i < vect_course.size(); i++){
		if (vect_course[i].getday() == "Monday")
			day_lengths.push_back(6);
		else if (vect_course[i].getday() == "Tuesday")
			day_lengths.push_back(7);
		else if (vect_course[i].getday() == "Wednesday")
			day_lengths.push_back(9);
		else if (vect_course[i].getday() == "Thursday")
			day_lengths.push_back(8);
		else if (vect_course[i].getday() == "Friday")
			day_lengths.push_back(6);
		}
	int max = 0;
	for (int i = 0; i < day_lengths.size(); i++){
		if (day_lengths[i] > max)
			max = day_lengths[i];
	}
	return max;
}

int main(int argc, char* argv[]){
	string crn, dept, code, name, day, start, end, room;

	//vector to store course data
	vector<Courses> allCourses;
	//opening input file
	ifstream inputFile;
	inputFile.open(argv[1]);
	//error message input file fails to open
	if (!inputFile.good()){
    	cerr << "Error: Cannot open input file " << argv[1] << endl;
   		exit(1);
  	}

  	//filling allCourses vector with Courses class objects taken from input file
  	while(inputFile>>crn>>dept>>code>>name>>day>>start>>end>>room){
  		for(int i =0; i<day.size();++i)
   			allCourses.push_back(Courses(atoi(crn.c_str()),dept,code,name,getDOTW(day[i]),start,end,room));
	}
	
	//printing out input file, to be removed
	cout << allCourses.size() << endl;
	for (int i=0;i<allCourses.size();i++){
		allCourses[i].print();
	}

	cout << "\n\n";

	//closing input file
	inputFile.close();

	//opening output file
	ofstream outFile;
	outFile.open(argv[2]);
	
	//error message if output file fails to open
	if (!outFile.good()){
    	cerr << "Error: Cannot open output file " << argv[2] << endl;
    	exit(1);
	}

	cout << allCourses.size() << endl;
	if (allCourses.size() == 0) {
		cout << "No data available." << endl;
		exit(1);
	}


	if (strcmp(argv[3], "room") == 0){
		if (argc == 5){
			vector<Courses> room_courses;
			for (int i = 0; i < allCourses.size(); i++){
				if (allCourses[i].getroom() == argv[4])
					room_courses.push_back(allCourses[i]);
			}

			if (room_courses.size() == 0)
				cout << "No data available." << endl;
				//exit(1);
			
			sort(room_courses.begin(),room_courses.end(),compare_room);

			cout << "Room " << argv[4] << endl;
			cout << "Dept";
			int max_dept = max_dept_length(room_courses);
			for (int i = 0; i < (max_dept-4)+2; i++)
				cout << " ";
			cout << "Coursenum" << "  " << "Class Title";
			int max_name = max_name_length(room_courses);
			if (max_name <= 11)
					cout << "  ";
			else {
				for (int i = 0; i < (max_name-11)+2; i++)
					cout << " ";
			}
			cout << "Day";
			int max_day = max_day_length(room_courses);
			for (int i = 0; i < (max_day-3)+2; i++)
				cout << " ";
			cout << "Start Time" << "  " << "End Time" << endl;
			for (int i = 0; i < max_dept; i++)
				cout << "-";
			cout << "  ---------  "; 
			for (int i = 0; i < max_name; i++)
				cout << "-";
			cout << "  ";
			for (int i = 0; i < max_day; i++)
				cout << "-";
			cout << "  ";
			cout << "----------  --------" << endl;	
			int counter = 0;
			for (int i = 0; i < room_courses.size(); i++){
				cout << room_courses[i].getdept() << "  " << room_courses[i].getcode();
				for (int j = 0; j < (11-room_courses[i].getcode().length()); j++)
					cout << " ";
				cout << room_courses[i].getname();
				for (int j = 0; j < (max_name-room_courses[i].getname().length())+2; j++)
					cout << " ";
				cout << room_courses[i].getday();
				int length = day_length(room_courses[i].getday());
				for (int j = 0; j < (max_day-length)+2; j++)
					cout << " ";
				cout << room_courses[i].getstart() << "     " << room_courses[i].getend() << " " << endl;
				counter += 1;
			}
		cout << counter << " entries\n\n";
		}
	
		else if (argc == 4){
			vector<string> rooms;
			for (int i = 0; i < allCourses.size(); i++){
				bool if_in = false;
				for (int j = 0; j < rooms.size(); j++){
					if (rooms[j] == allCourses[i].getroom())
						if_in = true;
				}
				if (!if_in)
					rooms.push_back(allCourses[i].getroom());
			}
			sort(rooms.begin(),rooms.end());
			
			vector<vector<Courses>> temp_vector;
			for (int i = 0; i < rooms.size(); i++){
				vector<Courses> temp_vector2;
				for (int j = 0; j < allCourses.size(); j++){
					if (allCourses[j].getroom() == rooms[i])
						temp_vector2.push_back(allCourses[j]);
				}
				temp_vector.push_back(temp_vector2);
			}

			for(int i = 0; i < temp_vector.size(); i++){
				
				sort(temp_vector[i].begin(),temp_vector[i].end(),compare_room);
				
				cout << "Room " << rooms[i] << endl;
				cout << "Dept";
				int max_dept = max_dept_length(temp_vector[i]);
				for (int j = 0; j < (max_dept-4)+2; j++)
					cout << " ";
				cout << "Coursenum" << "  " << "Class Title";
				int max_name = max_name_length(temp_vector[i]);
				if (max_name <= 11)
						cout << "  ";
				else {
					for (int j = 0; j < (max_name-11)+2; j++)
						cout << " ";
				}
				cout << "Day";
				int max_day = max_day_length(temp_vector[i]);
				for (int j = 0; j < (max_day-3)+2; j++)
					cout << " ";
				cout << "Start Time" << "  " << "End Time" << endl;
				for (int j = 0; j < max_dept; j++)
					cout << "-";
				cout << "  ---------  "; 
				for (int j = 0; j < max_name; j++)
					cout << "-";
				cout << "  ";
				for (int j = 0; j < max_day; j++)
					cout << "-";
				cout << "  ";
				cout << "----------  --------" << endl;	
				int counter = 0;
				for (int j = 0; j < temp_vector[i].size(); j++){
					cout << temp_vector[i][j].getdept() << "  " << temp_vector[i][j].getcode();
					for (int q = 0; q < (11-temp_vector[i][j].getcode().length()); q++)
						cout << " ";
					cout << temp_vector[i][j].getname();
					for (int q = 0; q < (max_name-temp_vector[i][j].getname().length())+2; q++)
						cout << " ";
					cout << temp_vector[i][j].getday();
					int length = day_length(temp_vector[i][j].getday());
					for (int q = 0; q < (max_day-length)+2; q++)
						cout << " ";
					cout << temp_vector[i][j].getstart() << "     " << temp_vector[i][j].getend() << " " << endl;
					counter += 1;
				}
				cout << counter << " entries\n\n";
			}
		}
	}


	if (strcmp(argv[3], "dept") == 0){
		vector<Courses> dept_courses;
		for (int i = 0; i < allCourses.size(); i++){
			if (allCourses[i].getdept() == argv[4])
				dept_courses.push_back(allCourses[i]);
		}

		if (dept_courses.size() == 0)
			cout << "No data available." << endl;

		sort(dept_courses.begin(),dept_courses.end(), compare_dept);

		cout << "Dept " << argv[4] << endl;
		cout << "Coursenum" << "  " << "Class Title";
		int max_name = max_name_length(dept_courses);
		if (max_name <= 11)
			cout << "  ";
		else {
			for (int i = 0; i < (max_name-11)+2; i++)
				cout << " ";
		}
		cout << "Day";
		int max_day = max_day_length(dept_courses);
		for (int i = 0; i < (max_day-3)+2; i++)
			cout << " ";
		cout << "Start Time" << "  " << "End Time" << endl;
		cout << "---------  "; 
		for (int i = 0; i < max_name; i++)
			cout << "-";
		cout << "  ";
		for (int i = 0; i < max_day; i++)
			cout << "-";
		cout << "  ";
		cout << "----------  --------" << endl;
		int counter = 0;
		for (int i = 0; i < dept_courses.size(); i++){
			cout << dept_courses[i].getcode() << "    " << dept_courses[i].getname();
			for (int j = 0; j < (max_name-dept_courses[i].getname().length())+2; j++)
				cout << " ";
			cout << dept_courses[i].getday();
			int length = day_length(dept_courses[i].getday());
			for (int j = 0; j < (max_day-length)+2; j++)
				cout << " ";
			cout << dept_courses[i].getstart() << "     " << dept_courses[i].getend() << " " << endl;
					counter += 1;
		}
	cout << counter << " entries\n\n";
	}

	if (strcmp(argv[3], "custom") == 0){
			vector<string> rooms;
			for (int i = 0; i < allCourses.size(); i++){
				bool if_in = false;
				for (int j = 0; j < rooms.size(); j++){
					if (rooms[j] == allCourses[i].getroom())
						if_in = true;
				}
				if (!if_in)
					rooms.push_back(allCourses[i].getroom());
			}
			sort(rooms.begin(),rooms.end());
			
			vector<vector<Courses>> allrooms_vect;
			for (int i = 0; i < rooms.size(); i++){
				vector<Courses> allrooms_vect2;
				for (int j = 0; j < allCourses.size(); j++){
					if (allCourses[j].getroom() == rooms[i])
						allrooms_vect2.push_back(allCourses[j]);
				}
				allrooms_vect.push_back(allrooms_vect2);
			}

			for(int i = 0; i < allrooms_vect.size(); i++){
				
				sort(allrooms_vect[i].begin(),allrooms_vect[i].end(),compare_room);
				
				cout << "Room " << rooms[i] << endl;
				cout << "Dept";
				int max_dept = max_dept_length(allrooms_vect[i]);
				for (int j = 0; j < (max_dept-4)+2; j++)
					cout << " ";
				cout << "Coursenum" << "  " << "Class Title";
				int max_name = max_name_length(allrooms_vect[i]);
				if (max_name <= 11)
						cout << "  ";
				else {
					for (int j = 0; j < (max_name-11)+2; j++)
						cout << " ";
				}
				cout << "Day";
				int max_day = max_day_length(allrooms_vect[i]);
				for (int j = 0; j < (max_day-3)+2; j++)
					cout << " ";
				cout << "Start Time" << "  " << "End Time" << endl;
				for (int j = 0; j < max_dept; j++)														
					cout << "-";
				cout << "  ---------  "; 
				if (max_name < 11)
					cout << "-----------";
				else{	
					for (int j = 0; j < max_name; j++)
						cout << "-";
				}
				cout << "  ";
				for (int j = 0; j < max_day; j++)
					cout << "-";
				cout << "  ";
				cout << "----------  --------" << endl;	
				int counter = 0;
				for (int j = 0; j < allrooms_vect[i].size(); j++){
					cout << allrooms_vect[i][j].getdept() << "  " << allrooms_vect[i][j].getcode();
					for (int q = 0; q < (11-allrooms_vect[i][j].getcode().length()); q++)
						cout << " ";
					cout << allrooms_vect[i][j].getname();
					if (max_name < 11){
						for (int q = 0; q < (11-allrooms_vect[i][j].getname().length())+2; q++)
							cout << " ";
					}
					else {
						for (int q = 0; q < (max_name-allrooms_vect[i][j].getname().length())+2; q++)
						cout << " ";
					}
					cout << allrooms_vect[i][j].getday();
					int length = day_length(allrooms_vect[i][j].getday());
					for (int q = 0; q < (max_day-length)+2; q++)
						cout << " ";
					cout << allrooms_vect[i][j].getstart() << "     " << allrooms_vect[i][j].getend() << " " << endl;
					counter += 1;
				}
				cout << counter << " entries" << endl;
				float percent = ((float)counter / (float)allCourses.size())* 100.00;
				cout << percent << "% of the courses listed in this file, " << argv[1] << ", are in this room, " << rooms[i] << ".\n\n";
			}
		}

outFile.close();
}