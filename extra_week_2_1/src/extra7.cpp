//============================================================================
// Name        : extra7.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// SEVENTH EXTRA ASSIGNMENT:
// Circularly linked list, deleted ever other word. Check rounds



#include <iostream>
#include<string>
#include <stack>
using namespace std;

struct node {
	char data;
	node *next;
};


void push(node **head, char value){



	node *ptr = new node;
	node *temp = *head;
	ptr->data = value;
	ptr->next = *head;

	if(*head != NULL){
		while(temp->next != *head){
			temp = temp->next;
		}
		temp->next = ptr;

	} else {
		ptr->next = ptr;
	}
	*head = ptr;
}

void p(node *head){
	node *temp = head;
	if(head != NULL){
		do {
			cout << temp->data << endl;
			temp = temp->next;
		} while(temp != head);

	}
}

int getCount(node *head){
	node *temp = head;
	int counter = 0;
	if(head != NULL){
		do {
			temp = temp->next;
			counter++;
		} while(temp != head);
	}
	return counter;
}

void rounds(node *head){
	int i = 1;
	int counter = getCount(head);
	node *prev = head;
	node *cu = prev->next;
	while(prev != prev->next && cu != NULL){
		cout << "Deleting " << cu->data << " on round " << i << endl;
		prev->next = cu->next;
		free(cu);
		i++;

		prev = prev->next;
		if(cu != NULL){
			cu = prev->next;
		}
		if(i == counter){
			cout << "Deleting " << cu->data << " on round " << i << endl;
			free(cu);
		}
	}
	p(head);
	cout << "Round completed!" << endl;
}





int main() {
	node *head = NULL;
	string input;
	stack<char> cStack;
	cout << "Enter a word: " << endl;
	cin >> input;
	int size = input.length();

	for(int i = 0; i < input.length(); i++){
		cStack.push(tolower(input[i]));
	}
	while(!cStack.empty()){
		push(&head, cStack.top());
		cStack.pop();
	}


	p(head);
	rounds(head);
	cout << "FINAL LIST: " << endl;
	p(head);

	return 0;
}
