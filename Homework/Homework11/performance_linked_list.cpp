#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

// defined in performance.cpp
void usage();


void list_test(const string* input_data, int input_count, const string &operation, string *output_data, int &output_count) {

    //construting list
    list<string> lst;
    
    //adding values to list
    for (int i = 0; i < input_count; i++) 
        lst.push_back(input_data[i]);

    if (operation == "sort") {
        //sorting list
        lst.sort();
        
        //setting output count to same as input count
        output_count = input_count;
        
        //add all values to output_data (already ordered)
        list<string>::iterator itr = lst.begin();
        int i = 0;
        while (itr != lst.end()){
            output_data[i] = *itr;
            itr++;
            i++;
        }
    } 

    else if (operation == "remove_dups_same_order") {
        //keeping track of what index to put a value in the output array as well as the number of values in output_data
        output_count = 0;
        
        //loop through list of values
        list<string>::iterator itr = lst.begin();
        while (itr != lst.end()){
            bool dup = false;
            //check if value to be added is already in output
            for (int i = 0; i < output_count; i++) {
                //value is there, do not add and break
                if (*itr == output_data[i]) {
                    dup = true;
                    break;
                }
            }
            //value was not found, add it
            if (!dup) {
                output_data[output_count] = *itr;
                output_count++;
            }
            itr++;
        }
    } 

    else if (operation == "remove_dups_any_order") {
        //sort list first
        lst.sort();
        
        //keeping track of what index to put a value in the output array as well as the number of values in output_data
        output_count = 0;
        
        //keep track of previous value
        list<string>::iterator itr = lst.begin();
        string tmp = *itr;
        itr++;

        //loop through list of values
        while (itr != lst.end()){
            //if current is not equal to the previous value, add it to output
            if (tmp != *itr){
                output_data[output_count] = tmp;
                output_count++;
            }
            //reassign previous value and move to next current value
            tmp = *itr;
            itr++;
        }

        //check if last value belongs in output
        if (tmp != output_data[output_count]){
            output_data[output_count] = tmp;
            output_count++;
        }
    } 

    else if (operation == "mode") {
        //sort values first
        lst.sort();

        //tracking the mode, current count, and the occurances of the current mode
        int current_count = 1;
        string mode;
        int mode_count = 0;
        
        //tracking current and previous values with two iterators
        list<string>::iterator curr = lst.begin();
        curr++;
        list<string>::iterator prev = lst.begin();

        //loop through list
        while (curr != lst.end()){
            //current and previous values are the same, increase occurances of current
            if (*curr == *prev){
                current_count++;
            }
            //if the current value does not equal the previous, assess if the previous values are the new mode
            else if (current_count >= mode_count){
                mode = *prev;
                mode_count = current_count;
                current_count = 1;
            }
            //no new mode, start with the next value
            else{
                current_count = 1;
            }
            curr++;
            prev++;
        }

        //final check to assess if the previous values are the new mode
        if (current_count >= mode_count){
            mode = *prev;
            mode_count = current_count;
        }

        //output data
        output_count = 1;
        output_data[0] = mode;
    } 

    else {
        cerr << "Error: Unknown operation: " << operation << endl;
        usage();
    }
}
