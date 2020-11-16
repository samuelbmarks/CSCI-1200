#include "Job.h"
#include "UrgentQueue.h"

//function that returns a pointer to the Job at the top of the queue  
Job*& UrgentQueue::top(){
	assert(!u_heap.empty()); //assuring queue isn't empty
	return u_heap[0]; 
}

//function that thats a Job pointer and inserts that Job into the queue
void UrgentQueue::push(Job*& entry){
	u_heap.push_back(entry); //adding entry to back of the queue
	unsigned int i = u_heap.size()-1; //setting i to back of queue
    
    //updating the hooks and queue pointers
    entry->urgent_hook = i;
	entry->priority_ptr = this;
    
    percolate_up(i); //percolate up from i
}

//function that organizes the internal structure of the queue (from bottom up)
void UrgentQueue::percolate_up(unsigned int i){
    //while i is not 0 and the Jobs's priority is greater than its parent's priority
    while (i != 0 && u_heap[i]->getPriority() > u_heap[(i-1)/2]->getPriority()){
        swap(u_heap[i],u_heap[(i-1)/2]); //swap locations in queue
        
        //update hooks
        u_heap[i]->urgent_hook = i;  
        u_heap[(i-1)/2]->urgent_hook = (i-1)/2;  
        
        i = (i-1)/2; //update i
    }
}

//function that removes the top Job pointer of the queue and returns that pointer 
Job* UrgentQueue::pop(){
    assert(!u_heap.empty()); //assuring queue is not empty
    Job* tmp = u_heap[0]; //setting temp to front pointer to preserve value
    swap(u_heap[0],u_heap[u_heap.size()-1]); //swap locations in queue
    
    //update hooks
    u_heap[0]->urgent_hook = 0;
    u_heap.pop_back();
    
    percolate_down(0); //percolate down from top
    return tmp; //return removed value
}

//function that organizes the internal structure of the queue (from top down)
void UrgentQueue::percolate_down(unsigned int i){
	//queue of this size does not need to be reordered
    if (u_heap.size() <= 1){
        return;
    }

    //while element at i has at least a left child
    while (i <= (u_heap.size()/2)-1){
		unsigned int child = 0;

		//if element has a right child and its right is greater than the left
        if (2*i+2 < u_heap.size() && u_heap[2*i+2]->getPriority() > u_heap[2*i+1]->getPriority())
		    child = 2*i+2; //choose right
		else 
		    child = 2*i+1; //choose left

		//if the Job pointer's child's priority is greater than its own, switch 
        if (u_heap[child]->getPriority() > u_heap[i]->getPriority()){
		    swap(u_heap[child],u_heap[i]); //swap locations in queue
            
            //update hooks
            u_heap[child]->urgent_hook = child;
            u_heap[i]->urgent_hook = i;         
            
            i = child; //update i
		} 
		else
		    break;
    }
}

//function that prints heap
void UrgentQueue::printHeap(ostream& out){
    unsigned int num = u_heap.size();
    out << "UQ " << num  << " jobs:" << endl;
    for (unsigned int i = 0; i < u_heap.size(); ++i )
    	out << "\t" << u_heap[i];
}

//function that takes an index and removes that Job pointer at that index
void UrgentQueue::remove_from_index(tq_hook i){
    assert(!u_heap.empty()); //assuring queue isn't empty
    vector<Job*> temp; //creating a vector to store values that are kept
    
    //adding all the values in original queue to new vector except the one at the given index
    for (unsigned int index = 0; index < u_heap.size(); index++){
        if ((int)index != i){
            temp.push_back(u_heap[index]); //added Job pointer
            temp[temp.size()-1]->urgent_hook = temp.size()-1; //updating hook as it goes
        }
    } 
    u_heap = temp; //setting heap equal to temp vector
    percolate_down(0); //reordering queue
}