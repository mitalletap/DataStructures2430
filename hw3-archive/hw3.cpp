// Received help from geetksforgeeks.
#include<iostream>
#include<cstdio>
#include<sstream>
#include<fstream>
#include<algorithm>
#include "ArgumentManager.h"
using namespace std;

struct node {
    int data;
    struct node *left;
    struct node *right;
}*root;

class Tree {
    public:
        int height(node *);
        int diff(node *);
        node *rightRight(node *);
        node *leftLeft(node *);
        node *leftRight(node *);
        node *rightLeft(node *);
        node* balance(node *);
        node* insert(node *, int );
        void display(node *, int);
        void inorder(node *, string &postorder);
        void preorder(node *, string &postorder);
        void postorder(node *, string &postorder);
        void printLevel(node *, int, string&);
        Tree() {
            root = NULL;
        }
};


int getLineCount(string input, int &numCount){
	string str1;
	ifstream inputFile(input);
	while(!inputFile.eof()){
		getline(inputFile,str1);
		numCount++;
		if(str1 == ""){
			numCount--;
		}
	}
	return numCount;
}



int main(int argc, char* argv[]){


	ArgumentManager am(argc, argv);
	string value = am.get("value");
	string command = am.get("command");
	string output = am.get("output");
	ofstream outputFile(output.c_str());


	//string value = "input33.txt", command = "command33.txt", output = "output33.txt";
	string temp1, temp2, str;
	ifstream inputFile(value);
	ifstream commandFile(command);
	int numCount = 0, number = 0;

	Tree tree1;
	stringstream sF(value), sC(command);
	numCount = getLineCount(value, numCount);
	string numbers[numCount];
	//Store numbers in array




	for(int i = 0; i < numCount; i++){
		getline(inputFile, temp1);
		numbers[i] = temp1;
	}

	for(int i = 0; i < numCount; i++){
		stringstream sF(numbers[i]);
		while(sF >> temp1){
			int a = stoi(temp1);
			root = tree1.insert(root, a);
		}
	}

	numCount = getLineCount(command, numCount);
	string inorder, preorder, postorder, levelOfTree;
	while(!commandFile.eof()){
		getline(commandFile, str);
		//cout << str << endl;
		stringstream sC(str);
		while(sC >> temp1 >> temp2){
			if(temp1 == "Preorder"){
				//cout << "Preorder: " << endl;
				tree1.preorder(root, preorder);
				outputFile << preorder << endl;
			} else if(temp1 == "Inorder"){
				//cout << "Inorder: " << endl;
				tree1.inorder(root, inorder);
				outputFile << inorder << endl;
			} else if(temp1 == "Postorder"){
				//cout << "Postorder: " << endl;
				tree1.postorder(root, postorder);
				outputFile << postorder << endl;
			} else {
				int num = stoi(temp2);
				int y = tree1.height(root);
				if(num > y){
					outputFile << "empty" << endl;
				} else {
					tree1.printLevel(root, num, levelOfTree);
					outputFile << levelOfTree << endl;
				}
				//cout << "Print Level: " << endl;
				levelOfTree.clear();
			}
		}
	}

//	inorder = "", preorder = "", postorder = "", levelOfTree = "";
	inorder.clear(), preorder.clear(), postorder.clear();



    return 0;
}


int Tree::height(node *temp){
    int h = 0;
    if (temp != NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

int Tree::diff(node *temp){
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}

node *Tree::rightRight(node *parent){
    node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

node *Tree::leftLeft(node *parent){
    node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

node *Tree::leftRight(node *parent){
    node *temp;
    temp = parent->left;
    parent->left = rightRight(temp);
    return leftLeft(parent);
}

node *Tree::rightLeft(node *parent){
    node *temp;
    temp = parent->right;
    parent->right = leftLeft(temp);
    return rightRight(parent);
}

node *Tree::balance(node *temp){
    int bal_factor = diff (temp);
    if (bal_factor > 1){
        if (diff (temp->left) > 0)
            temp = leftLeft(temp);
        else
            temp = leftRight(temp);
    }
    else if (bal_factor < -1){
        if (diff (temp->right) > 0)
            temp = rightLeft(temp);
        else
            temp = rightRight(temp);
    }
    return temp;
}

node *Tree::insert(node *root, int value){
    if (root == NULL){
        root = new node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->data){
        root->left = insert(root->left, value);
        root = balance (root);
    }
    else if (value > root->data){
        root->right = insert(root->right, value);
        root = balance (root);
    }
    return root;
}

void Tree::display(node *ptr, int level){
    int i;
    if (ptr!=NULL){
        display(ptr->right, level + 1);
        cout << endl;
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->data;
        display(ptr->left, level + 1);
    }
}

void Tree::inorder(node *tree, string &inorderS){
    if (tree == NULL){
    	 	 return;
    } else {
		inorder(tree->left, inorderS);
		inorderS += to_string(tree->data) + " ";
		inorder(tree->right, inorderS);
    	}
}

void Tree::preorder(node *tree, string &preorderS){
    if (tree == NULL){
    		return;
    } else {
    		preorderS += to_string(tree->data) + " ";
    	    preorder(tree->left, preorderS);
    	    preorder(tree->right, preorderS);
    }
}

void Tree::postorder(node *tree, string &postorderS){
    if (tree == NULL){
    		return;
    } else {
    		postorder(tree->left, postorderS);
    	    postorder(tree->right, postorderS);
    	    postorderS += to_string(tree->data) + " ";
    }
}

void Tree::printLevel(node *root, int level, string& levelOfTree){
	if(root == NULL){
		return;
	} else if(level == 1){
		levelOfTree += to_string(root->data) + " ";
		//v1.push_back(root->data);
	} else {
		printLevel(root->left, level-1, levelOfTree);
		printLevel(root->right, level-1, levelOfTree);
	}

}





























/*
// Received help from geetksforgeeks.
#include<iostream>
#include<cstdio>
#include<sstream>
#include<fstream>
#include<algorithm>
#include "ArgumentManager.h"
using namespace std;

struct node {
    int data;
    struct node *left;
    struct node *right;
}*root;

class Tree {
    public:
        int height(node *);
        int diff(node *);
        node *rightRight(node *);
        node *leftLeft(node *);
        node *leftRight(node *);
        node *rightLeft(node *);
        node* balance(node *);
        node* insert(node *, int );
        void display(node *, int);
        void inorder(node *);
        void preorder(node *);
        void postorder(node *);
        void printLevel(node *, int, int&);
        Tree() {
            root = NULL;
        }
};


int getLineCount(string input, int &numCount){
	string str1;
	ifstream inputFile(input);
	while(!inputFile.eof()){
		getline(inputFile,str1);
		numCount++;
		if(str1 == ""){
			numCount--;
		}
	}
	return numCount;
}



int main(int argc, char* argv[]){


	ArgumentManager am(argc, argv);
	string value = am.get("value");
	string command = am.get("command");
	string output = am.get("output");
	ofstream outputFile(output.c_str());


	//string value = "input33.txt", command = "command33.txt", output = "output33.txt";
	string temp1, temp2, str;
	ifstream inputFile(value);
	ifstream commandFile(command);
	int numCount = 0, number = 0;

	Tree tree1;
	stringstream sF(value), sC(command);
	numCount = getLineCount(value, numCount);
	string numbers[numCount];
	//Store numbers in array




	for(int i = 0; i < numCount; i++){
		getline(inputFile, temp1);
		numbers[i] = temp1;
	}

	for(int i = 0; i < numCount; i++){
		stringstream sF(numbers[i]);
		while(sF >> temp1){
			int a = stoi(temp1);
			root = tree1.insert(root, a);
		}
	}

	numCount = getLineCount(command, numCount);

	while(!commandFile.eof()){
		getline(commandFile, str);
		//cout << str << endl;
		stringstream sC(str);
		while(sC >> temp1 >> temp2){
			if(temp1 == "Preorder"){
				//cout << "Preorder: " << endl;
				tree1.preorder(root);
				cout << endl;
			} else if(temp1 == "Inorder"){
				//cout << "Inorder: " << endl;
				tree1.inorder(root);
				cout << endl;
			} else if(temp1 == "Postorder"){
				//cout << "Postorder: " << endl;
				tree1.postorder(root);
				cout << endl;
			} else {
				int num = stoi(temp2);
				int y = tree1.height(root);
				if(num > y){
					outputFile << "error" << endl;
				} else {
					tree1.printLevel(root, num, number);
					cout << endl;
					cout << "Number: " << number << endl;
				}
				//cout << "Print Level: " << endl;

			}
		}
	}



    return 0;
}


int Tree::height(node *temp){
    int h = 0;
    if (temp != NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

int Tree::diff(node *temp){
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}

node *Tree::rightRight(node *parent){
    node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

node *Tree::leftLeft(node *parent){
    node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

node *Tree::leftRight(node *parent){
    node *temp;
    temp = parent->left;
    parent->left = rightRight(temp);
    return leftLeft(parent);
}

node *Tree::rightLeft(node *parent){
    node *temp;
    temp = parent->right;
    parent->right = leftLeft(temp);
    return rightRight(parent);
}

node *Tree::balance(node *temp){
    int bal_factor = diff (temp);
    if (bal_factor > 1){
        if (diff (temp->left) > 0)
            temp = leftLeft(temp);
        else
            temp = leftRight(temp);
    }
    else if (bal_factor < -1){
        if (diff (temp->right) > 0)
            temp = rightLeft(temp);
        else
            temp = rightRight(temp);
    }
    return temp;
}

node *Tree::insert(node *root, int value){
    if (root == NULL){
        root = new node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->data){
        root->left = insert(root->left, value);
        root = balance (root);
    }
    else if (value > root->data){
        root->right = insert(root->right, value);
        root = balance (root);
    }
    return root;
}

void Tree::display(node *ptr, int level){
    int i;
    if (ptr!=NULL){
        display(ptr->right, level + 1);
        cout << endl;
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->data;
        display(ptr->left, level + 1);
    }
}

void Tree::inorder(node *tree){
    if (tree == NULL){
    	 	 return;
    } else {
		inorder(tree->left);
		cout << tree->data << " ";
		inorder(tree->right);
    	}
}

void Tree::preorder(node *tree){
    if (tree == NULL){
    		return;
    } else {
	    cout << tree->data << " ";
    	    preorder(tree->left);
    	    preorder(tree->right);
    }
}

void Tree::postorder(node *tree){
    if (tree == NULL){
    		return;
    } else {
    		postorder (tree->left);
    	    postorder (tree->right);
    	    cout << tree->data << " ";
    }
}

void Tree::printLevel(node *root, int level, int& number){
	if(root == NULL){
		return;
	} else if(level == 1){
		cout << root->data << " ";
		//v1.push_back(root->data);
	} else {
		printLevel(root->left, level-1, number);
		printLevel(root->right, level-1, number);
	}
	number = level;
}

 */
