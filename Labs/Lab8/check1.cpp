#include <map>
#include <iostream>
#include <vector>
#include <ostream>
#include <fstream>

using namespace std;

void findModes(vector<int> v){
	if (v.size() == 0) {
		cout << "The vector is empty" << endl;
		return;
	}
	
	// INDEXING METHOD
	map<int, int> counters;
	for (unsigned int i=0; i < v.size(); i++) {
		++counters[v[i]];
	}
	
	int max = 0;
	vector<int> modes;
	map<int, int>::iterator it;
	for (it = counters.begin(); it != counters.end(); ++it) {
		if (it->second > max) {
			max = it->second;
			if (modes.size() > 0) {
				modes.clear();
			}
			modes.push_back(it->first);
		}
		else if (it->second == max) {
			modes.push_back(it->first);
		}
	}
	cout << "Mode(s): ";
	for (unsigned int i = 0; i < modes.size(); i++) {
		cout << modes[i] << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	ifstream vectFile; 
	vectFile.open(argv[1]);
	if (!vectFile.good()){
    	cerr << "Error: Cannot successfully open dictionary file " << argv[1] << endl;
   		exit(1);
  	}
  	int num;
  	vector<int> numbers;

  	while(vectFile>>num){
  		numbers.push_back(num);
  	}
  	vectFile.close();

  	findModes(numbers);

	return 0;
}