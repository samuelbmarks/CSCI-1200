#include <iostream>

using namespace std;

unsigned int num_paths(int x, int y){
    if (x == 0 || y == 0)
		return 1;
	return num_paths(x-1,y) + num_paths(x,y-1);
}

int main(){

	int start_x;
	int start_y;
	
	cout << "Starting X Location: ";
	cin >> start_x;
	cout << "Starting Y Location: ";
	cin >> start_y;

	int paths = num_paths(start_x, start_y);
	cout << paths << endl;

}