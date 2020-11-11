#include <iostream>
#include "Point2D.h"
#include "Rectangle.h"
#include <vector>

using namespace std;

int main(){

	//INITIALIZING:
	//initializing lower right point
	Point2D p1(4,4);
	//intializing upper right point
	Point2D p2(10, 10);

	//initializing rectangle
	Rectangle r1(p1, p2);

	//initializing lower right point, second rectangle
	Point2D p3(7,7);
	//intializing upper right point, second rectangle
	Point2D p4(13, 13);

	//initializing second rectangle
	Rectangle r2(p3, p4);

	//printing rectangle
	print_rectangle(r1);
	print_rectangle(r2);

	cout << "\n";

	//TEST 1: IS POINT WITHIN
	Point2D is_in(5, 7); //point that should return true
	if (r1.is_point_within(is_in))
		cout << "TEST 1 (TRIAL 1) PASSED" << endl;
	else
		cout << "TEST 1 (TRIAL 1) FAILED" << endl;

	Point2D not_in(2, 12); //point that should not return true
	if (!r1.is_point_within(not_in))
		cout << "TEST 1 (TRIAL 2) PASSED" << endl;
	else
		cout << "TEST 1 (TRIAL 2) FAILED" << endl;

	Point2D edge(7,4); //point on the edge of rectangle, should return true
	if (r1.is_point_within(edge))
		cout << "TEST 1 (TRIAL 3) PASSED" << endl;
	else
		cout << "TEST 1 (TRIAL 3) FAILED" << endl;
	
	cout << "\n";

	//TEST 2: ADDING POINTS
	Point2D testp1(5,7);
	Point2D testp2(8,11);
	Point2D testp3(2,8);
	Point2D testp4(6,11);


	if (r1.add_point(testp1)) //should add point and return true
		cout << "TEST 2 (TRIAL 1) PASSED" << endl;
	else
		cout << "TEST 2 (TRIAL 1) FAILED" << endl;

	print_rectangle(r1); //printing to make sure point was added

	cout << "\n";

	if (!r1.add_point(testp3)) //should NOT add point and return false
		cout << "TEST 2 (TRIAL 2) PASSED" << endl;
	else
		cout << "TEST 2 (TRIAL 2) FAILED" << endl; 

	print_rectangle(r1); //printing to make sure point was NOT added

	cout << "\n";

	if (r2.add_point(testp2)) //should add point and return true
		cout << "TEST 2 (TRIAL 3) PASSED" << endl;
	else
		cout << "TEST 2 (TRIAL 3) FAILED" << endl; 

	print_rectangle(r2); //printing to make sure point was added

	cout << "\n";

	if (!r2.add_point(testp4)) //should NOT add point and return false
		cout << "TEST 2 (TRIAL 4) PASSED" << endl;
	else
		cout << "TEST 2 (TRIAL 4) FAILED" << endl; 

	print_rectangle(r2); //printing to make sure point was NOT added

	cout << "\n";
	
	//TEST 3: POINTS IN BOTH
	Point2D tp1(7,10); //creating points that can be added to both rectangles
	Point2D tp2(8,9);

	Point2D tp3(5,9); //creating points that will not be added to both rectangles
	Point2D tp4(10,12);

	r1.add_point(tp1);
	r1.add_point(tp2);
	r1.add_point(tp3);
	r1.add_point(tp4);
	r2.add_point(tp1);
	r2.add_point(tp2);
	r2.add_point(tp3);
	r2.add_point(tp4);

	//this should only print out tp1 and tp2, as they are the points that could be added to both
	vector<Point2D> pib;
	pib = points_in_both(r1,r2);
	if (pib.size() == 2){
		cout << "TEST 3 PASSED" << endl;
	}
	else{
		cout << "TEST 3 FAILED" << endl;
	} 

	cout << "Points in Both Rectangles:" << endl; //printing to make sure contents of pib is corrent
	for (int i = 0; i < pib.size(); i++)
	   		cout << pib[i].x() << "," << pib[i].y() << endl; 

	cout << "\n";

}