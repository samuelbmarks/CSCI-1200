//"Hop lists"
#include <iostream>

using namespace std;

//IMPORTANT: THIS IS NOT TEMPLATED
class Node{
public:
	Node(int v) : val(v), next_(NULL), prev_odd_(NULL) {}
	Node(int v, Node* next) : val(v), next_(next), prev_odd_(NULL) {}
	int val;
	Node* next_;
	Node* prev_odd_;
};

//Forward declarations
void DeleteList(Node*& head);
void PrintListForward(Node* head);
void PrintHopListBackwards(Node* tail);
void TestList(int size);

//TODO: Fill this function in. You may write your own helper functions if you want
//You should NOT assume tail is initialized
void AddPrevOddPointers(Node* head, Node*& tail){
	if(!head){
		tail = NULL;
		return;
	}
	Node* tmp = head->next_;
	if(tmp){
		tmp = tmp->next_;
		if(tmp){
			tmp->prev_odd_ = head;
			tail = tmp;
			AddPrevOddPointers(tmp, tail);
		}
		else if(!head->prev_odd_){
			tail = NULL;
		}
	}
	else if(!head->prev_odd_){ //Size 1 list
		tail = NULL;
	}
}

//TODO: Fill this function in. You may write your own helper functions if you want
//You should NOT assume tail is initialized
void AddPrevOddPointersIterative(Node* head, Node*& tail){
	if(!head || !head->next_ || !head->next_->next_){
		tail = NULL;
		return;
	}
	Node* tmp = head->next_->next_; 
	while(tmp->next_ && tmp->next_->next_){
		tmp->prev_odd_ = head;
		if(!tmp->next_ || !tmp->next_->next_){
			break;
		}
		head = tmp;
		tmp = tmp->next_->next_;
	}
	tmp->prev_odd_ = head;
	tail = tmp;
}

int main(){
	std::cout << "Testing size 10" << std::endl;
	TestList(10);
	std::cout << "Testing size 11" << std::endl;
	TestList(11);
	std::cout << "Testing size 1" << std::endl;
	TestList(1);
	std::cout << "Testing size 2" << std::endl;
	TestList(2);
	std::cout << "Testing size 3" << std::endl;
	TestList(3);
	std::cout << "Testing empty list" << std::endl;
	Node* head = NULL;
	Node* tail;
	AddPrevOddPointers(head, tail);
	PrintHopListBackwards(tail);
	return 0;
}

//Simple destructor
void DeleteList(Node*& head){
	if(!head){
		return;
	}
	while(head){
		DeleteList(head->next_);
		delete head;
		head = NULL;
	}
}

//Starts at the given node and loops forward printing every value
void PrintListForward(Node* head){
	std::cout << "Printing forward list:";
	while(head){
		std::cout << " " << head->val;
		head = head->next_;
	}
	std::cout << std::endl;
}

//Starts at the given node and loops backwards printing every tail value
//This should be the same as every other value. Also handles NULL tail.
void PrintHopListBackwards(Node* tail){
	if(!tail){
		std::cout << "List has less than 3 nodes." << std::endl;
		return;
	}
	std::cout << "Printing backwards every-other list:";
	while(tail){
		std::cout << " " << tail->val;
		tail = tail->prev_odd_;
	}
	std::cout << std::endl;
}

//Do not change this function.
void TestList(int size){
	//Do the recursive version
	Node* head = new Node(1);
	Node* tmp = head;
	for(int i=2; i<=size; i++){
		tmp->next_ = new Node(i);
		tmp = tmp->next_;
	}

	PrintListForward(head);
	Node* tail;
	AddPrevOddPointers(head,tail);
	PrintHopListBackwards(tail);
	std::cout << std::endl;
	DeleteList(head);

	//Now do the iterative version
	head = new Node(1);
	tmp = head;
	for(int i=2; i<=size; i++){
		tmp->next_ = new Node(i);
		tmp = tmp->next_;
	}

	PrintListForward(head);
	Node* tail2;
	AddPrevOddPointersIterative(head,tail2);
	PrintHopListBackwards(tail2);
	std::cout << std::endl;

	DeleteList(head);
}