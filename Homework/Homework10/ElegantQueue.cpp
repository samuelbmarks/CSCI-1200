#include "Job_extra.h"
#include "ElegantQueue.h"

using namespace std;

//function that returns a pointer to the Job at the top of the queue  
Job*& ElegantQueue::top(){
    assert(!heap.empty()); //assuring queue isn't empty
    return heap[0]; 
}

//function that thats a Job pointer and inserts that Job into the queue
void ElegantQueue::push(Job*& entry, const string& p){
    heap.push_back(entry); //adding entry to back of the queue
    unsigned int i = heap.size()-1; //setting i to back of queue
    
    //updating the hooks and queue pointers
    if (p == "time"){
        heap[i]->time_hook = i;
        heap[i]->elegant_ptr = this; 
        percolate_up(i,"time"); //percolate up from i
    }
    else{
        heap[i]->urgent_hook = i;
        heap[i]->elegant_ptr = this; 
        percolate_up(i,"urgent"); //percolate up from i
    }
}

//function that organizes the internal structure of the queue (from bottom up)
void ElegantQueue::percolate_up(unsigned int i, const string& p){
    //while i is not 0 and the Jobs's time is less than its parent's time
    if (p == "time"){
        while (i != 0 && heap[i]->getTime() < heap[(i-1)/2]->getTime()){
            swap(heap[i],heap[(i-1)/2]); //swap locations in queue
            
            //update hooks
            heap[i]->time_hook = i;
            heap[(i-1)/2]->time_hook = (i-1)/2;
            
            i = (i-1)/2; //update i
        }
    }
    else {
        while (i != 0 && heap[i]->getPriority() > heap[(i-1)/2]->getPriority()){
            swap(heap[i],heap[(i-1)/2]); //swap locations in queue
            
            //update hooks
            heap[i]->urgent_hook = i;
            heap[(i-1)/2]->urgent_hook = (i-1)/2;
            
            i = (i-1)/2; //update i
        }
    }
}

//function that removes the top Job pointer of the queue and returns that pointer 
Job* ElegantQueue::pop(const string& p){
    assert(!heap.empty()); //assuring queue is not empty
    Job* tmp = heap[0]; //setting temp to front pointer to preserve value
    swap(heap[0],heap[heap.size()-1]); //swap locations in queue
    
    //update hooks
    if (p == "time"){
        heap[0]->time_hook = 0;
         heap.pop_back();
        percolate_down(0,"time");//percolate down from top
        return tmp; //return removed value
    }
    else{
        heap[0]->urgent_hook = 0;
        heap.pop_back();
        percolate_down(0,"urgency");//percolate down from top
        return tmp; //return removed value
    }   
}

//function that organizes the internal structure of the queue (from top down)
void ElegantQueue::percolate_down(unsigned int i, const string& p){
    //queue of this size does not need to be reordered
    if (heap.size() <= 1){
        return;
    }

    //while element at i has at least a left child
    while (i <= (heap.size()/2)-1){
		unsigned int child = 0;

        if (p == "time"){
            //if element has a right child and its right is less than the left
            if (2*i+2 < heap.size() && heap[2*i+2]->getTime() < heap[2*i+1]->getTime())
    		    child = 2*i+2; //choose right
    		else 
    		    child = 2*i+1; //choose left

            //if the Job pointer's child's time is less than its own, switch 
            if (heap[child]->getTime() < heap[i]->getTime()){
    		    swap(heap[child],heap[i]); //swap locations in queue
                
                //update hooks
                heap[child]->time_hook = child;
                heap[i]->time_hook = i;
                
                i = child; //update i
    		} 
    		else
    		    break;
        }
        else {
            //if element has a right child and its right is greater than the left
            if (2*i+2 < heap.size() && heap[2*i+2]->getPriority() > heap[2*i+1]->getPriority())
                child = 2*i+2; //choose right
            else 
                child = 2*i+1; //choose left

            //if the Job pointer's child's priority is greater than its own, switch 
            if (heap[child]->getPriority() > heap[i]->getPriority()){
                swap(heap[child],heap[i]); //swap locations in queue
                
                //update hooks
                heap[child]->urgent_hook = child;
                heap[i]->urgent_hook = i;
                
                i = child; //update i
            } 
            else
                break;
        }
    }
}

//function that prints heap
void ElegantQueue::printHeap(ostream& out, const string& p){
    unsigned int num = heap.size();
    if (p == "time")
        out << "TQ " << num  << " jobs:" << endl;
    else 
        out << "UQ " << num  << " jobs:" << endl;
    for (unsigned int i=0; i < heap.size(); ++i )
        out << "\t" << heap[i];
}

//function that takes an index and removes that Job pointer at that index
void ElegantQueue::remove_from_index(tq_hook i, const string& p){
    assert(!heap.empty()); //assuring queue isn't empty
    vector<Job*> temp; //creating a vector to store values that are kept
    
    //adding all the values in original queue to new vector except the one at the given index
    for (unsigned int index = 0; index < heap.size(); index++){
        if ((int)index != i){
            temp.push_back(heap[index]); //added Job pointer
            if (p == "time")
                temp[temp.size()-1]->time_hook = temp.size()-1; //updating hook as it goes
            else 
                temp[temp.size()-1]->urgent_hook = temp.size()-1; //updating hook as it goes
        }
    } 
    heap = temp;//setting heap equal to temp vector
    if (p == "time")
        percolate_down(0,"time"); //reordering queue
    else         
        percolate_down(0,"urgency"); //reordering queue
}