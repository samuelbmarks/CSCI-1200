#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

#include "hashTable.h"

using namespace std;

typedef pair<int,vector<string>> pair_type;
typedef map<string,string> Actors;

//class to store all data about a particular movie
class Movie {
public:
	//constructor
	Movie(string t, int y, int rt, pair_type g, pair_type a, pair_type r) 
		: title(t), year(y), runtime(rt), genres(g), actors(a), roles(r) {}

	//accessors
	string getTitle() const {return title;}
	int getYear() const {return year;}
	int getRuntime() const {return runtime;}
	pair_type getGenres() const {return genres;}
	pair_type getActors() const {return actors;}
	pair_type getRoles() const {return roles;}

	void print(){
		cout << "Title: " << title << endl;
		cout << "Year: " << year << endl;
		cout << "Runtime: " << runtime << endl;
		cout << "Genres: ";
		for (int i = 0; i < genres.first; i++){
			cout << genres.second[i] << " ";
		}
		cout << endl;
		cout << "Actors: ";
		for (int i = 0; i < actors.first; i++){
			cout << actors.second[i] << " ";
		}
		cout << endl;
		cout << "Roles: ";
		for (int i = 0; i < roles.first; i++){
			cout << roles.second[i] << " ";
		}
		cout << endl << endl;
	}
	bool operator==(const Movie& m){
		return ((title == m.title || m.title == "?") && (year == m.year || m.year == 0) &&
			(year == m.year || m.year == 0) && (runtime == m.runtime || m.runtime == 0) &&
			(genres == m.genres || m.genres.first == 0) && (actors == m.actors || m.actors.first == 0) && 
			(roles == m.roles || m.roles.first == 0));
	}

private:
	//representation
	string title;
	int year;
	int runtime;
	pair_type genres;
	pair_type actors;
	pair_type roles;

};

class hash_Movie_obj {
public:
  	//http://www.partow.net/programming/hashfunctions/
	unsigned int operator() (const Movie& key) const {
	string toHash = key.getTitle() + to_string(key.getYear()) + to_string(key.getRuntime());
	for (int i = 0; i < key.getGenres().first; i++){
		toHash += key.getGenres().second[i];
	}
	for (int i = 0; i < key.getActors().first; i++){
		toHash += key.getActors().second[i];
	}
	for (int i = 0; i < key.getRoles().first; i++){
		toHash += key.getRoles().second[i];
	}
	unsigned int hash = 1;
	for(unsigned int i = 0; i < toHash.length(); i++)
		hash ^= ((hash << 5) + toHash[i] + (hash >> 2));

    return hash;
  } 
};

typedef hashTable<Movie, hash_Movie_obj> H_TABLE;

int main(){
	string str;
	
	int size = 0;
	float occupancy;

	while (cin>>str){
		//"table_size" command --------------------------------------------------------------------------
		if (str == "table_size"){
			cin>>str;
			size = stoi(str);
		}
		//"occupancy" command ---------------------------------------------------------------------------
		if (str == "occupancy"){
			cin>>str;
			occupancy = stof(str);
		}
		
		H_TABLE m(size,occupancy); 
		
		//"movies" command ------------------------------------------------------------------------------
		if (str == "movies"){
			cout << "movies guy" << endl << endl; 

			string file;
			cin>>str;
			file = str; //movies file
			
			//variables to store Movie data (used later to create Movie class object)
			string title; 
			int year, runtime, numGenres, numActors, numRoles;
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
	  			year = stoi(line); //storing year
	  			inputFile>>line; 
	  			runtime = stoi(line); //storing runtime
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
	  			Movie movie = Movie(title,year,runtime,genres,actors,roles); //creating Movie class object
	  			//movie.print();
	  			m.insert(movie); 
	  		}
  			m.print(cout);
		}

		//"actors" command ------------------------------------------------------------------------------
		else if (str == "actors"){
			cout << "actors guy" << endl << endl;
			Actors actor_map; //map to store actor data

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
			cout << "query guy" << endl << endl;
			
			//variables to store Movie data (used later to create Movie class object)
			string title; 
			int year, runtime, numGenres, numActors, numRoles;
			pair_type genres, actors, roles; 

			cin>>str;
   			title = str; //storing title
  			cin>>str;
  			if (str == "?"){
  				year = 0; //storing year as 0 if it is not provided
  			}
  			else{
  				year = stoi(str); //year is provided, store  normally
  			}
  			cin>>str;
  			if (str == "?"){
  				runtime = 0; //storing runtime as 0 if it is not provided
  			}
  			else{
  				runtime = stoi(str); //runtime provided, store normally
  			}
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
  			Movie movie = Movie(title,year,runtime,genres,actors,roles); //creating Movie class object
  			//movie.print();

		}
		
		//"quit" command --------------------------------------------------------------------------------
		else if (str == "quit"){
			cout << "quit guy" << endl << endl;
			break;
		}

		//error check -----------------------------------------------------------------------------------
		else{
			//error checking: making sure the input is valid
			//cerr << "Error: \"" << str << "\" is an invalid command" << endl;
			//exit(1);
		}
	}
}