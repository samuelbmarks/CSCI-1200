#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Node{
public:
	Node() : left{NULL}, right{NULL} {}
	Node* left;
	Node* right;
	int value;
};

bool shape_match(Node* t1, Node* t2){
	cout << t1->value << " " << t2->value << endl;
	if (!t1->left && !t2->left && t1->right && t2->right){
		return true;
	}

	if ((t1->left && !t2->left) || (!t1->left && t2->left))
		return false;
	if ((t1->right && !t2->right) || (!t1->right && t2->right)){
		cout << "test" << endl;
		return false;
	}
	if (t1->left && t2->left){
		//cout << "RC1" << endl;
		shape_match(t1->left,t2->left);
	}
	if (t1->right && t2->right){
		//cout << "RC2" << endl;
		//cout << t2->right->value << endl;
		shape_match(t1->right,t2->right);
	}
	cout << "test2" << endl;
	//return true;
}

int main(){
	Node* a = new Node; //a tree
	a->value = 5;
	a->left = new Node;
	a->left->value = 7;
	a->right = new Node;
	a->right->value = 13;
	a->left->left = new Node;
	a->left->left->value = 6;
	a->left->right = new Node;
	a->left->right->value = 11;
	a->right->right = new Node;
	a->right->right->value = 21;

	Node* b = new Node; //b tree
	b->value = 17;
	b->left = new Node;
	b->left->value = 9;
	b->right = new Node;
	b->right->value = 22;
	b->left->left = new Node;
	b->left->left->value = 10;
	b->left->right = new Node;
	b->left->right->value = 1;
	b->right->right = new Node;
	b->right->right->value = 8;
	b->right->right->right = new Node;
	b->right->right->right->value = 100;


	bool good = shape_match(a,b);
	if (good)
		cout << "Same shape" << endl;
	else
		cout << "Not the same shape" << endl;

	return 0;
}
