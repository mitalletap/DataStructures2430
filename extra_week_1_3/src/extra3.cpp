//============================================================================
// Name        : extra3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Line Type Class
//============================================================================


// THIRD EXTRA ASSIGNMENT:
// EQUATION OF A LINE

#include <iostream>
using namespace std;



class Line {
public:
	Line();
	Line(int, int, int);
	int getA();
	int getB();
	int getC();
	int changeA(int);
	int changeB(int);
	int changeC(int);
	bool isHorizontal();
	bool isVertical();
	bool isParallel(class Line &A);
	bool isPerp(class Line &A);
	double findSlope(double &slope);
	void printData();
	bool equalLines(class Line A);
private:
	int a;
	int b;
	int c;
	double  slope;
};

Line::Line(){
	a = 1;
	b = 1;
	c = 2;
	slope = findSlope(slope);

}

Line::Line(int x, int y, int z){
	a = x;
	b = y;
	c = z;
	slope = findSlope(slope);
}

int Line::getA(){
	return a;
}

int Line::getB(){
	return b;
}

int Line::getC(){
	return c;
}

int Line::changeA(int x){
	a = x;
	return a;
}

int Line::changeB(int y){
	b = y;
	return b;
}

int Line::changeC(int z){
	c = z;
	return c;
}

bool Line::isHorizontal(){
	if(a == 0){
		return true;
	} else {
		return false;
	}
}

bool Line::isVertical(){
	if(b == 0){
		slope = 0;
		return true;
	} else {
		return false;
	}
}

bool Line::isParallel(class Line &A){
	if(slope == A.findSlope(slope)){
		return true;
	} else {
		return false;
	}
}

bool Line::isPerp(class Line &A){
	if((a == 0 && A.isVertical()) || (b == 0 && A.isHorizontal())){
		return true;
	} else {
		return false;
	}

}

double Line::findSlope(double &slope){
	if(!isVertical()){
		slope = -((double)a/(double)b);
	}

	return slope;
}
void Line::printData(){
	cout << "Equation of Line is: " << endl;
	cout << a << "x+" << b << "y=" << c << endl;
}

bool Line::equalLines(class Line A){
	int Aa, Ab, Ac;
	Aa = A.getA();
	Ab = A.getB();
	Ac = A.getC();
	if((a == Aa) && (b == Ab) && (c == Ac)){
		return true;
	} else {
		return false;
	}
}

int main() {

	// Variables Declarations
	int x, y, z;
	double slope;

	// Object Declarations
	// Print Default Constructor
	Line redLine;
	redLine.printData();

	// Print Unique Constructor
	Line greenLine(5,2,6);
	greenLine.printData();

	Line orangeLine(1,2,3);
	orangeLine.printData();

	Line blueLine(1,2,3);
	blueLine.printData();



	// Get A Value
	x = greenLine.getA();
	cout << "Value of A: " << x << endl;

	// Get B Value
	y = greenLine.getB();
	cout << "Value of B: " << y << endl;

	// Get C Value
	z = greenLine.getC();
	cout << "Value of C: " << z << endl;

	// Get Slope
	greenLine.findSlope(slope);
	cout << "Slope: " << slope << endl;

	// Change A Value
	x = greenLine.changeA(3);
	cout << "New value of A: " << x << endl;

	// Change B Value
	y = greenLine.changeB(1);
	cout << "New value of B: " << y << endl;

	// Change C Value
	z = greenLine.changeC(9);
	cout << "New value of C: " << z << endl;




	// Demonstrate Parallel / Perpendicular Functions

	if(greenLine.isParallel(redLine)){
		cout << "greenLine and redLine are parallel!" << endl;
	} else {
		cout << "greenLine and redLine are NOT parallel!" << endl;
	}


	if(greenLine.isParallel(redLine)){
		cout << "orangeLine and blueLine are parallel!" << endl;
	} else {
		cout << "orangeLine and blueLine are NOT parallel!" << endl;
	}

	if(orangeLine.equalLines(blueLine)){
		cout << "The lines are the EXACT SAME!" << endl;
	}








}
