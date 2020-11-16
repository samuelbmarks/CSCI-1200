#ifndef __URGENTQ_H_
#define __URGENTQ_H_

#include <cassert>
#include <vector>

using namespace std;

typedef int uq_hook; //int to point to a location in the heap

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
ostream& operator<<(ostream& out, const vector<Job*>& heap);

class UrgentQueue{

private:
	vector<Job*> u_heap; //priority queue of job objects

public:
	//default constructor
	UrgentQueue() {}

	//private member functions
	Job*& top();
	void push(Job*& entry);
  	void percolate_up(unsigned int i);
  	Job* pop();
  	void percolate_down(unsigned int i);
  	void printHeap(ostream& ostr);
  	void remove_from_index(uq_hook i);
};

#endif
