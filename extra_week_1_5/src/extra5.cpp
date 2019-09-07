//============================================================================
// Name        : extra5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// FIFTH (UNASSIGNED) EXTRA ASSIGNMENT:
// Template with Class utilization

#include <iostream>
using namespace std;




template <class T>
class point {
private:
	T x;
	T y;
public:
	point(T x, T y);
	void setAll(T x, T y);
	T getX();
	T getY();
	void print();
};


template <class T>
point<T>::point(T a, T b){
	setAll(a,b);
}

template <class T>
void point<T>::setAll(T a, T b){
	if(a){
		x = a;
	} else {
		x = 10;
	}

	if(b){
		y = b;
	} else {
		y = 5;
	}
}

template <class T>
T point<T>::getX(){
	cout << "x: " << x << endl;
}

template <class T>
T point<T>::getY(){
	cout << "y: " << y << endl;
}

template <class T>
void point<T>::print(){
	cout << "(" << x << "," << y << ")" << endl;
}



int main() {

	point<int> point1(5,10);
	point1.getX();
	point1.getY();
	point1.print();




	return 0;
}
