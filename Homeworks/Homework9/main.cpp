#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

#include "hashTable.h"

using namespace std;

typedef pair<int,vector<string>> pair_type; //pair to store information about the genres, actors, and roles of each movie
typedef map<string,string> Actors; //map to store actor data


// Array of all 64 combinations of Movie object "completition" that could be present for a query Movie (1 represents if the information is present
// and 0 represents if the information is not present) where the 0th index is the title, the 1st index is the year, the 2nd index is the runtime,
// the 3rd index is the genre data, the 4th index is the actor data, and the 5th index is the role data.
// This will be used when inserting all versions of a Movie object into the hash table.
string combos[64] = {"111111","111110","111101","111100","111011","111010","111001","111000","110111","110110","110101","110100","110011","110010",
					"110001","110000","101111","101110","101101","101100","101011","101010","101001","101000","100111","100110","100101","100100",
					"100011","100010","100001","100000","011111","011110","011101","011100","011011","011010","011001","011000","010111","010110",
					"010101","010100","010011","010010","010001","010000","001111","001110","001101","001100","001011","001010","001001","001000",
					"000111","000110","000101","000100","000011","000010","000001","000000"};

//class to store all data about a particular movie
class Movie {
public:
	//constructor
	Movie(string t, string y, string rt, pair_type g, pair_type a, pair_type r) 
		: title(t), year(y), runtime(rt), genres(g), actors(a), roles(r) {}

	//accessors
	string getTitle() const {return title;}
	string getYear() const {return year;}
	string getRuntime() const {return runtime;}
	pair_type getGenres() const {return genres;}
	pair_type getActors() const {return actors;}
	pair_type getRoles() const {return roles;}

	// print function which will be used to print information about a movie, takes in a map of actors information in order to have
	// a comprehensive print and utilize the actors names as opposed to their id's (nconsts)
	void print(Actors& a){
		cout << title << endl;
		cout << year << endl;
		cout << runtime << endl;
		cout << genres.first;
		for (int i = 0; i < genres.first; i++){
			cout << " " << genres.second[i];
		}
		cout << endl;
		cout << actors.first;
		for (int i = 0; i < actors.first; i++){
			cout << " " << a[actors.second[i]] << " (" << roles.second[i] << ")";
		}
		cout << endl;
	}

	// function that returns a bool: true if two Movie objects are the same and false otherwise (compares each element of the object)
	bool operator==(const Movie& m){
		return (title == m.title && year == m.year && year == m.year && runtime == m.runtime && 
			genres == m.genres && actors == m.actors && roles == m.roles);
	}

private:
	//representation
	string title;
	string year;
	string runtime;
	pair_type genres;
	pair_type actors;
	pair_type roles;

};

// key for the hash table: stores a pair, the first element is pair of Movie objects, the first object representing the "partial" movie object and
// the second is the original movie object with all information still there
// the second part of the pair is an unsigned int, intended to store the hash value after the key is hashed
typedef pair<pair<Movie,Movie>,unsigned int> KEY_TYPE;

class hash_Movie_obj {
public:
  	// based off of hash function from http://www.partow.net/programming/hashfunctions/ with clear modifications
  	// the function takes a Movie object, combines all elements of the object into one string and hashes it from there
	unsigned int operator() (const Movie& key) const {
		string toHash = key.getTitle() + key.getYear() + key.getRuntime() + to_string(key.getGenres().first) + //creating a string, toHash
						to_string(key.getActors().first) + to_string(key.getRoles().first);
		for (int i = 0; i < key.getGenres().first; i++){ //adding genres
			toHash += key.getGenres().second[i];
		}
		for (int i = 0; i < key.getActors().first; i++){ //adding actors
			toHash += key.getActors().second[i];
		}
		for (int i = 0; i < key.getRoles().first; i++){ //adding roles
			toHash += key.getRoles().second[i];
		}
		unsigned int hash = 1;
		for(unsigned int i = 0; i < toHash.length(); i++)
			hash ^= ((hash << 5) + toHash[i] + (hash >> 2));

	    return hash;
  } 
};

// function that creates and returns a Movie object based on a combination (ex. 010110,001010,101001)
// where a 0 represents that the element of the object is empty ("?" or a 0). All the elements of the object are passed in
// along with the index of the combos array to access which combination the function is making. The function must pass by 
// value in order to maintain the original value of each element in Movie object. A new movie object is returned.
Movie makeCombos(string t, string y, string rt, pair_type g, pair_type a, pair_type r, unsigned int index){
	if (combos[index][0] == '0'){
		t = "?";
	}
	if (combos[index][1] == '0'){
		y = "?";
	}
	if (combos[index][2] == '0'){
		rt = "?";
	}
	if (combos[index][3] == '0'){
		g.first = 0;
		g.second.clear();
	}
	if (combos[index][4] == '0'){
		a.first = 0;
		a.second.clear();
	}
	if (combos[index][5] == '0'){
		r.first = 0;
		r.second.clear();
	}
	Movie m(t,y,rt,g,a,r);
	return m;
}

int main(){
	typedef hashTable<pair<pair<Movie,Movie>,unsigned int>, hash_Movie_obj> H_TABLE; //creating a typedef for the hash table

	string str; //str to parse cin data

	H_TABLE m; //creating hash table
	Actors actor_map; //map to store actor data

	while (cin>>str){
		//"table_size" command --------------------------------------------------------------------------
		if (str == "table_size"){
			cin>>str;
			m.editSize(stoi(str)); //updating size of the table
		}

		//"occupancy" command ---------------------------------------------------------------------------
		else if (str == "occupancy"){
			cin>>str;
			m.editOcc(stof(str)); //updating occupancy of the table
		}
		
		//"movies" command ------------------------------------------------------------------------------
		else if (str == "movies"){
			string file;
			cin>>str;
			file = str; //movies file
			
			//variables to store Movie data (used later to create Movie class object)
			string title, year, runtime; 
			int numGenres, numActors, numRoles;
			pair_type genres, actors, roles; 
			
			//opening file
			ifstream inputFile;
			inputFile.open(file);
			
			//error checking: making sure file is good
			if (!inputFile.good()){
	    		cerr << "Error: Cannot open input file " << file << endl;
	   			exit(1);
	  		}

	  		//reading in information and storing Movie class objects
	  		string line;
	  		while (inputFile>>line){
	  			title = line; //storing title
	  			inputFile>>line;
	  			year = line; //storing year
	  			inputFile>>line; 
	  			runtime = line; //storing runtime
	  			inputFile>>line; 
	  			numGenres = stoi(line); //storing number of genres
	  			inputFile>>line;
	  			vector<string> tmp; //temporary vector to store genres, actors, and roles
	  			for (int i = 0; i < numGenres; i++){
	  				tmp.push_back(line); //adding genre types to vector
	  				inputFile>>line;
	  			}
	  			genres = make_pair(numGenres,tmp); //store genres
	  			tmp.clear(); //clearing vector
	  			numActors = stoi(line); //storing number of actors
	  			inputFile>>line;
	 			for (int i = 0; i < numActors; i++){
	  				tmp.push_back(line); //adding actors to vector
	  				inputFile>>line;
	  			}
	  			actors = make_pair(numActors,tmp); //storing actors
	  			tmp.clear(); //clearing vector
	  			numRoles = stoi(line); //storing number of roles
	 			for (int i = 0; i < numRoles; i++){
	  				inputFile>>line;
	  				tmp.push_back(line); //adding role types to vector
	   			}
	  			roles = make_pair(numRoles,tmp); //storing roles
	  			Movie movie(title,year,runtime,genres,actors,roles); //Movie object with full movie data
	  			for (unsigned int i = 0; i < 64; i++){ //creating 64 movie class objects with varying degrees of completion
	  				Movie comb = makeCombos(title,year,runtime,genres,actors,roles,i); //Movie object of the specifications outlined in combination i
	  				KEY_TYPE key = make_pair(make_pair(comb,movie),0); //making the key to insert into hash table 
	  				m.insert(key); //insert object
	  			}
	  		}
		}

		//"actors" command ------------------------------------------------------------------------------
		else if (str == "actors"){
			string file;
			cin>>str;
			file = str; //actors file

			//opening file
			ifstream inputFile;
			inputFile.open(file);

			//error checking: making sure file is good
			if (!inputFile.good()){
		    	cerr << "Error: Cannot open input file " << file << endl;
		   		exit(1);
		  	}

		  	//reading in information about actors
		  	string line;
		  	while (inputFile>>line){
		  		string actorID, name; //variables to store information
		  		actorID = line; //storing actorID
		  		inputFile>>line; 
		  		name = line; //storing actor name
		  		actor_map.insert(make_pair(actorID,name)); //add to map
			}
		}

		//"query" command -------------------------------------------------------------------------------
		else if (str == "query"){ 			
			//variables to store Movie data (used later to create Movie class object)
			string title, year, runtime; 
			int numGenres, numActors, numRoles;
			pair_type genres, actors, roles; 

			cin>>str;
   			title = str; //storing title
  			cin>>str;
  			year = str; //storing year
  			cin>>str;
  			runtime = str; //storing runtime
  			cin>>str;
  			numGenres = stoi(str); //storing number of genres
  			cin>>str;
  			vector<string> tmp; //temporary vector to store genres, actors, and roles
  			for (int i = 0; i < numGenres; i++){
  				tmp.push_back(str); //adding genre types to vector
  				cin>>str;
  			}
  			genres = make_pair(numGenres,tmp); //store genres
  			tmp.clear(); //clearing vector
  			numActors = stoi(str); //storing number of actors
  			cin>>str;
 			for (int i = 0; i < numActors; i++){
  				tmp.push_back(str); //adding actors to vector
  				cin>>str;
  			}
  			actors = make_pair(numActors,tmp); //storing actors
  			tmp.clear(); //clearing vector
  			numRoles = stoi(str); //storing number of roles
 			for (int i = 0; i < numRoles; i++){
  				cin>>str;
  				tmp.push_back(str); //adding role types to vector
   			}
  			roles = make_pair(numRoles,tmp); //storing roles
  			Movie movie1 = Movie(title,year,runtime,genres,actors,roles); //creating Movie class object
  			KEY_TYPE q_key = make_pair(make_pair(movie1,movie1),0); //creating key type
  			int index = m.find(q_key); //using find to find the index in the hash table where all the matches are located (-1 is not found)

  			if (index == -1){ //no results are found
  				cout << "No results for query." << endl;
  			} 
  			else{ //a result is found, so print all elements at that index
  				m.printIndex(index, actor_map);
  			}
		}
		
		//"quit" command --------------------------------------------------------------------------------
		else if (str == "quit"){ //end/break/done/yay
			break;
		}
	}
}