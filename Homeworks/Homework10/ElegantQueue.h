#ifndef __URGENTQ_H_
#define __URGENTQ_H_

#include <cassert>
#include <vector>

using namespace std;

typedef int uq_hook; //Used to point to a location in the urgent heap
typedef int tq_hook; //Used to point to a location in the time heap

//Forward declaration of Job class
class Job;

//Promise to declare stream output operator for internal vector heap representation
ostream& operator<<(ostream& out, const vector<Job*>& heap);

class ElegantQueue{

private:
	vector<Job*> heap; //urgent queue

public:
	//default constructor
	ElegantQueue() {}
	
	//private member functions
	Job*& top();	
	void push(Job*& entry, const string& p);  	
	void percolate_up(unsigned int i, const string& p);	
	Job* pop(const string& p);	
	void percolate_down(unsigned int i, const string& p);	
	void printHeap(ostream& ostr, const string& p);	
	void remove_from_index(uq_hook i, const string& p);
};

#endif