/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.s
*/
#include <vector>
#include <cassert>
#include "Rope.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
//GOOD
rope_iterator& rope_iterator::operator++(){
	if (ptr_->right != NULL) { // find the leftmost child of the right node
		ptr_ = ptr_->right;
			while (ptr_->left != NULL) 
				ptr_ = ptr_->left;
	} 
	else { // go upwards along right branches... stop after the first left
		while (ptr_->parent != NULL && ptr_->parent->right == ptr_)  
			ptr_ = ptr_->parent; 
		ptr_ = ptr_->parent;
	}
	return *this;
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	if (!root)
		return rope_iterator(NULL);
	Node* p = root;
	while (p->left)
		p = p->left;
	return rope_iterator(p);
}

Node* Rope::copy_rope(Node* old_root, Node* the_parent) {
    if (old_root == NULL) 
    	return NULL;
    Node* answer = new Node;
    answer->value = old_root->value;
    answer->left = copy_rope(old_root->left,answer);
    answer->right = copy_rope(old_root->right,answer);
    answer->parent = the_parent;
    answer->weight = old_root->weight;
    return answer;
}

void Rope::destroy_rope(Node*& p){
 //    if (!p) return;
	// destroy_rope(p->right);
 //    destroy_rope(p->left);
 //    delete p;
}

Rope::Rope(){
	root = NULL;
	size_ = 0;
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	root = p;
	size_ = p->weight;
	while (p->right){
		p = p->right;
		size_ += p->weight;
	}
}

Rope::~Rope(){
	this->destroy_rope(root);
}

Rope::Rope(const Rope& r){
	size_ = r.size_;
	root = this->copy_rope(r.root, NULL);
}

Rope& Rope::operator= (const Rope& r){
	if (&r != this){
		this->destroy_rope(root);
		root = this->copy_rope(r.root, NULL);
		size_ = r.size_;
	}
	return *this;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
	if (!root) //check to make sure the rope is valid
		return false;
	if (i > size_-1 || i < 0){ //error check: cannot access index that does not exist
		//std::cerr << "Index " << i << " is outside the scope of the Rope" << std::endl;
		return false;
	}
	Node* p = root; //start at the root
	while(!is_leaf(p)){ //loop until node pointer reaches a leaf
		if (i < p->weight && p->left){ //move left
			p = p->left;
		}
		else if (i >= p->weight && p->right){ //moving right
			i = i - p->weight;
			p = p->right;
		}
		else{ //error check: cannot move right or left if left or right does not exist
			return false;
		}
	}
	c = p->value[i]; //finding the value
	return true; //value is found, return true
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	Node* new_root = new Node; //create a new node to be the new root
	Rope new_rope(r); //create a copy of the rope that is passed in
	new_root->weight = size_; //update the weight of the new root
	new_root->left = root; //assign the left and right of the new root to be the root nodes the of left and right ropes 
	new_root->right = r.root;
	root->parent = r.root->parent = new_root; //set the new root as the old roots parents
	root = new_root; //make the new root the current root
	Node* p = root; // update the size
	while (p->right){
		p  = p->right;
		size_ += p->weight;
	}
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	if (i > size_-1 || i < 0 || j > size_-1 || j < 0 || j < i){ //error check: cannot access range of indices outside scope of Rope
		//std::cerr << "Invalid range" << std::endl;
		return false;
	}
	s.clear(); //assuring the string is cleared
	char start; //char to hold characters to be added to the substring s
	while (i <= j){ //loop until i reaches j
		index(i,start); //making sure index is valid each time
		s.push_back(start); //adding new character to string
		i++; 
	}
	return true; //return true after substring is successfully found
}

void Rope::split_rope(int index_, std::vector<Rope>& ropes_){
	Node* r = root;
	while (r){
		if (is_leaf(r) && r->parent->right == r){
			r->parent->right = NULL; //disconnect node and make it its own rope
			r->parent = NULL;
			Rope new_rope(r);
			ropes_.push_back(new_rope); //add it to rope list
			//new_rope.print(std::cout);
			new_rope.destroy_rope(new_rope.root);
			break;
		}
		else if (is_leaf(r)){ 
			break;
		}
		else if (index_ < r->weight && r->right == NULL){
			r = r->left;
		}
		else if (index_ < r->weight){ 
			r->right->parent = NULL;
			Rope new_rope(r->right); //make a new rope with r->right has the root
			r->right = NULL;
			ropes_.push_back(new_rope); //add it to rope list
			//new_rope.print(std::cout);
			new_rope.destroy_rope(new_rope.root); 
			r = r->left;
		}
		else if (index_ >= r->weight){
			index_ = index_ - r->weight;
			r = r->right;
		}
	}
}

void Rope::adjust_size(){
	size_ = 0;
	for (rope_iterator it = begin(); it!= end(); it++){
		if(is_leaf(it.ptr_)){
			size_ += it.ptr_->weight;
		}
	}
	// for(rope_iterator it = begin(); it!= end(); it++){
	// 	if(is_leaf(it.ptr_)){
	// 		it.ptr_->weight = it.ptr_->value.size();
	// 	}
	// 	else{
	// 		it.ptr_->weight = 0;
	// 		for(rope_iterator itr = begin(); itr!= end(); itr++){
	// 			if (it.ptr_ == itr.ptr_)
	// 				break;
	// 			if(is_leaf(itr.ptr_)){
	// 				it.ptr_->weight += itr.ptr_->weight;
	// 			}
	// 		}
	// 	}
	// }
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	if (i < 1 || i >= size_){ //cannot split at index 0 (or less) because no split would be made there, and cannot split at an index that does not exist
		return *this;
	}
	std::vector<Rope> ropes; //list of rope objects that will need to be concatted
	int index = i - 1; //all indices that will be on the left rope
	Node* p = root;
	while(!is_leaf(p)){ //checking to see if node needs to be split or not
		if (i < p->weight && p->left){
			p = p->left;
		}
		else {
			i = i - p->weight;
			p = p->right;
		}
	}
	if (i == 0){ //split is to occur between two nodes, so no need to split the node
		split_rope(index,ropes); //function to split the rope
	}
	else{ //split is in the middle of the node, so the node must be split before we can split the rope as a whole
		Node* node1 = new Node; //create two new nodes
		Node* node2 = new Node;
		for (int x = 0; x < i; x++){ //set the value of the new left node to all chars to the left of the given index in the original node
			node1->value.push_back(p->value[x]);
			node1->weight++;
		}
		for (unsigned int x = i; x < p->value.size(); x++){ //set the value of the new right node to all chars at and to the right of the given index in the original node
			node2->value.push_back(p->value[x]);
			node2->weight++;;
		}
		p->value.clear(); //clear the value of the original node
		p->left = node1; //attach new nodes accordingly
		p->right = node2;
		node1->parent = p;
		node2->parent = p;
		p->weight = node1->weight; //update the weight of the new node
		if (p->parent->left == p){
			p->parent->weight = p->weight;
		}
		split_rope(index,ropes); //function to split the rope
	}

	if (ropes.size() == 0){ //no cuts were made, therefore no changes were made in the original rope
		return *this;
	}
	else if (ropes.size() == 1){ //only one cut was made
		rhs = ropes[0];
		rhs.adjust_size(); //adjusting size and weight
		adjust_size(); 
		return *this;
	}
	else { //multiple cuts were made and the right side of the rope needs to be put together (concat)
		Rope final_rope(ropes[ropes.size()-1]);

		for (int i = int(ropes.size()-2); i >= 0; i--){ //concatinating the ropes together
			final_rope.concat(ropes[i]);
		}
		rhs = final_rope;
		rhs.adjust_size(); //adjusting size and weight
		adjust_size();
		return *this;
	}
}
