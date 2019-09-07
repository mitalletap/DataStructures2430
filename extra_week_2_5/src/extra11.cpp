//============================================================================
// Name        : extra11.cpp
// Author      : Mital Patel (34%), Steven Stricklin (33%), Edgar Garza (33%)
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;



class LL {

	struct node{
		int data;
		node *next;
	};

	node *top;

public:
	LL(){
		top = NULL;
	}
	void push(int elt){
		node *n = new node;
		n->data = elt;
		n->next = top;
		top = n;
	}
	int pop(){
		node *temp = top;
		top = temp->next;
		return temp->data;
	}
	bool isEmpty(){
		if(top == NULL){
			return true;
		} else {
			return false;
		}
	}

	void display(){
		node *n = top;
		while(n != NULL){
			cout << n->data << "\n";
			n = n->next;
		}
	}

	void removeAll(){
		while(top != NULL){
			pop();
			top = top->next;
		}
	}

	void search(int elt){
		if(isEmpty()){
			cout << "empty" << endl;
		} else {
			node *n = top;
			while(n != NULL){
				int counter = 1;
				if(n->data == elt){
					cout << elt << " found at node " << counter << " from the top of the stack!" << endl;
					//exit(0);
					n = n->next;
					pop();
				}

				if(n->data != elt){
					n = n->next;
					pop();

				}
				counter++;

			}

		}


	}


};





int main() {
	cout << "Creating Stack..." << endl;
	LL stack1;
	cout << "Pushing To Stack..." << endl;
	stack1.push(1);
	stack1.push(2);
	stack1.push(3);
	stack1.push(4);
	stack1.push(5);
	stack1.push(6);
	cout << "Displaying Stack..." << endl;
	stack1.display();
	cout << "Searching In Stack..." << endl;
	stack1.search(6);

	cout << "Deleting All In Stack..." << endl;
	stack1.removeAll();

	return 0;
}
