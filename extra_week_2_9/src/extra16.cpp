//============================================================================
// Name        : extra16.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// SIXTEENTH EXTRA ASSIGNMENT:
// Write program to read keyboard input.
// Change uppercase to lowercase
// Push into queue and stack
// check if line is a palindrome (read same way forward and backwards: racecar)

// Worked on it with Kevin


#include <iostream>
#include <stack>
#include <queue>
#include<ctime>
using namespace std;

bool isPalindrome(string &str){
	bool correct = true;
	int size = str.length();
	stack<char> stack, temp;
	queue<char> queue;
	//replace(str.begin(), str.end(), ',', ' ');
	//replace(str.begin(), str.end(), '.', ' ');
	//replace(str.begin(), str.end(), ',', ' ');
	//replace(str.begin(), str.end(), '.', ' ');
	for(int i = 0; i < size; i++){
		if(str[i] == ' ' || str[i] == ',' || str[i] == '.' || str[i] == ';'){
			temp.push(str[i]);
		} else{
			stack.push(tolower(str[i]));
			queue.push(tolower(str[i]));
		}
	}



	while(!stack.empty()){
		if(stack.top() == queue.front()){
			stack.pop();
			queue.pop();
		} else {
			correct = false;
			break;
		}
	}

	if(correct == false){
		return false;
	} else {
		return true;
	}
}


int main() {
	int start_s=clock();

	string input;
	cout << "Enter a string: " << endl;
	getline(cin, input);

	if(isPalindrome(input)){
		cout << input <<  " is a palindrome!" << endl;
	} else {
		cout << input <<  " is not a palindrome!" << endl;
	}

	int stop_s=clock();
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << " seconds!"<< endl;
	return 0;
}
