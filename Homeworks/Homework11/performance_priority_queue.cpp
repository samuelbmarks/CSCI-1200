#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

// defined in performance.cpp
void usage();


void priority_queue_test(const string* input_data, int input_count, const string &operation, string *output_data, int &output_count) {

    //constructing priority queue
    priority_queue<string,vector<string> > pq(input_data,input_data+input_count);

    if (operation == "sort") {
        //same amount of values going in and out
        output_count = input_count;

        //priority queue orders values in a reverse sort order, so assign output values in reverse order
        for (unsigned int i = pq.size()-1; i >= 0; i--){
            output_data[i] = pq.top(); //add the top value
            if (pq.size() > 1)
                pq.pop(); //remove the top value to access the next value (if possible)
            else
                break; //no values left to add
        }
    } 

    else if (operation == "remove_dups_same_order"){
        cerr << "Cannot perform operation" << endl;         
    } 

    else if (operation == "remove_dups_any_order"){
       
        //keeping track of what index to put a value in the output array as well as the number of values in output_data
        output_count = 0;
        
        //storing and removing the top value ("prev")
        string prev = pq.top();
        pq.pop();

        //adding the top value to output
        output_data[output_count] = prev;
        output_count++;
        
        //while there are values left in queue
        while (pq.size() > 0){
            //if the current value is not equal to the previous, add it to output
            if (pq.top() != prev){
                output_data[output_count] = pq.top();
                output_count++;
            }
            //reassign prev and remove it in order to access next value in queue
            prev = pq.top(); 
            pq.pop();
        }
    } 

    else if (operation == "mode"){
        //storing the "previous value"
        string prev = pq.top();
        pq.pop();

        //tracking the mode, current count, and the occurances of the current mode
        string mode;
        int current_count = 1;
        int mode_count = 0;

        //while values are still in the queue
        while (pq.size() > 0){
            //if the current value equals the previous, increase its count
            if (pq.top() == prev){ 
                current_count++;
            }
            //if the current value does not equal the previous, assess if the previous values are the new mode
            else if (current_count >= mode_count){
                mode = prev;
                mode_count = current_count;
                current_count = 1;
            }
            //no new mode, start with the next value
            else{
                current_count = 1;
            }
            //reassign prev and remove it in order to access next value in queue
            prev = pq.top();
            pq.pop();
        }
        
        //final check to assess if the previous values are the new mode
        if (current_count >= mode_count){
            mode = prev;
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
