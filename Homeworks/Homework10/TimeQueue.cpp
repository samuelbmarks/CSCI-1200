#include "Job.h"
#include "TimeQueue.h"
#include "UrgentQueue.h"

using namespace std;

//function that returns a pointer to the Job at the top of the queue  
Job*& TimeQueue::top(){
    assert(!t_heap.empty()); //assuring queue isn't empty
    return t_heap[0]; 
}

//function that thats a Job pointer and inserts that Job into the queue
void TimeQueue::push(Job*& entry){
    t_heap.push_back(entry); //adding entry to back of the queue
    unsigned int i = t_heap.size()-1; //setting i to back of queue
    
    //updating the hooks and queue pointers
    t_heap[i]->time_hook = i; 
    t_heap[i]->time_ptr = this; 

    percolate_up(i); //percolate up from i
}

//function that organizes the internal structure of the queue (from bottom up)
void TimeQueue::percolate_up(unsigned int i){
    //while i is not 0 and the Jobs's time is less than its parent's time
    while (i != 0 && t_heap[i]->getTime() < t_heap[(i-1)/2]->getTime()){
    	swap(t_heap[i],t_heap[(i-1)/2]); //swap locations in queue
        
        //update hooks
        t_heap[i]->time_hook = i;
        t_heap[(i-1)/2]->time_hook = (i-1)/2;
    	
        i = (i-1)/2; //update i
    }
}

//function that removes the top Job pointer of the queue and returns that pointer 
Job* TimeQueue::pop(){
    assert(!t_heap.empty()); //assuring queue is not empty
    Job* tmp = t_heap[0]; //setting temp to front pointer to preserve value
    swap(t_heap[0],t_heap[t_heap.size()-1]); //swap locations in queue
    
    //update hooks
    t_heap[0]->time_hook = 0;
    t_heap.pop_back();
    
    percolate_down(0); //percolate down from top
    return tmp; //return removed value
}

//function that organizes the internal structure of the queue (from top down)
void TimeQueue::percolate_down(unsigned int i){
    //queue of this size does not need to be reordered
    if (t_heap.size() <= 1){
        return;
    }

    //while element at i has at least a left child
    while (i <= (t_heap.size()/2)-1){
		unsigned int child = 0;

        //if element has a right child and its right is less than the left
        if (2*i+2 < t_heap.size() && t_heap[2*i+2]->getTime() < t_heap[2*i+1]->getTime())
		    child = 2*i+2; //choose right
		else 
		    child = 2*i+1; //choose left

        //if the Job pointer's child's priority is less than its own, switch 
		if (t_heap[child]->getTime() < t_heap[i]->getTime()){
		    swap(t_heap[child],t_heap[i]); //swap locations in queue
            
            //update hooks
            t_heap[child]->time_hook = child;
            t_heap[i]->time_hook = i;
            
            i = child; //update i
		} 
		else
		    break;
    }
}

//function that prints heap
void TimeQueue::printHeap(ostream& out){
    unsigned int num = t_heap.size();
    out << "TQ " << num  << " jobs:" << endl;
    for (unsigned int i=0; i < t_heap.size(); ++i )
        out << "\t" << t_heap[i];
}

//function that takes an index and removes that Job pointer at that index
void TimeQueue::remove_from_index(tq_hook i){
    assert(!t_heap.empty()); //assuring queue isn't empty
    vector<Job*> temp; //creating a vector to store values that are kept
    
    //adding all the values in original queue to new vector except the one at the given index
    for (unsigned int index = 0; index < t_heap.size(); index++){
        if ((int)index != i){
            temp.push_back(t_heap[index]); //added Job pointer
            temp[temp.size()-1]->time_hook = temp.size()-1; //updating hook as it goes
        }
    } 
    t_heap = temp; //setting heap equal to temp vector
    percolate_down(0); //reordering queue
}
