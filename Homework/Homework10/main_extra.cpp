#include <cassert>
#include <fstream> //For file I/O
#include <iostream> //For std::cerr
#include <string> //For parsing
#include <ctime> //For std::time_t
#include <list>
#include "ElegantQueue.h"
#include "Job_extra.h"

using namespace std;

//Prints a heap represented as a vector to out
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap){
    out << heap.size() << " jobs:" << std::endl;
    for(std::size_t i=0; i<heap.size(); i++){
        out << "\t" << heap[i];
    }
    return out;
}

//Add a job to both queues
void AddToQueue(ElegantQueue& eq1, ElegantQueue& eq2, Job* job){
    eq1.push(job,"time");
    eq2.push(job,"urgency");
}

//Remove the highest urgency Job from the queues
void GetNextUrgent(ElegantQueue& eq){
    Job* tmp = eq.pop("urgency");
    tmp->removeFromTime();
}

//Remove the oldest Job from the queues
void GetNextTime(ElegantQueue& eq){
    Job* tmp = eq.pop("time");
    tmp->removeFromUrgent();
}

int main(int argc, char** argv){
    if(argc != 3){
        std::cerr << "Correct usage is " << argv[0] << " [input file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream infile(argv[1]);
    if(!infile){
        std::cerr << "Could not open " << argv[1] << " for reading!";
        return -1;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Could not open " << argv[2] << " for writing!";
        return -1;
    }

    /* "jobs" must be a list so that we don't reallocate, 
     * since that would COPY jobs. We will pass around pointers
     * instead of duplicating jobs when we want to interact with the queues. */
    std::list<Job*> jobs; 
    ElegantQueue eq1; //time
    ElegantQueue eq2; //urgency

    std::string token;

    while(infile >> token){
        if(token == "add-job"){
            int priority;
            std::time_t timestamp;
            infile >> priority >> timestamp;
            jobs.push_back(new Job(priority,timestamp));
            AddToQueue(eq1,eq2,jobs.back());
            cout << jobs[0] << endl;
        }
        else if(token == "print-by-urgent"){
            eq2.printHeap(outfile,"urgency"); 
        }
        else if(token == "print-by-time"){
            eq1.printHeap(outfile,"time");
        }
        else if(token == "print-next-urgent"){
            const Job* j = eq2.top();
            cout << j;
        }
        else if(token == "print-next-age"){
            const Job* j = eq1.top();
            cout << j;
        }
        else if(token == "remove-next-urgent"){
            GetNextUrgent(eq2);
        }
        else if(token == "remove-next-age"){
            GetNextTime(eq1);
        }
        else{
            std::cerr << "Invalid/unexpected input token " << token << std::endl;
            return -1;
        }
    }

    //Make sure that we didn't copy jobs during any operations
    Job validator(0,0);
    assert(validator.getID()-1 == (int)jobs.size());

    for(std::list<Job*>::iterator it = jobs.begin(); it!=jobs.end(); it++){
        delete *it;
    }

    return 0;
}
