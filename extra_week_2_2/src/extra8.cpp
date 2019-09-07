//============================================================================
// Name        : extra8.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// Help received from http://btechsmartclass.com/


// EIGHTH EXTRA ASSIGNMENT:
// Implement Doubly Linked List with all functionality
// Read forward and backwards





#include <iostream>
using namespace std;

struct node {
	int data;
	node *next;
	node *prev;
};

node *head = NULL;


void insertAtEnd(int value){
	node *newNode = new node;
	newNode->data = value;
	newNode->next = NULL;
	if(head == NULL){
		newNode->prev = NULL;
		head = newNode;
		newNode->next = NULL;
	} else {
		node *temp = head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newNode;
		newNode->prev = temp;
		newNode->next = NULL;
	}
}

void displayForward(){
	if(head == NULL){
		cout << "list empty" << endl;
	} else {
		node *temp = head;
		while(temp != NULL){
			cout << temp->data << endl;
			temp = temp->next;
		}
	}

}

void displayBackwards(){
	if(head == NULL){
		cout << "list empty" << endl;
	} else {
		node *temp = head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		while(temp != NULL){
			cout << temp->data << endl;
			temp = temp->prev;
		}
	}

}












int main() {

	insertAtEnd(1);
	insertAtEnd(2);
	insertAtEnd(3);
	insertAtEnd(4);
	cout << "Forward:" << endl;
	displayForward();
	cout << "Backwards:" << endl;
	displayBackwards();


	return 0;
}
