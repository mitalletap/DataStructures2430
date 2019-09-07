//============================================================================
// Name        : hw0.cpp
// Author      : Mital Patel
// Version     : V4
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// RESOURCES USED FOR THIS PROJECT INCLUDE:
// youtube.com
// cplusplus.com
// stackoverflow.com





// INCLUDES
#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"

using namespace std;


// GLOBAL VARIABLES
int row = 0, column = 0;
const int N = 20;


// STRUCTURE FOR THE ARRAY
struct AS {
	double arr[N][N];
};


// PRINT FUNCTION
void addToArray(AS var){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			var.arr[i][j];
		}
	}

	// Reset the values
	column = 0;
	row = 0;
}


// READ FUNCTION
AS makeArray(string file){
	AS var;
	ifstream fileI(file);
	string line;
	double x;

	if(!fileI.is_open()){
		cout << "ERROR: FILE CANNOT BE OPENED. TRY ANOTHER FILE." << endl;
		exit(0);
	}

	while(getline(fileI, line)){
		istringstream stream(line);
		column = 0;
		while(stream >> x){
			var.arr[row][column] = x;
			column++;
		}
		row++;
	}
	return var;
}


// READ'S MATRIX TO FIND DIMENSIONS
int readMatrixSize(string file1, string file2, int& col1, int& col2, int& row1, int& row2){
	AS var1, var2;
	ifstream fileA(file1);
	ifstream fileB(file2);
	string line;
	double x;
	while(!fileA.eof()){
		while(getline(fileA, line)){
			istringstream stream(line);
			column = 0;
			while(stream >> x){
				var1.arr[row][column] = x;
				column++;
			}
			row++;
		}
		col1 = column;
		row1 = row;
		row = 0;
		column = 0;
	}
	while(!fileB.eof()){
		while(getline(fileB, line)){
			istringstream stream(line);
			column = 0;
			while(stream >> x){
				var2.arr[row][column] = x;
				column++;
			}
			row++;
		}
		col2 = column;
		row2 = row;
		row = 0;
		column = 0;
	}
	return col1, col2, row1, row2;

}


// COMPARES MATRICES TO FIND LOWEST DIMENSIONS
int compareMatrix(int col1, int col2, int row1, int row2, int& row, int& column){
	if(row1 <= row2){
		row = row1;
	} else {
		row = row2;
	}
	if(col1 <= col2){
		column = col1;
	} else {
		column = col2;
	}
	return row, column;
}


// FUNCTION TO ADD BOTH MATRICES
string addMatrices(int row, int column, AS first, AS second, AS& result, const char* filename){
	ofstream outputFile(filename);
	outputFile.precision(2);
	outputFile.setf(std::ios::fixed);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			result.arr[i][j] = first.arr[i][j] + second.arr[i][j];
			outputFile << result.arr[i][j] << " ";
		}
		outputFile << endl;
	}
	return 0;
}


// MAIN FUNCTION
int main(int argc, char* argv[])
{


  if (argc < 2) {
    cout << "Usage: densemult \"A=<file>;B=<file>;C=<file>\"" << endl;
    return -1;
  }





  ArgumentManager am(argc, argv);
  string file1 = am.get("A");
  string file2 = am.get("B");
  string output = am.get("C");
  ofstream outputFile(output.c_str());
  outputFile.precision(2);
  outputFile.setf(std::ios::fixed);


  //cout << "File1: " << file1 << " File2: " << file2 << " File3: " << output << endl;
  //cout << "File name for matrix A: " << file1 << ". File name for matrix C: " << file2 << endl;

  //string file1 = "test0A1.txt";
  //string file2 = "test0A2.txt";
  //string file3 = "ans0A.txt";
  int col1 = 0, col2 = 0, row1 = 0, row2 = 0;
  AS first, second, result;


  first = makeArray(file1);
  addToArray(first);
  //cout << endl;

  second = makeArray(file2);
  addToArray(second);
  //cout << endl;

  readMatrixSize(file1, file2, col1, col2, row1, row2);
  compareMatrix(col1, col2, row1, row2, row, column);
  addMatrices(row, column, first, second, result, output.c_str());


  return 0;
}