#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Time {
public:
	Time();
	Time(int hour, int minute, int second);

	//accessors
	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	//modifiers
	void setHour(int hour); 
	void setMinute(int minute);
	void setSecond(int second);

	void printAMPM();
private:
	int HOUR;
	int MINUTE;
	int SECOND;
};