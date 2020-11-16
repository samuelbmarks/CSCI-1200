#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ostream>
#include <cstring>
using namespace std;

/* 
This function takes in two arguments, image_vect, a vector of strings that make up a grid of
ASCII characters, and start, a string of an ASCII character that represents the "foreground 
character" that the user of the function wants to expand upon. The purpose of the function is 
to change each "background" character in the grid to the provided "foreground" character if in 
any direction it is next to a "foreground" character. The function will return a revised vector
of strings, image_vect, providing a new grid where these changes are displayed.
*/
vector<string> dilation(vector<string> &image_vect, const string &expand){
    vector<string> dil;
	dil = image_vect; 
    /*
	This nested for loop first checks if each character in the vector, dil, is the character 
	given by the expand argument. If it is, nothing is changed. If it is not, the characters 
	to the left, right, upward direction, and downward direction on the grid are checked 
	(taking into account the boundaries of the grid) to see if one or more of those characters
	is the same as the character given by the expand argument. If none of them are, nothing is 
	changed. If one or more is, then the character in that position in the image_vect vector 
	is changed to the "expand" character.
    */
    for (unsigned int i = 0; i < dil.size(); i++){		
		for (unsigned int j = 0; j < dil[i].size(); j++){
			if (dil[i][j] != expand[0]){
				if (i != 0 && dil[i-1][j] == expand[0]){
					image_vect[i][j] = expand[0];	
				}
				if (j != 0 && dil[i][j-1] == expand[0]){
					image_vect[i][j] = expand[0];
				}
				if (i+1 < dil.size() && dil[i+1][j] == expand[0]){
					image_vect[i][j] = expand[0];
				}
				if (j+1 < dil[i].size() && dil[i][j+1] == expand[0]){
					image_vect[i][j] = expand[0];
				}
			}
		}
	}
	return image_vect;
}

/* 
This function takes in three arguments, image_vect, a vector of strings that make up a grid of
ASCII characters, start, a string of an ASCII character that the user wants to erode, and change, 
a string of an ACII character that represents that "background" character in the grid that the
eroded "start" characters will become. The purpose of this function is to convert each "start" 
character in the grid to the provided "background" character if in any direction it is next to a
"background" character. The function will return the revised vector of strings, image_vect, 
providing a new grid where these changes are displayed.
*/
vector<string> erosion(vector<string> &image_vect, const string &fore, const string &back){
	vector<string> ero;
	ero = image_vect;
	/*
	This nested for loop first checks if the characters to the left, right, upward direction, 
	and downward direction of a given character on the grid (taking into account the boundaries 
	of the grid) to see if one or more of those characters are the same as the character given by
	the back argument. If none of them are, nothing is changed. If one or more are, then the 
	character in that position on the image_vect vector is changed to the "back" character.
    */
    for (unsigned int i = 0; i < ero.size(); i++){
		for (unsigned int j = 0; j < ero[i].size(); j++){
			if (i != 0 && ero[i-1][j] != fore[0]){
				image_vect[i][j] = back[0];	
			}
			if (j != 0 && ero[i][j-1] != fore[0]){
				image_vect[i][j] = back[0];
			}
			if (i+1 < ero.size() && ero[i+1][j] != fore[0]){
				image_vect[i][j] = back[0];
			}
			if (j+1 < ero[i].size() && ero[i][j+1] != fore[0]){
				image_vect[i][j] = back[0];
			}
		}
	}
	return image_vect;
}

/* 
This function takes in three arguments, image_vect, a vector of strings that make up a grid of
ASCII characters, start, a string of an ASCII character that the user wants to change, and change, 
a string of an ACII character that the user wants the "start" character to be changed to. The 
purpose of the function is replace all "start" characters to the "change" character. The function 
will return the revised vector of strings, image_vect, providing a new grid where these changes 
are displayed.
*/
vector<string> replace(vector<string> &image_vect, const string &start, const string &change){
	vector<string> rep;
	rep = image_vect;
	/*
	This nested for loop first checks if each character in the vector, rep, is the character 
	given by the start argument. If it is not, nothing is changed. If it is, the character in that 
	position on the image_vect vector is changed to the "change" character.
    */
	for (unsigned int i = 0; i < rep.size(); ++i){
		for (unsigned int j = 0; j < rep[i].size(); ++j){
            if (rep[i][j] == start[0]){
            	image_vect[i][j] = change[0];
            }
		}
	}
    return image_vect;
}

/* 
This function first will open the files given as arguments in the command line and will return 
an error if either fails to open. Next, the input file is read into a vector of strings, image. 
Then, based on the function given as an argument in the command line, one of the functions 
(dilation, erosion, or replace) will be performed. Finally, the new vector is outputted to the 
output file given as an argument in the command line.
*/
int main(int argc, char* argv[]){
	//opening input file
	ifstream inputFile;
	inputFile.open(argv[1]);
	if (!inputFile.good()) {
    	cerr << "Error: Cannot open input file " << argv[1];
   		exit(1);
  	}

	//opening output file
	ofstream ostr;
	ostr.open(argv[2]);
	if (!ostr.good()) {
    	cerr << "Error: Cannot open output file " << argv[2];
    	exit(1);
 	}

	string str;
	vector<string> image;

	//while loop stores each line in the input file in vector of strings, image
	while (getline(inputFile,str)){
		image.push_back(str);
	}
	
	inputFile.close();
	
	//if statement will perform dilation fuction if 4th argument in command line is "dilation"
	if (strcmp(argv[3], "dilation") == 0){
		vector<string> dil = dilation(image, argv[4]);
	 	//outputting new vector in output file
	 	for (unsigned int i = 0; i < dil.size(); i++){
        	ostr << dil[i] << endl;
   	 	}
	}

	//if statement will perform erosion fuction if 4th argument in command line is "erosion"
	else if (strcmp(argv[3], "erosion") == 0){
		vector<string> ero = erosion(image, argv[4], argv[5]);
	 	//outputting new vector in output file
	 	for (unsigned int i = 0; i < ero.size(); i++){
        	ostr << ero[i] << endl;
   	 }
	}

	//if statement will perform replace fuction if 4th argument in command line is "replace"
	else if (strcmp(argv[3], "replace") == 0){
		vector<string> rep = replace(image, argv[4], argv[5]);
	 	//outputting new vector in output file
	 	for (unsigned int i = 0; i < rep.size(); i++){
        	ostr << rep[i] << endl;
		}
	}

	//closing output file
	ostr.close();
	return 0;

}