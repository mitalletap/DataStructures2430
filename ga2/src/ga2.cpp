//============================================================================
// Name        : ga2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// Mital Patel 33%, Edgar Garza 33%, Steven Stricklin 33%


#include <iostream>
using namespace std;

class node {
public:
	int data;
	node *next;
	node *prev;
	node();
	node(int);
	bool isEmpty();
	void addToBegin(node inputNode, int value);
	void addToIndex(node inputNode, int value, int index);
	void addToEnd(node inputNode, int value);
	void deleteAtBegin();
	void deleteAtIndex(node inputNode, int index);
	void deleteAtEnd();
	void deleteAll();
	void print();
	void search(int value);
};

node *head = NULL;
node *tail = NULL;


// IsEmpty DONE
// AddToBegin DONE
// AddToMid DONE
// AddToEnd DONE
// DeleteBegin DONE
// DeleteMid DONE
// DeleteEnd DONE
// Print DONE
// DeleteAll DONE
// Search DONE


node::node(){
	data = 0;
	next = NULL;
	prev = NULL;
}

node::node(int value){
	data = value;
	next = NULL;
	prev = NULL;
}

bool node::isEmpty(){
	return (head == NULL);
}

void node::addToBegin(node inputNode, int value){
	if(inputNode.isEmpty()){
		node *temp = new node(value);
		head = temp;
		tail = head;
		/*
		cout << "head->prev: " << head->prev << endl;
		cout << "head->next: " << head->next << endl;
		cout << "head->data: " << head->data << endl;
		*/
	} else {
		node *temp = new node(value);
		temp->next = head;
		head = temp;
		/*
		cout << "head->prev: " << head->prev << endl;
		cout << "head->next: " << head->next << endl;
		cout << "head->data: " << head->data << endl;
		*/
	}
}

void node::addToIndex(node inputNode, int value, int index){

	if(inputNode.isEmpty()){
		node *temp = new node(value);
		head = temp;
		tail = head;
	} else {
		int counter = 0;
		node *cu = head;
		for(int i = 1; i < index - 1; i++){
			cu = cu->next;
			counter++;
		}
		cout << cu->data << endl;

		//set pr to 4th index and ne to 5th
		node *pr = cu;
		node *ne = cu->next;


		// create new node with the data
		node *newNode = new node(value);
		newNode->prev = pr;
		pr->next = newNode;
		newNode->next = ne;
		ne->prev = newNode;
	}
}

void node::addToEnd(node inputNode, int value){
	if(inputNode.isEmpty()){
		node *temp = new node(value);
		head = temp;
		tail = head;
	} else {
		node *temp = new node(value);
		tail->next = temp;
		temp->next = tail;
		tail = temp;
	}
}

void node::deleteAtBegin(){
	node *current = head->next;
	current->prev = NULL;
	current->next = head->next->next;
	head->next = NULL;
	free(head);
	head = current;
}

void node::deleteAtIndex(node inputNode, int index){
	if(inputNode.isEmpty()){
		cout << "List is Empty!" << endl;
	} else {
		int counter = 0;
		node *cu = head;
		for(int i = 1; i < index - 1; i++){
			cu = cu->next;
			counter++;
		}

		//set pr to 4th index and ne to 5th
		node *pr = cu;
		node *deleteNode = cu->next;
		node *ne = cu->next->next;

		pr->next = ne;
		ne->prev = pr;
		deleteNode->next = NULL;
		deleteNode->prev = NULL;
		free(deleteNode);
	}
}

void node::deleteAtEnd(){
	node *current = head;
	while(current->next != tail){
			current = current->next;
			cout << current->data << endl;

		}
		current->next = NULL;
		tail->prev = NULL;
		tail->next = NULL;
		tail = current;
		free(current);
}

void node::deleteAll(){
	node *cu = head;
	node *temp;
	while(cu != NULL){
		temp = cu->next;
		free(cu);
		cu = next;
	}
	head = NULL;

}

void node::search(int value){
	int counter = 1;
	node *cu = head;
	while(cu != NULL){
		if(cu->data == value){
			cout << cu->data << " found at the " << counter << " index!" << endl;
			break;
		} else {
			cu = cu->next;
			counter++;
		}
	}
}

void node::print(){
	if(head == tail){
		cout << "-------------" << endl;
		cout << "list is empty" << endl;
		cout << "-------------" << endl;
	} else {
		node *cu = head;
		cout << endl;
		cout << "List: " << endl;
		cout << "-------------" << endl;
		while(cu != tail){
			cout << cu->data << endl;
			cu = cu->next;
		}
		cout << cu->data << endl;
		cout << "-------------" << endl;
		//cout << cu->data << endl;
	}
}

int main() {

	int size, indexToAdd, valueToAdd, indexToDelete, searchNumber;
	char option;
	cout << "Enter the size of the list: " << endl;
	cin >> size;

	node node1;
	cout << "Added " << size << " elements..." << endl;
	for(int i = 0; i < size; i++){
		node1.addToBegin(node1, i);
	}
	node1.print();
	cout << endl;

	cout << "Enter the value to add: " << endl;
	cin >> valueToAdd;

	cout << "Enter the index in which that value will be added: " << endl;
	cin >> indexToAdd;

	if(indexToAdd > size){
		cout << "Error! Index is greater than the size of the linked list!" << endl;
		exit(0);
	}
	cout << "Adding the value " << valueToAdd << " to the " << indexToAdd << " position..." << endl;
	node1.addToIndex(node1, valueToAdd, indexToAdd);
	node1.print();
	cout << endl;

	cout << "Enter the index to Delete: " << endl;
	cin >> indexToDelete;

	cout << "Deleting the " << indexToDelete << " position..." << endl;
	node1.deleteAtIndex(node1, indexToDelete);
	node1.print();
	cout << endl;

	cout << "Enter a number to search for: " << endl;
	cin >> searchNumber;
	cout << "Searching for " << searchNumber << endl;
	node1.search(searchNumber);
	node1.print();
	cout << endl;

	cout << "Delete first element: T/F" << endl;
	cin >> option;
	if(option == 'T'){
		cout << "Deleting first element..." << endl;
		node1.deleteAtBegin();
		node1.print();
		cout << endl;
	}

	cout << "Delete Last element: T/F" << endl;
	cin >> option;
	if(option == 'T'){
		cout << "Deleting last element..." << endl;
		node1.deleteAtEnd();
		node1.print();
		cout << endl;
	}

	cout << "Delete All element: T/F" << endl;
	cin >> option;
	if(option == 'T'){
		cout << "Deleting All element." << endl;
		node1.deleteAll();
		node1.print();
		cout << endl;
	}
	return 0;
}
