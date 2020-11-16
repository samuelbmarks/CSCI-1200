#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <algorithm>
#include <list>
#include <cstring>


using namespace std;

//GLOBAL VARIABLE: Variable to store a list of grids that meet the constraints provided.
//============================================================================================================================================
list<vector<vector<char>>> list_grids;

//class Loc: Class that stores a row and column integer value, representing a location in the grid.
//============================================================================================================================================
class Loc {
public:
  	Loc(int r = 0, int c = 0) : row(r), col(c) {}
 	int row, col;
};

//class Word: Class that stores a word (string) and a list of locations/points within a grid that each character in the word appears (list<Loc>).
//============================================================================================================================================
class Word {
public:
	Word(string w, list<Loc> p) : word(w), points(p) {}
  	string word;
  	list<Loc> points;
};

//operator==: Helper function to determine if two Word class objects are equal.
//============================================================================================================================================
bool operator== (const Word& w1, const Word& w2) { 
  return w1.word == w2.word && w1.points == w2.points; 
}

//operator==: Helper function to determine if two Loc class objects are equal.
//============================================================================================================================================
bool operator== (const Loc& l1, const Loc& l2) { 
  return l1.row == l2.row && l1.col == l2.col; 
}

//print_grid: Function that takes a vector<vector<char>>, updated_grid, and prints the elements of it.
//============================================================================================================================================
void print_grid(const vector<vector<char>>& updated_grid){
	cout << "Board:" << endl;
	for (unsigned int i = 0; i < updated_grid.size(); i++){
		for (unsigned int j = 0; j < updated_grid[i].size(); j++){
	    	cout << updated_grid[i][j];
	    }
		cout << endl;
	}
}

//find_word: Function that takes a vector<vector<char>>, grid_, and a string, word_, and finds the location of that word in the grid,  
//			 returning a list of Word objects taking into account if a word appears twice in grid.
//============================================================================================================================================
list<Word> find_word(const vector<vector<char>>& grid_, const string& word_){
	//list of Word objects, holding the word and its location (could contain multiple objects for multiple occurances of the word within the grid)
	list<Word> words_points;

	//list of Loc objects, holding location of each letter in the desired word
	list<Loc> word_location;

	//checking if the word is longer than the board both horizontally and vertically, in which the word cannot be found
	if (word_.length() > grid_.size() && word_.length() > grid_[0].size())
		return words_points;

	//flags for breaking out of nested for loop so loop does not continue needlessly
	bool exit1 = false;	
	bool exit2 = false;
	bool exit3 = false;
	
	//checking downward only if the word is longer than board horizontally
	if (word_.length() > grid_[0].size()){
		for (unsigned int i = 0; i < grid_.size(); i++){
			for (unsigned int j = 0; j < grid_[i].size(); j++){
				//checking if length of the word would not fit vertically at a given vertical index
				if (i + word_.length() > grid_.size()){
					exit1 = true;
					break;
				}
				else{
					//making a "dummy" word in order to check it against word_
					string dummy;
					unsigned int counter = i;
					while (dummy.size() < word_.length()){
						dummy.push_back(grid_[counter][j]);
						word_location.push_back(Loc(counter,j)); //document the words location
						counter++;
					} 
					//if the "dummy" word is equal to word_, a Word object is made and it is added to words_points
					if (dummy == word_){
						words_points.push_back(Word(word_,word_location)); 
						word_location.clear(); //reset location to empty
					}
					else
						word_location.clear(); //reset location to empty
				}
			}
			if (exit1 == true)
				break;
		}
		return words_points;
	}

	//checking rightward only
	else if (word_.length() > grid_.size()){
		for (unsigned int i = 0; i < grid_.size(); i++){
			for (unsigned int j = 0; j < grid_[i].size(); j++){
				if (j + word_.length() > grid_[i].size()){
					exit2 = true;
					break;
				}
				else{
					//making a "dummy" word in order to check it against word_
					string dummy;
					unsigned int counter = j;
					while (dummy.size() < word_.length()){
						dummy.push_back(grid_[i][counter]);
						word_location.push_back(Loc(i,counter)); //document the words location
						counter++;
					} 
					//if the "dummy" word is equal to word_, a Word object is made and it is added to words_points
					if (dummy == word_){
						words_points.push_back(Word(word_,word_location));
						word_location.clear(); //reset location to empty
					}
					else
						word_location.clear(); //reset location to empty
				}
			}
			if (exit2 == true)
				break;
		}
		return words_points;
	}

	//checking in both directions
	else{
		for (unsigned int i = 0; i < grid_.size(); i++){
			for (unsigned int j = 0; j < grid_[i].size(); j++){
				//checking if word is too long in both directions
				if ((i + word_.length() > grid_.size()) && (word_.length() > grid_[i].size())){
					exit3 = true;
					break;
				}
				//checking downward (if applicable)
				if (i + word_.length() <= grid_.size()){
					//making a "dummy" word in order to check it against word_
					string dummy;
					unsigned int counter = i;
					while (dummy.size() < word_.length()){
						dummy.push_back(grid_[counter][j]);
						word_location.push_back(Loc(counter,j)); //document the words location
						counter++;
					} 
					//if the "dummy" word is equal to word_, a Word object is made and it is added to words_points
					if (dummy == word_){
						words_points.push_back(Word(word_,word_location));
						word_location.clear(); //reset location to empty
					}
					else 
						word_location.clear(); //reset location to empty
				}
				//checking rightward (if applicable)
				if (j + word_.length() <= grid_[i].size()){
					//making a "dummy" word in order to check it against word_
					string dummy;
					unsigned int counter = j;
					while (dummy.size() < word_.length()){
						dummy.push_back(grid_[i][counter]);
						word_location.push_back(Loc(i,counter)); //document the words location						
						counter++;
					} 
					//if the "dummy" word is equal to word_, a Word object is made and it is added to words_points
					if (dummy == word_){
						words_points.push_back(Word(word_,word_location));
						word_location.clear(); //reset location to empty
					}
					else
						word_location.clear(); //reset location to empty
				}
			}
			if (exit3 == true)
				break;
		}
		return words_points;
	}	
}

//print_directory: Helper funnction that takes a list of Word class objects, directory_, and prints the contents of the list, which is all words 
// 				   and their locations/points within the grid.
//============================================================================================================================================
void print_directory(const list<Word>& directory_){
	list<Word>::const_iterator d = directory_.begin();
	list<Loc>::const_iterator l;
	while (d != directory_.end()){
		cout << d->word << endl;
		l = d->points.begin();
		while (l != d->points.end()){
			cout << l->row << " " << l->col << endl;;
			l++;
		}
		d++;
	}	
}

//make_directory: Function that takes a vector<vector<char>>, grid_, and a list of strings, dict_, and utilizes the find_word function to 
//				  create a directory (list of Word objects) of every word in the dictionary and its location in the grid taking into account 
//				  if a word has multiple locations within the grid, and returns that directory.
//============================================================================================================================================
list<Word> make_directory(const vector<vector<char>>& grid_, const list<string>& dict_){
	list<Word> word_;
	list<Word> directory_;

	list<string>::const_iterator d = dict_.begin();
	while (d != dict_.end()){
		word_ = find_word(grid_,*d);
		list<Word>::const_iterator w = word_.begin();
		while (w != word_.end()){
			directory_.push_back(*w);
			w++;
		}
		word_.clear();
		d++;
	}
	return directory_;	
}

//check_word_count: Function that takes a vector<vector<char>>, updated_grid, and a list of Word objects, directory_, and determines if the 
//					board is valid and generates a solution that truly satisfies the constraints by assuring that all of words that has not 
// 					been used already in the board have not been "accidently" generated within solution, resulting in more words than the amount required.
//============================================================================================================================================
bool check_word_count(const vector<vector<char>>& updated_grid, const list<Word>& directory_){
	bool good = true; //bool to determine whether the grid meets all of the constraints
	list<Word>::const_iterator d = directory_.begin();
	list<Loc>::const_iterator p;
	//nested while that checks if each point in each word is completely used within a given final solution, meaning that the word appears "accidentally"
	while (d != directory_.end()){
		unsigned int counter = 0;
		p = d->points.begin();
		while (p != d->points.end()){
			if (updated_grid[p->row][p->col] == '#')
				counter++;
			p++;
		}
		// if no letter in the word appears as a '#' in the grid, then that word indirectly appears, therefore the grid fails the test
		if (counter == 0){
			good = false;
			return good;
		}
		d++;
	}	
	return good;
}

//update_grid: Function that takes a vector<vector<char>>, grid_, and a Word object, word_, and copies grid_, puts that word in the grid, 
//			   and returns the new grid.
//============================================================================================================================================
vector<vector<char>> update_grid(const vector<vector<char>>& grid_, const Word& word_){
	vector<vector<char>> to_update = grid_;
	list<Loc>::const_iterator l_itr = word_.points.begin();
	unsigned int counter = 0;
	while (l_itr != word_.points.end() && counter < word_.word.length()){
		to_update[l_itr->row][l_itr->col] = word_.word[counter];
		l_itr++;
		counter++;
	}
	return to_update;
}

//update_directory: Function that takes a list of Word objects, directory_, and a Word object, word_, and copies the list, removes that word 
//					object from the list, and returns the new list.
//============================================================================================================================================
list<Word> update_directory(const list<Word>& directory_, const Word& word_){
	list<Word> to_update = directory_;
	list<Word>::iterator d_itr = to_update.begin();
	list<Loc>::iterator l_itr;
	while (d_itr != to_update.end()){
		if (*d_itr == word_){
			d_itr = to_update.erase(d_itr);
		}
		else
			d_itr++;
	}
	return to_update;
}


//update_cons: Function that takes a list of integers, constraints_, and a unsigned integer, con_, and makes a copy of the list and removes
//			   the constraints that was met from the list. If the constraint is not present in the constraint list, the list is cleared,
//			   a "dummy" unsigned int 999 is pushed back into the list, and the list is returned.
//============================================================================================================================================
list<unsigned int> update_cons(const list<unsigned int>& constraints_, unsigned int con_){
	list<unsigned int> to_update = constraints_;
	list<unsigned int>::iterator c_itr = to_update.begin();
	//checking to see if the constraint is present in the list
	int num = count(to_update.begin(),to_update.end(),con_);
	if (num == 0){
		to_update.clear();
		to_update.push_back(999);
		return to_update;
	}
	while (c_itr != to_update.end()){
		if (*c_itr == con_){
			c_itr = to_update.erase(c_itr);
			break; //deleting first instance of the number only
		}
		else
			c_itr++;
	}
	return to_update;
}

//print_constraints: Helper function that prints a list of integer constraints.
//============================================================================================================================================
void print_constraints(const list<unsigned int>& cons){
	list<unsigned int>::const_iterator c = cons.begin();
	while (c != cons.end()){
		cout << "CONSTRAINT: " << *c << " ";
		c++;
	}
	cout << endl;
}

//all_solutions: RESCURSIVE function that takes an vector<vector<char>>, updated_grid, a list of Word objects, directory, and a list of
//				 unsigned integers, constraints. The base case is whether the constraints list is empty. This will ultimately end the recursion.
//				 If this is the case, check_word_count is used to check the validity of the board. If the board is valid, it is added to the 
//				 global variable, list_grid. If the constraints list is not empty, for each word in the directory, that word is checked to see 
//				 if it would satisfy a constraint. If not, false is returned. If so, the board is updated with that word and that word is removed 
//				 from the directory, and the function is called again recursively.
//============================================================================================================================================			             
bool all_solutions(const vector<vector<char>>& updated_grid, const list<Word>& directory_, const list<unsigned int>& constraints_,unsigned int& c){
	//check if constraints is empty (base case)
	if (constraints_.size() == 0){
		//bool to check to see if the final board doesn't include more words than required
		bool done = check_word_count(updated_grid, directory_);
		if (done == true){
			int counter = 0;
			counter = count(list_grids.begin(),list_grids.end(),updated_grid); //checking to assure the final board does not match any previous boards that were made
			if (counter == 0){
				list_grids.push_back(updated_grid); //if it doesn't match any previous boards, it is pushed back into list_grids
				c++;
			}
			return false; //returning false will allow the program to run until all solutions are found
		}
		else{
		 	return false;
		}
	}
	//for loop to go through every word in the directory
	for (list<Word>::const_iterator d_itr = directory_.begin(); d_itr != directory_.end(); d_itr++){
		list<unsigned int> new_cons = update_cons(constraints_,d_itr->word.length());
		list<unsigned int>::iterator n_itr = new_cons.begin();
		//checking to make sure that the constraint was present in the constraints list
		if ((new_cons.size() == 1) && (*n_itr == 999)){
			return false;
		}
		vector<vector<char>> new_grid = update_grid(updated_grid,*d_itr); //updating the grid
		list<Word> new_direct = update_directory(directory_,*d_itr); //updating the directory
		if (all_solutions(new_grid,new_direct,new_cons,c)) 
			return true;
	}
	return false;
}

//one_solution: RESCURSIVE function that takes an vector<vector<char>>, updated_grid, a list of Word objects, directory, and a list of
//				unsigned integers, constraints. The base case is whether the constraints list is empty. This will ultimately end the recursion.
//				If this is the case, check_word_count is used to check the validity of the board. If the board is valid, it is added to the 
//				global variable, list_grid. If the constraints list is not empty, for each word in the directory, that word is checked to see 
//				if it would satisfy a constraint. If not, false is returned. If so, the board is updated with that word and that word is removed 
//				from the directory, and the function is called again recursively.
//============================================================================================================================================
bool one_solution(const vector<vector<char>>& updated_grid, const list<Word>& directory_, const list<unsigned int>& constraints_){
	//check if constraints is empty (base case)
	if (constraints_.size() == 0){
		//bool to check to see if the final board doesn't include more words than required
		bool done = check_word_count(updated_grid, directory_);
		if (done == true){
			list_grids.push_back(updated_grid); //adding final grid to global variable, list_grids
			return true; //returning true here will end the recursion after finding one correct board
		}
		else{
		 	return false;
		}
	}
	//for loop to go through every word in the directory
	for (list<Word>::const_iterator d_itr = directory_.begin(); d_itr != directory_.end(); d_itr++){
		list<unsigned int> new_cons = update_cons(constraints_,d_itr->word.length());
		list<unsigned int>::iterator n_itr = new_cons.begin();
		//checking to make sure that the constraint was present in the constraints list
		if ((new_cons.size() == 1) && (*n_itr == 999)){
			return false;
		}
		vector<vector<char>> new_grid = update_grid(updated_grid,*d_itr); //updating the grid
		list<Word> new_direct = update_directory(directory_,*d_itr); //updating the directory
		if (one_solution(new_grid,new_direct,new_cons)) 
			return true;
	}
	return false;
}

//main: Reads in and stores the data from the files and utilizies functions to provide a the solution requested by the other command arguments.
//============================================================================================================================================
int main(int argc, char* argv[]){
	//READING IN THE DICTIONARY FILE AND STORING IT IN A LIST
	//========================================================================================================================================
	list<string> dict; //list to store words in dictionary file
	string word;
	ifstream dictFile; 
	dictFile.open(argv[1]); //opening the dictionary file
	
	//checking if dictionary file successfully opened
	if (!dictFile.good()){
    	cerr << "Error: Cannot successfully open dictionary file " << argv[1] << endl;
   		exit(1);
  	}

  	//filling dict list with words in dictionary
  	while(dictFile>>word){
  		dict.push_back(word);
  	}

  	//closing dictionary file
  	dictFile.close();

	//READING IN THE GRID AND THE CONSTRAINTS FROM THE GRID FILE AND STORING IT IN A VECTOR OF VECTOR OF CHARACTERS AND A LIST RESPECTIVELY
	//========================================================================================================================================
  	vector<vector<char>> grid; //vector to store grid in grid file
	string line;
	ifstream gridFile; 
	gridFile.open(argv[2]); //opening the grid file
	
	//checking if grid file successfully opened
	if (!gridFile.good()){
    	cerr << "Error: Cannot successfully open initial grid file " << argv[2] << endl;
   		exit(1);
  	}
  	
  	list<unsigned int> constraints; //list to store constraints
  	//filling grid vector and constraints list from grid file
  	while (gridFile>>line) {
		if (line[0] == '!') //ignoring if the first character in the line is a '!'
			continue;
		else if (line[0] == '+')
			constraints.push_back(stoi(line.substr(1,line.length()-1))); //taking only the number on the line (accounting for if it is two digits) and converting it to an int
		else{
			vector<char> letters;
			for (unsigned int i = 0; i < line.length(); i++){
				letters.push_back(line[i]);
			}
			grid.push_back(letters);
		}
	}	
	
	//SETTING UP ARGUMENTS THAT WILL BE PASSED IN TO SOLUTION FUNTIONS
	//========================================================================================================================================
	//creating a blank grid to fill in
	vector<vector<char>> blank = grid;
	for (unsigned int i = 0; i < blank.size(); i++){
		for (unsigned int j = 0; j < blank[0].size(); j++)
			blank[i][j] = '#';
	}

	//making a list of word objects
	list<Word> directory = make_directory(grid,dict);

	unsigned int counter = 0;
	
	//ADDITIONAL COMMAND LINE ARGUMENTS- SOLUTION AND OUTPUT MODE
	//========================================================================================================================================
	//if the users wants only one solution but only the number of solutions (which will onlyh result in 1 if there is at least one solution)
	if ((strcmp(argv[4],"count_only") == 0) && (strcmp(argv[3], "one_solution") == 0)){
		one_solution(blank,directory,constraints);
		cout << "Number of solution(s): " << list_grids.size() << endl;
	}
	
	//if the user wants all solutions but only the number of solutions
	else if ((strcmp(argv[4],"count_only") == 0) && (strcmp(argv[3], "all_solutions") == 0)){
		all_solutions(blank,directory,constraints,counter);
		cout << "Number of solution(s): " << list_grids.size() << endl;
	}
	
	//if the user wants only one solution and that solution to by printed
	else if ((strcmp(argv[4],"print_boards") == 0) && (strcmp(argv[3], "one_solution") == 0)){
		one_solution(blank,directory,constraints);
		cout << "Number of solution(s): " << list_grids.size() << endl;
		if (list_grids.size() > 0){
			list<vector<vector<char>>>::const_iterator v_itr = list_grids.begin();
			print_grid(*v_itr);
		}
	}

	//if the user wants all solutions and all solutions to be printed
	else if ((strcmp(argv[4],"print_boards") == 0) && (strcmp(argv[3],"all_solutions") == 0)){
		all_solutions(blank,directory,constraints,counter);
		cout << "Number of solution(s): " << list_grids.size() << endl;
		if (list_grids.size() > 0){
			list<vector<vector<char>>>::const_iterator v_itr = list_grids.begin();
			while (v_itr != list_grids.end()){
				print_grid(*v_itr);
				v_itr++;
			}
		}
	}

	//if the user inputs an invalid solution mode
	else if ((strcmp(argv[3], "one_solution") != 0) && (strcmp(argv[3], "all_solutions") != 0)){
		cerr << "Error: Invalid solution mode " << argv[3] << endl;
		exit(1);
	}

	//if the user inputs an invalid output mode
	else{
		cerr << "Error: Invalid output mode " << argv[4] << endl;
		exit(1);
	}
}