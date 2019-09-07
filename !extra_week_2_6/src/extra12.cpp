//============================================================================
// Name        : extra12.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// TWELTH EXTRA ASSIGNMENT:
// Combined
// Stack would be a base class
// LL would inherit from the base and have additional functionallity
// Write base case (choose 1) and write inherited case


#include <iostream>
using namespace std;

struct node {
	int data;
	node *next;
};


class stack {
private:
	int top = -1;
public:
	int a[10];
	stack(){
		top = -1;
	}

	void push(int x){
		if(top >= 10){
			cout << "stack overflow" << endl;
		} else {
			a[++top] = x;
		}
	}

	void pop(){
		if(top < 0){
			cout << "stack underflow" << endl;
		} else {
			a[top--];
		}
	}

	bool isEmpty(){
		if(top == -1){
			return true;
		} else {
			return false;
		}
	}

};


class LL: public stack {
public:

private:
};







int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
