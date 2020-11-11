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


//This function takes in a single character as an argument, c, and returns the day of the week (DOTW) that it cooresponds to 
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

//This function takes in a vector of Courses class objects, vect_course, and returns an integer, max, the maximum string length of all of the object's class names/titles
//This function is used to format the spacing of the tables that are outputted to the output file
int max_name_length(vector<Courses>& vect_course){
	int max = 0;
	for (unsigned int i = 0; i < vect_course.size(); i++){
		if (vect_course[i].getname().length() > max)
			max = vect_course[i].getname().length();
	}
	return max;
}

//This function takes in a vector of Courses class objects, vect_course, and returns an integer, max, the maximum string length of all of the object's deptartment
//This function is used to format the spacing of the tables that are outputted to the output file
int max_dept_length(vector<Courses>& vect_course){
	int max = 0;
	for (int i = 0; i < vect_course.size(); i++){
		if (vect_course[i].getdept().length() > max)
			max = vect_course[i].getdept().length();
	}
	return max;
}

//This function takes in a string representing a day of the week, day, and returns an integer that is the length of the of the string, day
//This function is used to format the spacing of the tables that are outputted to the output file
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

//This function takes in a vector of Courses class objects, vect_course, and returns an integer, max, the maximum string length of all of the object's days
//This function is used to format the spacing of the tables that are outputted to the output file
int max_day_length(vector<Courses>& vect_course){
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

//Four major variations in user input: an unspecified room, a specified room, a specified department, and custom
//Unspecified room: returns statistics about all the rooms that appear in a given file
//Specified room: returns statistics about the room that is given as an argument in the command line
//Specified dept: returns statistics about the dept that is given as an argument in the command line
//custom: return more specific statistics about all of the rooms that appear in a given file
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

	//error check: checks to make sure that there is data in the input file
	if (allCourses.size() == 0) {
		outFile << "No data available." << endl;
		exit(1);
	}

	//room based output
	if (strcmp(argv[3], "room") == 0){
		//this section is organized to output information about a specified room inputted by the user
		if (argc == 5){
			vector<Courses> room_courses;
			for (int i = 0; i < allCourses.size(); i++){
				if (allCourses[i].getroom() == argv[4])
					room_courses.push_back(allCourses[i]);
			}

			//error check: checks to make sure that the room entered by the user is present in the file
			if (room_courses.size() == 0){
				outFile << "No data available." << endl;
				exit(1);
			}
			
			//sorting rooms by day of the week (earliest first), by time (earliest first), then by course code 
			sort(room_courses.begin(),room_courses.end(),compare_room);

			//outputting the chart, utilizing functions created at the beginning of the file for spacing purposes
			outFile << "Room " << argv[4] << endl;
			outFile << "Dept";
			int max_dept = max_dept_length(room_courses);
			for (int i = 0; i < (max_dept-4)+2; i++)
				outFile << " ";
			outFile << "Coursenum" << "  " << "Class Title";
			int max_name = max_name_length(room_courses);
			if (max_name <= 11)
					outFile << "  ";
			else {
				for (int i = 0; i < (max_name-11)+2; i++)
					outFile << " ";
			}
			outFile << "Day";
			int max_day = max_day_length(room_courses);
			for (int i = 0; i < (max_day-3)+2; i++)
				outFile << " ";
			outFile << "Start Time" << "  " << "End Time" << endl;
			for (int i = 0; i < max_dept; i++)
				outFile << "-";
			outFile << "  ---------  "; 
			if (max_name < 11)
					outFile << "-----------";
			else{	
				for (int j = 0; j < max_name; j++)
					outFile << "-";
				}
			outFile << "  ";
			for (int i = 0; i < max_day; i++)
				outFile << "-";
			outFile << "  ";
			outFile << "----------  --------" << endl;	
			int counter = 0;
			for (int i = 0; i < room_courses.size(); i++){
				outFile << room_courses[i].getdept() << "  " << room_courses[i].getcode();
				for (int j = 0; j < (11-room_courses[i].getcode().length()); j++)
					outFile << " ";
				outFile << room_courses[i].getname();
				for (int j = 0; j < (max_name-room_courses[i].getname().length())+2; j++)
					outFile << " ";
				outFile << room_courses[i].getday();
				int length = day_length(room_courses[i].getday());
				for (int j = 0; j < (max_day-length)+2; j++)
					outFile << " ";
				outFile << room_courses[i].getstart() << "     " << room_courses[i].getend() << " " << endl;
				counter += 1;
			}
		outFile << counter << " entries\n\n";
		}
	
		//this section is organized to output information about all the rooms that are present in the input file
		else if (argc == 4){
			//creating a vector of strings, rooms, that contain all the rooms in the input file, checking for duplicates
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
			
			//sorting the rooms in the rooms vector in alphabetic order
			sort(rooms.begin(),rooms.end());
			
			//creating a vector of vectors containing Courses class objects, allrooms_vect, that will contain a vectors of information about all of the rooms present
			//this filling of the vector is completed in the following nested for loop
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
				//sorting rooms by day of the week (earliest first), by time (earliest first), then by course code
				sort(allrooms_vect[i].begin(),allrooms_vect[i].end(),compare_room);
				
				//outputting tables containing information about room in the file utilizing functions created at the beginning of the file
				outFile << "Room " << rooms[i] << endl;
				outFile << "Dept";
				int max_dept = max_dept_length(allrooms_vect[i]);
				for (int j = 0; j < (max_dept-4)+2; j++)
					outFile << " ";
				outFile << "Coursenum" << "  " << "Class Title";
				int max_name = max_name_length(allrooms_vect[i]);
				if (max_name <= 11)
						outFile << "  ";
				else {
					for (int j = 0; j < (max_name-11)+2; j++)
						outFile << " ";
				}
				outFile << "Day";
				int max_day = max_day_length(allrooms_vect[i]);
				for (int j = 0; j < (max_day-3)+2; j++)
					outFile << " ";
				outFile << "Start Time" << "  " << "End Time" << endl;
				for (int j = 0; j < max_dept; j++)														
					outFile << "-";
				outFile << "  ---------  "; 
				if (max_name < 11)
					outFile << "-----------";
				else{	
					for (int j = 0; j < max_name; j++)
						outFile << "-";
				}
				outFile << "  ";
				for (int j = 0; j < max_day; j++)
					outFile << "-";
				outFile << "  ";
				outFile << "----------  --------" << endl;	
				int counter = 0;
				for (int j = 0; j < allrooms_vect[i].size(); j++){
					outFile << allrooms_vect[i][j].getdept() << "  " << allrooms_vect[i][j].getcode();
					for (int q = 0; q < (11-allrooms_vect[i][j].getcode().length()); q++)
						outFile << " ";
					outFile << allrooms_vect[i][j].getname();
					if (max_name < 11){
						for (int q = 0; q < (11-allrooms_vect[i][j].getname().length())+2; q++)
							outFile << " ";
					}
					else {
						for (int q = 0; q < (max_name-allrooms_vect[i][j].getname().length())+2; q++)
						outFile << " ";
					}
					outFile << allrooms_vect[i][j].getday();
					int length = day_length(allrooms_vect[i][j].getday());
					for (int q = 0; q < (max_day-length)+2; q++)
						outFile << " ";
					outFile << allrooms_vect[i][j].getstart() << "     " << allrooms_vect[i][j].getend() << " " << endl;
					counter += 1;
				}
				outFile << counter << " entries\n\n";
			}
		}
	}

	//this section is organized to output information about the department that is inputted by the user in the command line
	if (strcmp(argv[3], "dept") == 0){
		//creating a vector of Courses class objects, dept_courses, that contain all of the class objects that fall under the department that the user has inputted
		vector<Courses> dept_courses;
		for (int i = 0; i < allCourses.size(); i++){
			if (allCourses[i].getdept() == argv[4])
				dept_courses.push_back(allCourses[i]);
		}

		//error check: checks to make sure that the dept entered by the user is present in the file 
		if (dept_courses.size() == 0)
			outFile << "No data available." << endl;

		//sorting the courses by course code, then by day of the week (earliest first), then by time (earliest first)
		sort(dept_courses.begin(),dept_courses.end(), compare_dept);

		//outputting the chart containing information about courses in the inputted department
		outFile << "Dept " << argv[4] << endl;
		outFile << "Coursenum" << "  " << "Class Title";
		int max_name = max_name_length(dept_courses);
		if (max_name <= 11)
			outFile << "  ";
		else {
			for (int i = 0; i < (max_name-11)+2; i++)
				outFile << " ";
		}
		outFile << "Day";
		int max_day = max_day_length(dept_courses);
		for (int i = 0; i < (max_day-3)+2; i++)
			outFile << " ";
		outFile << "Start Time" << "  " << "End Time" << endl;
		outFile << "---------  "; 
		for (int i = 0; i < max_name; i++)
			outFile << "-";
		outFile << "  ";
		for (int i = 0; i < max_day; i++)
			outFile << "-";
		outFile << "  ";
		outFile << "----------  --------" << endl;
		int counter = 0;
		for (int i = 0; i < dept_courses.size(); i++){
			outFile << dept_courses[i].getcode() << "    " << dept_courses[i].getname();
			for (int j = 0; j < (max_name-dept_courses[i].getname().length())+2; j++)
				outFile << " ";
			outFile << dept_courses[i].getday();
			int length = day_length(dept_courses[i].getday());
			for (int j = 0; j < (max_day-length)+2; j++)
				outFile << " ";
			outFile << dept_courses[i].getstart() << "     " << dept_courses[i].getend() << " " << endl;
					counter += 1;
		}
	outFile << counter << " entries\n\n";
	}

	//this section is organized to output information about all the classes present in an input file
	if (strcmp(argv[3], "custom") == 0){
			//vector of strings, rooms, contains all the rooms present in the input file (checks for duplicates)
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
			//sorts rooms in alphabetical order
			sort(rooms.begin(),rooms.end());
			
			//creating a vector of vectors containing Courses class objects, allrooms_vect, that will contain a vectors of information about all of the rooms present
			//this filling of the vector is completed in the following nested for loop
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
				
				//sorting rooms by day of the week (earliest first), by time (earliest first), then by course code
				sort(allrooms_vect[i].begin(),allrooms_vect[i].end(),compare_room);
				
				//outputting the chart containing information about courses in the inputted department
				outFile << "Room " << rooms[i] << endl;
				outFile << "Dept";
				int max_dept = max_dept_length(allrooms_vect[i]);
				for (int j = 0; j < (max_dept-4)+2; j++)
					outFile << " ";
				outFile << "Coursenum" << "  " << "Class Title";
				int max_name = max_name_length(allrooms_vect[i]);
				if (max_name <= 11)
						outFile << "  ";
				else {
					for (int j = 0; j < (max_name-11)+2; j++)
						outFile << " ";
				}
				outFile << "Day";
				int max_day = max_day_length(allrooms_vect[i]);
				for (int j = 0; j < (max_day-3)+2; j++)
					outFile << " ";
				outFile << "Start Time" << "  " << "End Time" << endl;
				for (int j = 0; j < max_dept; j++)														
					outFile << "-";
				outFile << "  ---------  "; 
				if (max_name < 11)
					outFile << "-----------";
				else{	
					for (int j = 0; j < max_name; j++)
						outFile << "-";
				}
				outFile << "  ";
				for (int j = 0; j < max_day; j++)
					outFile << "-";
				outFile << "  ";
				outFile << "----------  --------" << endl;	
				int counter = 0;
				for (int j = 0; j < allrooms_vect[i].size(); j++){
					outFile << allrooms_vect[i][j].getdept() << "  " << allrooms_vect[i][j].getcode();
					for (int q = 0; q < (11-allrooms_vect[i][j].getcode().length()); q++)
						outFile << " ";
					outFile << allrooms_vect[i][j].getname();
					if (max_name < 11){
						for (int q = 0; q < (11-allrooms_vect[i][j].getname().length())+2; q++)
							outFile << " ";
					}
					else {
						for (int q = 0; q < (max_name-allrooms_vect[i][j].getname().length())+2; q++)
						outFile << " ";
					}
					outFile << allrooms_vect[i][j].getday();
					int length = day_length(allrooms_vect[i][j].getday());
					for (int q = 0; q < (max_day-length)+2; q++)
						outFile << " ";
					outFile << allrooms_vect[i][j].getstart() << "     " << allrooms_vect[i][j].getend() << " " << endl;
					counter += 1;
				}
				outFile << counter << " entries" << endl;
				
				//output at the bottom of each table is a statistic relaying to the user the percentage of courses that room makes up in terms of all of the rooms included in the file
				float percent = ((float)counter / (float)allCourses.size())* 100.00;
				outFile << percent << "% of the courses listed in this file, " << argv[1] << ", are in this room, " << rooms[i] << ".\n\n";
			}
		}
		
outFile.close();
}