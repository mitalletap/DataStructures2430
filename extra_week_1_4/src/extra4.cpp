//============================================================================
// Name        : extra4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Quadratic using operator overloading
//============================================================================

// FOURTH EXTRA ASSIGNMENT:
// Quadratic using operator overloading

#include <iostream>
using namespace std;


class quadraticEq
{   friend ostream& operator<< (ostream&, const quadraticEq&);
    friend istream& operator>> (istream&, quadraticEq&);
public:
    const quadraticEq& operator=(const quadraticEq& right);
    void rootsType();
    void eqRoots();
    void setEq(double a, double b, double c);
    bool operator==(const quadraticEq& right) const;
    bool operator!=(const quadraticEq& right) const;
    quadraticEq operator+(const quadraticEq& num);
    quadraticEq operator-(const quadraticEq& num);

    quadraticEq(double a = 0, double b = 0, double c = 0);
private:
    double coeffXSquare;
    double coeffX;
    double constTerm;
};


int main() {
	quadraticEq eq1(1, 2, 1);
	quadraticEq eq2(1, 1, 1);
	quadraticEq eq3(2, 4, 2);

	cout << "eq1: " << eq1 << endl;
	cout << "eq2: " << eq2 << endl;
	cout << "eq3: " << eq3 << endl;

	eq1.rootsType();
	eq1.eqRoots();
	eq2.rootsType();
	eq2.eqRoots();

	cout << "eq1 + eq2 = " << eq1 + eq2 << endl;

	cout << "eq1 - eq2 = " << eq1 - eq2 << endl;

	cout << "eq1 == eq2: " << (eq1 == eq2) << endl;
	cout << "eq1 != eq2: " << (eq1 != eq2) << endl;
	cout << "eq1 == eq3: " << (eq1 == eq3) << endl;
	cout << "eq1 != eq3: " << (eq1 != eq3) << endl;
	return 0;
}
