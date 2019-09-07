//============================================================================
// Name        : extra10.cpp
// Author      : Mital Patel
// Version     :
// Copyright   : Your copyright notice
// Description : Write a recursive c++ program
//============================================================================

#include <iostream>
using namespace std;



void function1();
void function2();
void function3();
void function4();
void factorial(int);

int main() {
	//function1();
	factorial(5);
	return 0;
}

void function1(){
	function2();
	cout << "Hello 1" << endl;
}
void function2(){
	function3();
	cout << "Hello 2" << endl;
}
void function3(){
	function4();
	cout << "Hello 3" << endl;
}
void function4(){
	cout << "BYE" << endl;
}

/*

void factorial(int x){
	if(x == 1){
		//return 1;
		cout << "1" << endl;
	} else if( x > 1) {
		//return (x * factorial(x-1));
		cout << x << endl;
	}
}


int repeat(int a, int b){

	if(b == 1){
		return a;
	} else {
		return (a+repeat(a,b-1));
	}
}
*/
