#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#include "time.h"

Time::Time(){
	HOUR = 0;
	MINUTE = 0; 
	SECOND = 0;
}

Time::Time(int hour, int minute, int second){
	HOUR = hour;
	MINUTE = minute;
	SECOND = second;
}

int Time::getHour()const {return HOUR;}
int Time::getMinute() const{return MINUTE;}
int Time::getSecond() const{return SECOND;}

void printAMPM(){
	if (hour > 12){
		hour = hour - 12;
		cout << 0 << hour << ":";
		if (minute < 10){
			cout << 0 << minute << ":";
			if (second < 10){
				cout << 0 << second << "PM";
			}
			else{
				count << second << "PM";
			}
		}
		else{
			cout << minute << ":";
			if (second < 10){
				cout << 0 << second << "PM";
			}
			else{
				count << second << "PM";
		}
	}
	else if (hour < 12){
		if (hour == 11||hour == 10){
			cout << hour << ":";
			if (minute < 10){
			cout << 0 << minute << ":";
				if (second < 10){
					cout << 0 << second << "AM";
				}
				else{
					count << second << "AM";
				}
			}
			else{
				cout << minute << ":";
				if (second < 10){
					cout << 0 << second << "AM";
			}
				else{
					count << second << "AM";
		}
		else{
			cout << 0 << hour << ":";
			if (minute < 10){
			cout << 0 << minute << ":";
				if (second < 10){
					cout << 0 << second << "AM";
				}
				else{
					count << second << "AM";
				}
			}
			else{
				cout << minute << ":";
				if (second < 10){
					cout << 0 << second << "AM";
				}
				else{
					count << second << "AM";
				}

		}

	}
	else if (hour == 12){
		cout << 12 << ":";
		if (minute < 10){
			cout << 0 << minute << ":";
				if (second < 10){
					cout << 0 << second << "AM";
				}
				else{
					count << second << "AM";
				}
			}
			else{
				cout << minute << ":";
				if (second < 10){
					cout << 0 << second << "AM";
				}
				else{
					count << second << "AM";
				}
			}	
		}
	}	
}