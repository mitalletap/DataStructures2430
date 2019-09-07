//============================================================================
// Name        : extra6.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// SIXTH EXTRA ASSIGNMENT:
// http://opendatastructures.org/ods-cpp.pdf; page 30;
// Create constuctor, destructor, dynamically allocated array


#include <iostream>
using namespace std;



class dArray{
private:
	int *a = NULL;
	int size;
public:
	dArray(){
		size = 10;
		a = new int[size];
		cout << "dArray Created!" << endl;
		for(int i = 0; i < size; i++){
			a[i] = i;
		}
	}
	dArray(int s){
		size = s;
		a = new int[size];
	}
	~dArray(){
		delete a;
		a = NULL;
		cout << "dArray Deleted!" << endl;
	}
	void print(){
		if(a == NULL){
			cout << "Error! Array Empty!" << endl;
			exit(0);
		} else {
			for(int i = 0; i < size; i++){
				cout << a[i] << endl;
			}
		}
	}
};






int main() {

	dArray dynamic;
	cout << "--------------------------------" << endl;
	cout << "Print Array" << endl;
	dynamic.print();
	cout << endl;
	cout << "--------------------------------" << endl;
	cout << "Delete Array" << endl;
	dynamic.~dArray();
	cout << "--------------------------------" << endl;
	cout << "Printing Array After Deletion" << endl;
	dynamic.print();






}
