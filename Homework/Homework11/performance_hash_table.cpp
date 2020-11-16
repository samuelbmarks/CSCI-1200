#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// defined in performance.cpp
void usage();


void hash_table_test(const string* input_data, int input_count, const string &operation, string *output_data, int &output_count) {

    //cannot/should not sort a hash table
    if (operation == "sort") {        
        cerr << "Cannot perform operation" << endl;
    } 

    else if (operation == "remove_dups_same_order") {
        //constructing table
        unordered_map<string,int> ht;
        
        //keeping track of the index in order to maintain information about the original order
        int index = 0;
        
        for (int i = 0; i < input_count; i++){
            unordered_map<string,int>::iterator itr = ht.find(input_data[i]);
            //insert element if it is not already in table
            if (itr == ht.end()){
                ht.insert(make_pair(input_data[i],index)); //keep track of only one of its locations, ignorng the other instances of the same value
                index++;
            }
        }

        //keeping track of what index to put a value in the output array as well as the number of values in output_data
        output_count = 0;
        
        //for all indicies of the original data, check if any key in the table has that value 
        for (int i = 0; i < (int)ht.size(); i++){
            for (unordered_map<string,int>::iterator itr = ht.begin(); itr != ht.end(); itr++){
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
        //constructing table
        unordered_set<string> ht(input_count);
        
        //inserting values
        for (int i = 0; i < input_count; i++){
            ht.insert(input_data[i]);
        }

        //unordered_set will automatically no allow for duplicates, so merely add all values to output_data
        output_count = 0;
        unordered_set<string>::iterator itr = ht.begin();
        while (itr != ht.end()){
            output_data[output_count] = *itr;
            output_count++;
            itr++;
        }
    } 

    else if (operation == "mode") {        
        //constructing table
        unordered_map<string,int> ht(input_count);
        
        //add values to the table is they are not already in the table
        for (int i = 0; i < input_count; i++){
            unordered_map<string,int>::iterator itr = ht.find(input_data[i]);
            //value is not in table already, insert it
            if (itr == ht.end()){
                ht.insert(make_pair(input_data[i],1));
            }
            //value is already in table, increase the number of occurances
            else{
                itr->second++;
            }
        }

        //track the current mode and mode count/occurances
        int mode_count;
        string mode;

        //looping through table
        unordered_map<string,int>::iterator itr = ht.begin();
        while (itr != ht.end()){
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
