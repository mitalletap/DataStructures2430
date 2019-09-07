//============================================================================
// Name        : extra13.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
using namespace std;


bool isLowOperator(char c){
	if(c == '+' || c == '-' || c == '*' || c == '/'){
		return true;
	} else {
		return false;
	}
}
bool isHighOperator(char c){
	if(c == '(' || c == ')'){
		return true;
	} else {
		return false;
	}
}

// 2+(3*3))(
bool hasEvenParenth(string str){
	stack<int> temp;
	bool failed = false;
	int size = str.length()-1;
	int counter = 0;
	for(int i = 0; i <= size; i++){
		if(str[i] == '('){
			counter++;
			temp.push(str[i]);
		} else if(str[i] == ')'){
			if(temp.empty() || temp.top() == ')'){
				failed = true;
			} else {
				counter--;
				temp.pop();
			}
		}
	}
	if(!temp.empty()){
		failed = true;
	}
	if(failed == true){
		return false;
	} else {
		return true;
	}
}
bool endCorrent(string str){
	int size = str.length() - 1;
	if(str[size] == '+' || str[size] == '-' || str[size] == '*' || str[size] == '/'){
		return false;
	} else {
		return true;
	}
}
bool AdjOperators(string str){
	bool found = false;
	int size = str.length() - 1;
	int x = 0;
	while(found == false){
		if(isLowOperator(str[x]) && isLowOperator(str[x+1])){
			found = true;
			return true;
		} else if(x == str[size]){
			return false;
		} else {
			x++;
		}
	}
}
bool isValidFunction(string str){
	if(hasEvenParenth(str) && endCorrent(str) && !AdjOperators(str)){
		return true;
	} else {
		return false;
	}
}



int main() {
	cout << "Enter a function: " << endl;
	string str;
	getline(cin, str);
	if(isValidFunction(str)){
		cout << str << " is a Valid Function!" << endl;
	} else {
		cout << str << " is an Invalid Function!" << endl;
	}
	return 0;
}



