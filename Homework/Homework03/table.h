#include <iostream>
using namespace std;

template <class T> class Table{

public:
	//tpyedefs
	typedef unsigned int unint;

	//constructors, assignment operator, & destructor
	Table() {this->create();}
	Table(unint rows, unint cols, T value) {this->create(rows, cols, value);}
	Table(const Table& t) {copy(t);}
	~Table() {destroy();}
	Table& operator=(const Table& t);
	
	//member functions and other operators
	T& get(unint r, unint c) const;
	void set(unint r, unint c, T new_value);
	unint numRows() {return rows_;}
	unint numColumns() {return cols_;}
	void push_back_row(vector<T>& new_values);
	void push_back_column(vector<T>& new_values);
	void pop_back_row();
	void pop_back_column();
	void push_back_rows(const Table<T>& t);
	void push_back_columns(const Table<T>& t);
	void destroy();
	
	//print helper function
	void print();
	

private:
	//private member variables
	unint rows_;
	unint cols_;
	T value_;
	T** data_table;

	//private member functions
	void create();
	void create(unint rows, unint cols, T& value);
	void copy(const Table<T>& t);
};

template <class T> void Table<T>::create(){
	//setting pointer to array of pointers to NULL and rows and cols values to zero (empty table)
	data_table = NULL;
	rows_ = cols_ = 0;
}

template <class T> void Table<T>::create(unint rows, unint cols, T& value){
	//assigning private member variables
	rows_ = rows;
	cols_ = cols;
	value_ = value;
	
	//setting pointer to point to an array of pointers with size rows
	data_table = new T* [rows_];
	
	//setting each pointer in an array of pointers to point to an array of size cols
	for (unint i = 0; i < rows_; i++)
		data_table[i] = new T [cols_];
	
	//setting each value in the 2D array to the value input by the user
	for (unint i = 0; i < rows_; i++){
		for (unint j = 0; j < cols_; j++)
			data_table[i][j] = value_;
	}
}
template <class T> T& Table<T>::get(unint r, unint c) const{
	//error checking: checks to assure entered location is valid (boundary checking)
	if (r < 0 || r >= rows_ || c < 0 || c >= cols_){
		cerr << "Error: Entered row and column values passed as arguments in get() do not represent a valid location in data table" << endl;
		exit(1);
	}
	return data_table[r][c];
}

template <class T> void Table<T>::set(unint r, unint c, T new_value){
	//error checking: checks to assure entered location is valid (boundary checking)
	if (r < 0 || r >= rows_ || c < 0 || c >= cols_){
		cerr << "Error: Entered row and column values passed as arguments in set() do not represent a valid location in data table" << endl;
		exit(1);
	}
	//setting given location to new_value
	data_table[r][c] = new_value;
}

template<class T> void Table<T>::push_back_row(vector<T>& new_values){
	//creating variable with new number of rows, new_row
	unint new_row= rows_+1;

	//error checking: checking to assure the size of new_values matches the number of columns so that the values fit correctly in the new data table
	if (new_values.size() != cols_){
		cerr << "Error: Attempt to add an inadequate number of values to new row when calling push_back_row()" << endl;
		exit(1);
	}

	//creating a new table with new number of rows and same number of columns
	T** table = new T*[new_row];
	for(unint i=0; i<new_row;++i)
		table[i] = new T[cols_];

	//copying values from original data_table to new table, table
	for(unint i = 0; i < rows_; ++i){
		for(unint j = 0; j < cols_;++j)
			table[i][j] = data_table[i][j];
	}

	//calling destroy() to destruct old, now unused pointer to array of pointers and assigning new table to data_table
	destroy();
	data_table = table;
	
	//inserting new values into the new data_table
	for(unint j = 0; j < cols_; ++j)
		data_table[rows_][j] = new_values[j];
		
	//updating row_ to account for the size of new table
	rows_ = new_row;
}

template<class T> void Table<T>::push_back_column(vector<T>& new_values){
	//creating variable with new number of columns, new_col
	unint new_col= cols_+1;

	//error checking: checking to assure the size of new_values matches the number of rows so that the values fit correctly in the new data table
	if (new_values.size() != rows_){
		cerr << "Error: Attempt to add an inadequate number of values to new column when calling push_back_column()" << endl;
		exit(1);
	}

	//creating a new table with same number of rows and new number of columns
	T** table = new T*[rows_];
	for(unint i = 0; i < rows_; ++i)
		table[i] = new T[new_col];

	//copying values from original data_table to new table, table
	for(unint i = 0; i < rows_; ++i){
		for(unint j = 0; j < cols_; ++j)
			table[i][j] = data_table[i][j];
	}
	
	//calling destroy() to destruct old, now unused pointer to array of pointers and assigning new table to data_table
	destroy();
	data_table = table;
	
	//inserting new values into the new data_table
	for (unint j = 0; j < rows_; ++j)
		table[j][cols_] = new_values[j];
	
	//updating cols_ to account for the size of new table
	cols_ = new_col;
}

template<class T> void Table<T>::pop_back_row(){
	//error checking: checks to assure there are more than 0 rows
	if (rows_ == 0){
		cerr << "Error: Cannot remove a row (invalid call to pop_back_row())" << endl;
		exit(1);
	}

	//creating variable with new number of rows, new_row
	unint new_row = rows_-1;

	//creating a new table with new number of rows and the same number of columns
	T** table = new T*[new_row];
	for(unint i = 0; i < new_row; ++i)
		table[i] = new T[cols_];

	//copying values from original data_table to new table, disregarding values in the removed row
	for(unint i = 0; i < new_row; ++i){
		for(unint j = 0; j < cols_; ++j)
			table[i][j] = data_table[i][j];
	}

	//calling destroy() to destruct old, now unused pointer to array of pointers and assigning new table to data_table
	destroy();
	data_table = table;

	//updating cols_ to account for the size of new table
	rows_ = rows_-1;
}

template<class T> void Table<T>::pop_back_column(){
	//error checking: checks to assure there are more than 0 rows
	if (cols_ == 0){
		cerr << "Error: Cannot remove a column (invalid call to pop_back_column())" << endl;
		exit(1);
	}

	//creating variable with new number of columns, new_col
	unint new_col = cols_-1;

	//creating a new table with same number of rows and new number of columns
	T** table = new T*[rows_];
	for(unint i = 0; i < rows_; ++i)
		table[i] = new T[new_col];

	//copying values from original data_table to new table, disregarding values in the removed column
	for(unint i = 0; i < rows_; ++i){
		for(unint j = 0; j < new_col; ++j)
			table[i][j] = data_table[i][j];
	}

	//calling destroy() to destruct old, now unused pointer to array of pointers and assigning new table to data_table
	destroy();
	data_table = table;

	//updating cols_ to account for the size of new table
	cols_ = cols_-1;
}

template <class T> void Table<T>::destroy(){
	//delete each pointer in the array
	for (unint i = 0; i < rows_; i++){
		delete [] data_table[i];
	}
	//deleting the pointer to the array of pointers
	delete [] data_table;
}

template <class T> void Table<T>::print(){
	//printing out each character in the table
	cout << "table: " << rows_ << " rows, " << cols_ << " columns" << endl;
	for(unint i = 0; i < rows_; i++){
        for(unint j = 0; j < cols_; j++)
            cout << data_table[i][j] << " ";
        cout << endl;
    }
    cout << "\n";
}

template<class T> void Table<T>::copy(const Table<T>& t){
	//sets rows_ and cols_ to that of the Table object that is being copied
	rows_ = t.rows_;
	cols_ = t.cols_;
	
	//created new table with newly set dimensions and copies over the values from Table object t
	data_table = new T*[t.rows_];
	for(unint i = 0; i < t.rows_; ++i){
		data_table[i] = new T[cols_];
		for(unint j = 0; j < cols_; ++j)
			data_table[i][j] = t.get(i,j);
	}
}


template <class T> Table<T>& Table<T>::operator=(const Table<T>& t) {
	//assignment operator, checks to assure current object is not equivalent to Table object t
	//if it is not, the object is destructed and then copied (the copy is returned)
	if (this != &t) {
  		destroy();
    	this -> copy(t);
    }
  	return *this;
}

//EXTRA CREDIT MEMBER FUNCTIONS

template<class T> void Table<T>::push_back_rows(const Table<T>& t){
	//error checking: checking to assure that both tables have the same amount of columns
	if (cols_ != t.cols_){
		cerr << "Error: Invalid attempt to add new rows (with function push_back_rows()) due to mismatching number of columns" << endl;
		exit(1);
	}

	//creating a vector of vectors to copy information in each row of Table object t into each vector in to_inserts vector 
	vector<vector<T>> to_insert;
	for (unint i = 0; i < t.rows_; i++){
		vector<T> each_row;
		for (unint j = 0; j < t.cols_; j++){
			each_row.push_back(t.data_table[i][j]);
		}
		to_insert.push_back(each_row);
	}
	
	//creating variable with new number of rows, new_rows
	unint new_rows = rows_ + t.rows_;

	//creating a new table with new number of rows and same number of columns
	T** table = new T*[new_rows];
	for (unint i = 0; i < new_rows; ++i)
		table[i] = new T[cols_];

	//copying values from original data_table to new table, table
	for (unint i = 0; i < rows_; ++i){
		for (unint j = 0; j < cols_; ++j)
			table[i][j] = data_table[i][j];
	}

	//calling destroy() to destruct old, now unused pointer to array of pointers and assigning new table to data_table
	destroy();
	data_table = table;

	//inserting new values into the new data_table
	for(unint i = new_rows-t.rows_; i < new_rows; i++){
		for (unint j = 0; j < cols_; j++)
			data_table[i][j] = to_insert[i-(new_rows-t.rows_)][j];
	}
	//updating rows_ to account for the size of new table
	rows_ = new_rows;
}

template<class T> void Table<T>::push_back_columns(const Table<T>& t){
	//error checking: checking to assure that both tables have the same amount of rows
	if (rows_ != t.rows_){
		cerr << "Error: Invalid attempt to add new columns (with function push_back_columns()) due to mismatching number of rows" << endl;
		exit(1);
	}

	//creating a vector of vectors to copy information in each row of Table object t into each vector in to_inserts vector 
	vector<vector<T>> to_insert;
	for (unint i = 0; i < t.rows_; i++){
		vector<T> each_row;
		for (unint j = 0; j < t.cols_; j++){
			each_row.push_back(t.data_table[i][j]);
		}
		to_insert.push_back(each_row);
	}
	
	//creating variable with new number of rows, new_rows
	unint new_cols = cols_ + t.cols_;

	//creating a new table with new number of rows and same number of columns
	T** table = new T*[rows_];
	for (unint i = 0; i < rows_; ++i)
		table[i] = new T[new_cols];

	//copying values from original data_table to new table, table
	for (unint i = 0; i < rows_; ++i){
		for (unint j = 0; j < cols_; ++j)
			table[i][j] = data_table[i][j];
	}

	//calling destroy() to destruct old, now unused pointer to array of pointers and assigning new table to data_table
	destroy();
	data_table = table;

	//inserting new values into the new data_table
	for(unint i = 0; i < rows_; i++){
		for (unint j = new_cols-t.cols_; j < new_cols; j++)
			data_table[i][j] = to_insert[i][j-(new_cols-t.cols_)];
	}
	//updating cols_ to account for the size of new table
	cols_ = new_cols;
}