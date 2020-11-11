#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;

// defined in performance.cpp
void usage();


void bst_test(const string* input_data, int input_count, const string &operation, string *output_data, int &output_count) {

    if (operation == "sort") {
        //constructing bst
        map<string,int> mp;

        //add values to the table is they are not already in the table
        for (int i = 0; i < input_count; i++){
            map<string,int>::iterator itr = mp.find(input_data[i]);
            //value is not in table already, insert it
            if (itr == mp.end()){
                mp.insert(make_pair(input_data[i],1));
            }
            //value is already in table, increase the number of occurances
            else{
                itr->second++;
            }
        }

        //keeping track of what index to put a value in the output array as well as the number of values in output_data
        output_count = 0;

        //going through map, adding each key to the output the amount of times stored in the value
        map<string,int>::iterator itr = mp.begin();
        while (itr != mp.end()){
            for (int i = 0; i < itr->second; i++){
                output_data[output_count] = itr->first; //add value
                output_count++;
            }
            itr++;
        }
    } 

    else if (operation == "remove_dups_same_order") {
        //constructing bst
        map<string,int> mp;

        //keeping track of the index in order to maintain information about the original order
        int index = 0;
        
        for (int i = 0; i < input_count; i++){
            map<string,int>::iterator itr = mp.find(input_data[i]);
            //insert element if it is not already in table
            if (itr == mp.end()){
                mp.insert(make_pair(input_data[i],index)); //keep track of only one of its locations, ignorng the other instances of the same value
                index++;
            }
        }

        //keeping track of what index to put a value in the output array as well as the number of values in output_data
        output_count = 0;
        
        //for all indicies of the original data, check if any key in the table has that value 
        for (int i = 0; i < (int)mp.size(); i++){
            for (map<string,int>::iterator itr = mp.begin(); itr != mp.end(); itr++){
                //the key contains that value, therefore it can be added to output_data
                if (itr->second == i){
                    output_data[i] = itr->first; //adding value
                    output_count++;
                    break; //value at that location found, go to next index
                }
            }
        }
    } 

    else if (operation == "remove_dups_any_order") {
        //constructing bst
        set<string> st;

        //inserting values
        for (int i = 0; i < input_count; i++){
            st.insert(input_data[i]);
        }

        //set will automatically no allow for duplicates, so merely add all values to output_data
        output_count = 0;
        set<string>::iterator itr = st.begin();
        while (itr != st.end()){
            output_data[output_count] = *itr;
            output_count++;
            itr++;
        }
    } 

    else if (operation == "mode") {
        //constructing bst
        map<string,int> mp;

        //add values to the table is they are not already in the table
        for (int i = 0; i < input_count; i++){
            map<string,int>::iterator itr = mp.find(input_data[i]);
            //value is not in table already, insert it
            if (itr == mp.end()){
                mp.insert(make_pair(input_data[i],1));
            }
            //value is already in table, increase the number of occurances
            else{
                itr->second++;
            }
        }

        //track the current mode and mode count/occurances
        int mode_count = 1;
        string mode;

        //looping through table
        map<string,int>::iterator itr = mp.begin();
        while (itr != mp.end()){
            //occurances of current value is greater than occurances of current mode
            if (itr->second >= mode_count){
                //update mode and mode count
                mode = itr->first;
                mode_count = itr->second;
            }
            itr++;
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
