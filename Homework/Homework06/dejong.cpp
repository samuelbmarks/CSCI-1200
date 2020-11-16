
vector<vector<char>> single_solution(const vector<vector<char>>& original_grid, vector<vector<char>> updated_grid, const list<Word>& directory_, const list<unsigned int>& constraints_){
	if(constraints_.size() == 0)
		return updated_grid;

	for (list<string>::iterator cw_itr = current_words.begin(); cw_itr != current_words.end(); cw_itr++){
		list<Loc> location = find_word(original_grid,*cw_itr);
		if (location.size() > 0){
			for (list<Loc>::iterator l_itr = location.begin(); l_itr != location.end(); l_itr++){
				updated_grid[l_itr->row][l_itr->col] = '$';
			}
			num_solutions++;
			dict_.remove(*cw_itr);
			current_words.remove(*cw_itr);
			constra-ints_.pop_front();
			num_solutions=solutionHelper(original_grid, updated_grid, dict_, constraints_, current_words);
		}
		else{
			dict_.remove(*cw_itr);
			num_solutions=solutionHelper(original_grid, updated_grid, dict_, constraints_);
		}
	}
}

int solutions(const vector<vector<char>>& original_grid, vector<vector<char>> updated_grid, list<string>& dict_, const list<unsigned int>& constraints_){
	int num_solutions = 0;

	if (constraints_.size() == 0){
		bool done = check_word_count(updated_grid, dict_);
		if (done == true){
			print_grid(updated_grid);
		}
		else{
			return 0;
		}
		return num_solutions;
	}





	//here


	//create a list of all words from dict with size == constraint[0]
		//for each word in list, call find_word
		//find word in dict with a length of a constraint
		//use find_word to find the word in grid (return location)

		//IF WORD IS FOUND (return list size > 0)
		//go through returned list and update locations in updated_grid (set used characters to $)
		//remove word from dict_ and constraint from constraints_ (if found)
		//call solutions(original_grid, newly updated_grid, dict_, contraints_)

		//IF WORD IS NOT FOUND (returned list size is 0)
		//remove word from dict
		//call it again as is (only thing that changes is dict)


	return 0;
}
