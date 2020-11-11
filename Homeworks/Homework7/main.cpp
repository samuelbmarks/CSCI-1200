#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath> 
#include <vector>
#include <algorithm>
#include <set>
#define earthRadiusKm 6371.0
#ifndef M_PI
#define M_PI 3.14
#endif

using namespace std;

//TODO: You must fill in all ?????? with the correct types.
typedef unsigned int ID_TYPE; //Type for user IDs
typedef pair<float,float> COORD_TYPE; //Type for a coordinate (latitude and longitude)
typedef map<ID_TYPE,vector<ID_TYPE>> ADJ_TYPE; //Adjacency Lists type
typedef map<ID_TYPE,COORD_TYPE> GEO_TYPE; //Positional "dictionary"

//my own additional typedefs
typedef map<int,vector<ID_TYPE>> RDIST_TYPE; //Type for distances (rounded down) and the user IDs at that distance 
typedef map<double,vector<ID_TYPE>> DIST_TYPE; //Type for distances and the user IDs at that distance 

//Function forward declarations. DO NOT CHANGE these. 
double deg2rad(double deg);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile);
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile);
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance);
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree);
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations, 
                                std::ofstream& outfile, const ID_TYPE& start_id, 
                                double max_distance);
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin, 
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it, unsigned int offset);


// DO NOT CHANGE THIS FUNCTION
int main(int argc, char** argv){
    ADJ_TYPE adj_lists;
    GEO_TYPE locations;

    if(argc != 3){
        std::cout << "Correct usage is " << argv[0] 
                  << " [commands file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream commands(argv[1]);
    if(!commands){
        std::cerr << "Problem opening " << argv[1] << " for reading!" 
                  << std::endl;
        return -1;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Problem opening " << argv[2] << " for writing!" 
                  << std::endl;
        return -1;
    }

    std::string token; //Read the next command
    while(commands >> token){
        if(token == "load-connections"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading connections." << std::endl;
                return -1;
            }

            loadConnections(adj_lists, loadfile);
        }
        else if(token == "load-locations"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading locations." << std::endl;
                return -1;
            }

            loadLocations(locations, loadfile);
        }
        else if(token == "print-degrees"){
            printDegreesOfAll(adj_lists, outfile);
        }
        else if(token == "print-degree-histogram"){
            printDegreesHistogram(adj_lists, outfile);
        }
        else if(token == "all-users-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printAllUsersWithinDistance(locations, outfile, start_id, 
                                        max_distance);
        }
        else if(token == "friends-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printFriendsWithinDistance(adj_lists, locations, outfile, 
                                       start_id, max_distance);
        }
        else if(token == "friends-with-degree"){
            ID_TYPE start_id,degree;
            commands >> start_id >> degree;

            printFriendsWithDegree(adj_lists, outfile, start_id, degree);
        }
        else if(token == "nodes-within-ID-range"){
            ID_TYPE start_id,offset;
            commands >> start_id >> offset;

            printUsersWithinIDRange(outfile, adj_lists.begin(), adj_lists.end(),
                                    adj_lists.find(start_id), offset);
        }
        else{
            std::cerr << "Unknown token \"" << token << "\"" << std::endl;
            return -1;
        }
    }

    return 0;
}




// This function converts decimal degrees to radians
// From https://stackoverflow.com/a/10205532
// DO NOT CHANGE THIS FUNCTION
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * Taken from https://stackoverflow.com/a/10205532
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 * DO NOT CHANGE THIS FUNCTION
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//////////////////TODO: IMPLEMENT ALL FUNCTIONS BELOW THIS POINT////////////////////

/**
 * Loads a list of connections in the format "a b" meaning b is a friend of a
 * into the adjacency lists data structure. a and b are IDs.
 * @param adj_lists Adjacency lists structure
 * @param loadfile File to read from
 */
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile){
  ID_TYPE id;

  while (loadfile>>id){
    //if the current id is not found as a key within the map, add it to the map
    if (adj_lists.find(id) == adj_lists.end()){
      vector<ID_TYPE> temp; //vector to hold connection
      ID_TYPE key = id; //storing the id
      loadfile>>id;
      ID_TYPE connection = id; //storing the connection
      temp.push_back(connection); //adding the connection to the vector
      adj_lists.insert(make_pair(key,temp)); //making and inserting a pair into the map
    }
    //if the current id does appear as a key within the map, add the new connection to its existing vector of connections
    else{
      ADJ_TYPE::iterator itr = adj_lists.find(id); //setting an iterator equal to the location within the map that the key appears
      loadfile>>id;
      ID_TYPE connection = id; //storing the connection
      itr->second.push_back(connection); //adding the connection to the vector of that key
    }
  } 
}

/**
 * Loads a list of locations in the format "id latitude longitude"
 * @param locations Location lookup table
 * @param loadfile File to read from
 */
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile){
  ID_TYPE id;
  float loc;

  while (loadfile>>id){
    loadfile>>loc; 
    float lat = loc; //storing latitude
    loadfile>>loc;
    float lon = loc; //storing longitude
    COORD_TYPE location = make_pair(lat,lon); //making a pair of latitude and longitude coordinates
    locations.insert(make_pair(id,location)); //adding an ID with its cooresponding coordinates
  }
}

/**
 * Prints all users within a certain distance of a particular user.
 * Sorted from shortest distance to user to longest distance to user.
 * Rounds down to the next lowest km if the difference is a decimal
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance){
  RDIST_TYPE within; //map to store the locations and user IDs at that location that are within the distance constraint

  //error checking: assuring location for user id exists
  if (locations.find(start_id) == locations.end()){
    outfile << "User ID " << start_id << " does not have a recorded location." << endl;
    return;
  }

  GEO_TYPE::const_iterator loc = locations.find(start_id); //finding start_id in locations map

  for (GEO_TYPE::const_iterator itr = locations.begin(); itr != locations.end(); ++itr){
    //checking if for loop is currently on the location containing information about start_id
    if (itr == loc){
      continue;
    }
    else{
      int distance = distanceEarth(loc->second.first,loc->second.second,itr->second.first,itr->second.second); //calulating distance
      //checking if distance is less than or equal to the distance constraint
      if (distance <= max_distance){
        RDIST_TYPE::iterator d_itr = within.find(distance);
        //checking if that distance already appears in new map
        if (d_itr == within.end()){
          vector<ID_TYPE> temp;
          temp.push_back(itr->first); 
          within.insert(make_pair(distance,temp));
        }
        else
          d_itr->second.push_back(itr->first);
      }
    }
  }

  //checking if there are no users within the provided distance (printing accordingly)
  if (within.size() == 0){
    outfile << "There are no users within " << max_distance << " km of user " << start_id << endl;
    return;
  }
  //printing all the users within provided distance
  else{
    outfile << "User IDs within " << max_distance << " km of user " << start_id << ":" << endl;
    for (RDIST_TYPE::iterator itr = within.begin(); itr != within.end(); itr++){
      outfile << " " << itr->first << " km:";
      for (unsigned int i = 0; i < itr->second.size(); i++)
        outfile << " " << itr->second[i];
      outfile << endl;
    }
  }
}

/**
 * Prints a sorted list of degrees (smallest to largest) along with how many users
 * have that degree. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
  map<int,int> degrees; //map to store all degrees

  //filling in map, recording how many times a degree occurs (making histogram)
  for (ADJ_TYPE::const_iterator itr = adj_lists.begin(); itr != adj_lists.end(); ++itr)
    degrees[itr->second.size()]++;

  //printing histogram
  outfile << "Histogram for " << adj_lists.size() << " users:" << endl;
  for (map<int,int>::const_iterator itr = degrees.begin(); itr != degrees.end(); ++itr){
    outfile << " Degree " << itr->first << ": " << itr->second << endl;
  }
}

/**
 * Prints a sorted list of user IDs (smallest to largest) along with the degree for
 * each user. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
  unsigned int counter = 0; //counter to count the number of users (w/ a degree of >=1)
  
  //finding the number of users with a degree that is >=1
  for (ADJ_TYPE::const_iterator itr = adj_lists.begin(); itr != adj_lists.end(); ++itr){
    if (itr->second.size() >= 1)
      counter++;
  }

  //printing
  outfile << "Degrees for " << counter << " users:" << endl;
  for (ADJ_TYPE::const_iterator itr = adj_lists.begin(); itr != adj_lists.end(); ++itr)
    //only printing the users that have a degree >=1
    if (itr->second.size() >= 1){
      outfile << " " << itr->first << ":" << " Degree " << itr->second.size() << endl;
    }
}

/**
 * Prints all friends of a particular user who have a particular degree.
 * Sorted by user ID (from smallest to largest).
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 * @param start_id User whose friends we are looking at
 * @param degree The degree of friends we want to print. Will be >=1.
 */
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree){
  ADJ_TYPE with_degree;
  
  //error checking: assuring user id exists within network
  if (adj_lists.find(start_id) == adj_lists.end()){
    outfile << "There is no user with friends and ID " << start_id << endl;
    return;
  }
  //filling a new map with elements that meet the degree requirement
  ADJ_TYPE::const_iterator id = adj_lists.find(start_id); //finding start_id in map
  //for loop goes through each of the users connections, seeing if its degree matches the desired degree
  for (unsigned int i = 0; i < id->second.size(); i++){ 
    ADJ_TYPE::const_iterator deg = adj_lists.find(id->second[i]);
    //checking if the user has other connections in the network (aka degree != 0)
    if (deg != adj_lists.end()){
      if (deg->second.size() == degree)
        with_degree.insert(*deg);
    }
  }

  //if there are no friends of the user with the degree, print accordingly
  if (with_degree.size() == 0){
    outfile << "User " << start_id << " has 0 friend(s) with degree " << degree << endl;
    return;
  }
  //printing
  outfile << "User " << start_id << " has " << with_degree.size() << " friend(s) with degree " << degree << ":";
  for (ADJ_TYPE::iterator itr = with_degree.begin(); itr != with_degree.end(); ++itr)
    outfile << " " << itr->first;
  outfile << endl;
}

/**
 * Prints friends of a particular user within a certain distance of that user.
 * Sorted from shortest distance to user to longest distance to user.
 * @param adj_lists Adjacency lists structure
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations,
                                std::ofstream& outfile, const ID_TYPE& start_id, 
                                double max_distance){
  DIST_TYPE within; //map to store distances and friends at that distance

  //error checking: assuring user id exists within network
  if (adj_lists.find(start_id) == adj_lists.end()){
    outfile << "There is no user with friends and ID " << start_id << endl;
    return;
  }

  //error checking: assuring location for user id exists
  if (locations.find(start_id) == locations.end()){
    outfile << "User ID " << start_id << " does not have a recorded location." << endl;
    return;
  }

  ADJ_TYPE::const_iterator con = adj_lists.find(start_id); //finding start_id in connections map
  GEO_TYPE::const_iterator loc = locations.find(start_id); //finding start_id in locations map

  //for loop going through each of the users connections and seeing if its distance to the user is within the distance constraint
  for (unsigned int i = 0; i < con->second.size(); i++){ 
    GEO_TYPE::const_iterator temp = locations.find(con->second[i]); //finding location of current friend id in locations map
    double distance = distanceEarth(loc->second.first,loc->second.second,temp->second.first,temp->second.second); //calulating distance
    //checking if distance is less than or equal to the max distance allowed
    if (distance <= max_distance){ 
      DIST_TYPE::iterator d_itr = within.find(distance);
      //checking if a user with this distance has not already been found
      if (d_itr == within.end()){
        vector<ID_TYPE> temp;
        temp.push_back(con->second[i]); 
        within.insert(make_pair(distance,temp)); //creating a new pair in vector
      }
      else
        d_itr->second.push_back(con->second[i]); //adding ID to vector within map
    }
  }

  //checking if there are no users within the provided distance
  if (within.size() == 0){
    outfile << "There are no friends within " << max_distance << " km of user " << start_id << endl;
    return;
  }
  //printing all the users in provided distance, sorted by there distance from the initial user (start_id)
  else{
    outfile << "Friends within " << max_distance << " km of user " << start_id << ":" << endl;
    for (DIST_TYPE::iterator itr = within.begin(); itr != within.end(); itr++){
      outfile << " " << itr->first << " km:";
      for (unsigned int i = 0; i < itr->second.size(); i++)
        outfile << " " << itr->second[i];
      outfile << endl;
    }
  }
}


/**
 * Prints users with an ID that is "close" to a particular user's ID.
 * Sorted from smallest to largest user ID.
 * Only prints for degree >=1.
 *
 * If there are M IDs that should be printed this function should only use
 * ADJ_TYPE::const_iterator::operator++ / ADJ_TYPE::const_iterator::operator-- O(M) times
 *
 * @param outfile File to write output to
 * @param begin The .begin() iterator for the adjacency lists structure
 * @param end The .end() iterator for the adjacency lists structure
 * @param start_it Iterator for user we are using as our baseline (i.e. 0 diifference)
 *        It is possible that the start_it was not found in the data.
 * @param offset Maximum absolute difference from start_id that a printed user's
 *               ID can have
 */
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin,
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it, unsigned int offset){
  vector<ID_TYPE> in_range; //vector to store user IDs that are within the ID range

  //error checking: assuring user ID exists within network
  if (start_it == end){
    outfile << "There is no user with the requested ID" << endl;
    return;
  }

  //setting upper and lower bounds  
  ID_TYPE upper;
  ID_TYPE lower;

  //if the offset will make the upper bound greater than 4,000,000,000, the bound is set to that value
  //as a user ID will not exceed this value
  if (4000000000-start_it->first <= offset)
    upper = 4000000000;
  else
    upper = start_it->first + offset;
  
  //if the offset would set the lower bound to a value lower than zero, the bound is set to zero
  //as a user ID will not be lower than 0
  if (start_it->first <= offset)
    lower = 0;
  else
    lower = start_it->first - offset;
  
  //pushing back the user ids that fall in this range (lower-upper) and checking for duplicates (so start_it id is not added)
  while (begin != end){
    if (begin->first >= lower && begin->first <= upper && begin->first != start_it->first){
      in_range.push_back(begin->first);
    }
    begin++;
  }

  //if there is no IDs that meet the constraints, print accordingly
  if (in_range.size() == 0)
    outfile << "There are no users with an ID within +/-" << offset << " of " << start_it->first << endl;
  //printing
  else{
    outfile << "Users with an ID within +/-" << offset << " of " << start_it->first << ":";
    for (unsigned int i = 0; i < in_range.size(); i++)
        outfile << " " << in_range[i];
    outfile << endl;
  }
}
