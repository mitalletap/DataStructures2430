// Help received from:
// cplusplus.org
// stackoverflow.org

// Mital Patel 33%, Steven Stricklin 33%, Edgar Garza 33%

#include<iostream>
#include<cstdio>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;

struct node
{
    string data;
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
        node *balance(node *);
        void checkSame(node* , string, vector<string> v1);
        void printIndex(node*, vector<string> &v1, vector<string> &v2);
        node *insert(node *, string, vector<string> &v1,  vector<string> &v2);
        int getLevelFunction(node *, string, int);
        int getLevel(node *, string, int);
        void display(node *, int);
        void inorder(node *);
        void preorder(node *);
        void postorder(node *);
        void printLevel(node *, int, int&);
        void indexCorrectly(node *root, int level, int& number);
        //node *getDuplicates(node *, string);
        //void convertToArray(node *, int, vector<string> &v2);
        Tree(){
            root = NULL;
        }
};

void menu(int& selection, Tree tree1, vector<string> &v1,  vector<string> &v2){
	cout << "Select an option:" << endl;
	cout << "1. View Tree" << endl;
	cout << "2. View Inorder" << endl;
	cout << "3. View Preorder" << endl;
	cout << "4. View Postorder" << endl;
	cout << "5. View Duplicates" << endl;
	cout << "6. Exit" << endl;
	cin >> selection;
	cout << endl;
	int number = 0, level = 3, totalPossible = ((v1.size() - 1)/2) + 1;

	if(selection > 0 && selection <= 6){
		switch(selection){
		case 1:
			cout << "Tree: ";
			tree1.display(root, 1);
			cout << endl;
			cout << endl;
			break;
		case 2:
			cout << "Inorder: ";
			tree1.inorder(root);
			cout << endl;
			cout << endl;

			break;
		case 3:
			cout << "Preorder: ";
			tree1.preorder(root);
			cout << endl;
			cout << endl;
			break;
		case 4:
			cout << "Postorder: ";
			tree1.postorder(root);
			cout << endl;
			cout << endl;
			break;
		case 5:
			cout << "Duplicates:" << endl;
			if(v2.size() != 0){
				tree1.printIndex(root, v1, v2);
				cout << endl;
			} else {
				cout << "No Duplicates!" << endl;
			}

			//tree1.indexCorrectly(root, totalPossible, number);
			cout << endl;
			break;
		case 6:
			cout << "Goodbye..." << endl;;
			exit(0);
		}
	} else {
		cout << "Error! You chose incorrectly!" << endl;
	}
	menu(selection, tree1, v1, v2);
}

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


int main(){



	string temp, numb, str; //str = "mital patel is a pan named mital1";
	int level, index = 1, selection, number;
	vector<string> v1;
	vector<string> v2;
	cout << "Enter a string: ";
	getline(cin, str);
	Tree tree1;
	//ifstream inputFile(input);
	stringstream ss(str);
	while(ss >> temp){
		root = tree1.insert(root, temp, v1, v2);
	}
	menu(selection, tree1, v1, v2);

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

void Tree::checkSame(node *root , string value, vector<string> v1){
	while(root != NULL){
		if (root->data == value){
			cout << "Value: " << value << endl;
		}
		checkSame(root->left, value, v1);
		checkSame(root->right, value, v1);
	}
}

void Tree::printIndex(node *root , vector<string> &v1, vector<string> &v2){

	for(int i = 0; i < v2.size(); i++){
		for(int j = 0; j < v1.size(); j++){
			if(v2[i] == v1[j]){
				cout << v2[i] << " found at index " << j << endl;
			}
		}
	}

//	if (v1 < root->data){
//		printIndex(root->left, v1, index+1);
//	} else if (v1 > root->data){
//		printIndex(root->right, v1, index*2);
//	} else if (v1 == root->data){
//		//cout << value << " can be found at " << index << endl;
//		int x = getLevelFunction(root, v1, index);
//		cout << v1 << " at level " << x << endl;
//		if(root->right != NULL){
//			printIndex(root->right, v1, index+1);
//		}
//	}

}

void Tree::indexCorrectly(node *root, int size, int& number){
	int i = 0;
	if(root == NULL){
		return;
	} else if(i != size){
		cout << "Data: " << root->data << endl;
		cout << number+2 << endl;
		i++;
		printLevel(root->left, size-1, number);
		printLevel(root->right, size-1, number);
	} else {
		printLevel(root->left, size-1, number);
		printLevel(root->right, size-1, number);
	}
}

node *Tree::insert(node *root, string value, vector<string> &v1, vector<string> &v2){
    if (root == NULL){
        root = new node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        v1.push_back(root->data);
        return root;
    } else if (value < root->data){
        root->left = insert(root->left, value, v1, v2);
        root = balance (root);
    } else if (value > root->data){
        root->right = insert(root->right, value, v1, v2);
        root = balance (root);
    } else if (value == root->data){
    		root->right = insert(root->right, value, v1, v2);
		root = balance (root);
		v2.push_back(value);
    }
    return root;
}

int Tree::getLevelFunction(node *root, string str, int level){
	if(root == NULL){
		return 0;
	}
	if(root->data == str){
		return level;
	}

	int downLevel = getLevel(root->left, str, level+1);
	if(downLevel != 0){
		return downLevel;
	}
	downLevel = getLevel(root->right, str, level+1);
	if(downLevel != 0){
		return downLevel;
	}
	if(root->data != str){
		return 0;
	}
}

int Tree::getLevel(node *root, string str, int level){
	return getLevelFunction(root, str, level);
}

void Tree::display(node *ptr, int level){
    int i;
    if (ptr!=NULL){
        display(ptr->right, level + 1);
        cout << endl;
        if (ptr == root)
        cout << "Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->data;
        display(ptr->left, level + 1);
    }
}

void Tree::inorder(node *tree){
    if (tree == NULL)
        return;
    inorder (tree->left);
    cout<<tree->data<<"  ";
    inorder (tree->right);
}

void Tree::preorder(node *tree){
    if (tree == NULL)
        return;
    cout<<tree->data<<"  ";
    preorder (tree->left);
    preorder (tree->right);

}

void Tree::postorder(node *tree){
    if (tree == NULL)
        return;
    postorder (tree->left);
    postorder (tree->right);
    cout<<tree->data<<"  ";
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
