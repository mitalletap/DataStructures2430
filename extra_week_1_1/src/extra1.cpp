//============================================================================
// Name        : extra1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
//Yeets
#include <iostream>
using namespace std;
int CONST_VALUE = 5;

struct node {
	int data;
	node *next;
};

void createNodes(int *array);

int main() {

	int array[5] = {12, 13, 55,66, 77};
	createNodes(array);



}

void createNodes(int *array){
	node* head, *cu;
	head = new node;
	int i = 1;
	head->data = array[0];
	head->next = new node;
	cu = head->next;
	cu->data = array[1];
	cu->next = new node;
	cu = cu->next;
	cu->data = array[2];
	cu->next = new node;
	cu = cu->next;
	cu->data = array[3];
	cu->next = new node;
	cu = cu->next;
	cu->data = array[4];
	cu->next = NULL;

	while(head != NULL){
		cout << head->data << endl;
		head = head->next;
	}
}


