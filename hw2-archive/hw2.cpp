//============================================================================
// Name        : hw2.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// FIX END PARENTH


#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

/*
Functions:
1. IsEmpty
2. IsOperator
3. IsNumber
4. Evaluate
5. IsValidFunction
6. Priority
    1. What happens when priority is greater or less than
    2. If operatorStack.top() > current && !parenthesis, take top 2 integers and top operator and compute
    3. If operatorStack.top() > current && parenthesis, push to stack
    4.
    */



int getLineCount(string str, int &numCount){
	string str1;
	ifstream inputFile(str);
	getline(inputFile,str);
	while(!inputFile.eof()){
		getline(inputFile, str1);
		//cout << str << endl;
		numCount++;
	}
	return numCount;
}
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
bool hasEvenParenth(string str){
	bool failed = false;
	int size = str.length()-1;
	int counter = 0;
	for(int i = 0; i <= size; i++){
		if(str[i] == '('){
			counter++;
		} else if(str[i] == ')'){
			counter--;
		}
	}
	if(counter == 0){
		return true;
	} else {
		return false;
	}




	/*
	stack<char> temp;
	for(int i = 0; i < size; i++){
		if(str[i] == '('){
			temp.push(str[i]);
		} else if(str[i] == ')'){
			if(temp.empty()){
				failed = true;
			} else if(temp.top() == '('){
				temp.pop();
			}
		}
	}

	if(temp.empty()){
		return true;
	} else if(failed == true) {
		return false;
	}
	*/
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
int priority(char c){
	switch(c){
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		default:
			return -1;
	}
}
long long int math(long long  val1, long long val2, char op){
	if(op == '+'){
		return (val2 + val1);
	} else if(op == '-'){
		return (val2 - val1);
	} else if(op == '*'){
		return (val2 * val1);
	} else if(op == '/'){
		return (val2 / val1);
	}
}
void evaluate(stack<long long int> &N, stack<char> O){
	long long int val1 = N.top();
	N.pop();
	cout << "val1: " << val1 << endl;
	long long int val2 = N.top();
	N.pop();
	cout << "val2: " << val2 << endl;
	char op = O.top();
	O.pop();
	cout << "val1: " << val1 << " val2: " << val2 << " op: " << op << endl;
	long long int value = math(val1, val2, op);
	N.push(value);
}
void printStackI(stack<long long int> num){
	while(!num.empty()){
		cout << num.top() << endl;
		num.pop();
	}
}
void printStackO(stack<char> op){
	while(!op.empty()){
		cout << op.top() << endl;
		op.pop();
	}
}
long long int readInfix(string str){
	stack<char> op;
	stack<long long int> num;
	int size = str.length(), charCount = 0;
	string temp = " ";
	// "(2+3+42)"
	//cout << "size: " << size << endl;
	for(int i = 0; i <= size; i++){
		if(isdigit(str[i])){
			if(isdigit(str[i+1])){
				int x = i;
				temp += str[i];
				while(isdigit(str[x+1])){
					temp += str[x+1];
					x++;
				}
				long long int tempV = stoll(temp);
				/*
				if(!isdigit(str[i-2])){
					char operate = op.top();
					if(operate == '-'){
						num.push(-tempV);
						op.pop();
					} else if(operate == '+'){
						num.push(tempV);
						op.pop();
					}
				}
				*/
				num.push(tempV);
				//cout << "x: " << x << endl;
				i = x;
			} else {
				int tempV = str[i] - '0';
				num.push(tempV);
				/*
				if(!isdigit(str[i-2])){
					char operate = op.top();
					if(operate == '-'){
						cout << tempV << " changed to " << -tempV << endl;
						num.push(-tempV);
						op.pop();
					} else if(operate == '+'){
						num.push(tempV);
						op.pop();
					}
				}
				*/
			}
			cout << "Digit: " << num.top() << endl;
			charCount++;
			cout << "charCount: " << charCount << endl;
			temp = "";
		} else if(str[i] == '('){
			op.push(str[i]);
			cout << "Open: " << str[i] << endl;
			charCount++;
			cout << "charCount: " << charCount << endl;
		} else if(str[i] == ')'){
			cout << "Closed: " << str[i] << endl;

			cout << "---------------------------" << endl;
			printStackI(num);
			cout << "-------" << endl;
			printStackO(op);
			cout << "---------------------------" << endl;

			while(op.top() != '('){
				evaluate(num, op);
				op.pop();
				cout << "evaluated!" << endl;
				cout << "NUM: " << num.top() << endl;
			}
			op.pop();
			charCount++;
			cout << "charCount: " << charCount << endl;
		} else if(isLowOperator(str[i]) && op.empty()){
			if(str[i] == '-' && num.empty()){
				op.push(str[i]);
				num.push(0);
				cout << "First in line!: " << str[i] << endl;
				charCount++;
				cout << "charCount: " << charCount << endl;
			} else {
				op.push(str[i]);
				cout << "First in line!: " << str[i] << endl;
				charCount++;
				cout << "charCount: " << charCount << endl;
			}
		} else if(isLowOperator(str[i]) && op.top() == '('){
			if(str[i] == '-' && str[i-1] == '('){
				num.push(0);
				op.push(str[i]);
				cout << "Pushed: " << str[i] << endl;
			} else {
				op.push(str[i]);
				cout << "Pushed: " << str[i] << endl;
				if(num.empty()){
					num.push(0);
				}
			}

			charCount++;
			cout << "charCount: " << charCount << endl;
		} else if(isLowOperator(str[i]) && (priority(op.top()) < priority(str[i]))){
			cout << "Priority 2: " << str[i] << endl;
			op.push(str[i]);
			charCount++;
			cout << "charCount: " << charCount << endl;
		} else if(isLowOperator(str[i]) && (priority(op.top()) >= priority(str[i]))){
			cout << "op.top: " << op.top() << endl;
			cout << "Priority 1: " << str[i] << endl;
			evaluate(num, op);
			op.pop();
			op.push(str[i]);
			cout << "New Top: " << num.top() << endl;
			charCount++;
			cout << "charCount: " << charCount << endl;
		}

	}

	while(!op.empty()){
		evaluate(num, op);
		op.pop();
	}



	cout << "Stacks:" << endl;
	printStackI(num);
	printStackO(op);

	long long int result = num.top();
	return result;



}










int main(int argc, char* argv[]){

	if (argc < 2) {
		cout << "Usage: densemult \"input=<input21.txt>;output=<output1.txt>\"" << endl;
		return -1;
	}


	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output1 = am.get("output");
	ofstream outputFile(output1.c_str());




	//string input = "input21.txt", test = "((-1))-(-1)", str, output = "output1.txt";
	string str;
	ifstream inputFile(input);
	//ofstream outputFile(output1);
	int numCount = 1, size = input.length();
	getLineCount(input, numCount);
	cout << "HI" << endl;
	for(int i = 0; i < numCount; i++){
		getline(inputFile, str);
		cout << "--------------------------------------------" << endl;
		if(isValidFunction(str)){
			cout << str << endl;
			long long int value = readInfix(str);
			outputFile << str << "=" << value << endl;
		} else {
			outputFile << "error" << endl;
		}
		cout << "--------------------------------------------" << endl;
	}

}
