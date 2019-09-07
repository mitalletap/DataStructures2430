// I had resources from last semester which I used to complete this assignment as well as
// Brandon Labuschagne on youtube

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;


struct node {
	// Keys
	/*
	string identificationK;
	string fNameK;
	string lNameK;
	string dobK;
	string gpaK;
	*/
	// Values
	string identificationV;
	string fNameV;
	string lNameV;
	string dobV;
	string gpaV;
	node *next;
};


bool isEmpty(node *head);
void insertAtFirst(node *&head, node *&last, string idV, string fNameV, string lNameV, string dobV, string gpaV);
void insert(node *&head, node *&last, string idV, string fNameV, string lNameV, string dobV, string gpaV);
void remove(node *&head, node *&last);
void removeAtValue(node *&head, string V);
void showListDeleted(node *current, string valueToDelete);
void showList(node *cu);
void deleteExtra(node *cu, string V);
void printFormatted(node *current, const char* filename);
int getLineNumber(string file, int& number);
string removeDelimiters(string&line);
string readAttributes(string file, string& idNumber, string& nameFirst, string& nameLast, string& birthDate, string& gradePoint);
bool hasKey(node *cu, string V);
void sort(node *head, string attribute1, string attribute2, string attribute3, string attribute4, string attribute5);


int main(int argc, char* argv[]){

	if (argc < 2) {
		cout << "Usage: densemult \"input=<input1.txt>;output=<output1.txt>;sort=<sort1.txt>\"" << endl;
		return -1;
	}

	ArgumentManager am(argc, argv);
	string input1 = am.get("input");
	string output1 = am.get("output");
	string sort1 = am.get("sort");
	ofstream outputFile(output1.c_str());

	node *head = NULL;
	node *last = NULL;

	int m = -1, z = 0, x = 0, number = 0;
	string file = input1, attributeFile = sort1, str, temp, idNumber, nameFirst, nameLast, birthDate, gradePoint, valueToDelete;
	getLineNumber(file, number);
	string arrayLine[number], value[number][5];
	ifstream input(file);
	while(getline(input, str)){
		arrayLine[z] = str;
		z++;
	}

	for(int i = 0; i < number; i++){
		x = 0;
		m++;
		temp = arrayLine[m];
		string ID = " ", nameF = " ", nameL = " ", bDay = " ", grade = " ";
		removeDelimiters(temp);
		stringstream ss(temp);
		string K, V;
		while(ss >> K >> V){
			if(K == "delete"){
				valueToDelete = V;
				removeAtValue(head, valueToDelete);
			} else {
				value[m][x] = V;
				x++;
				//ID = value[m][0], nameF = value[m][1], nameL = value[m][2], bDay = value[m][3], grade = value[m][4];

			}


		}
		insert(head, last, value[m][0], value[m][1], value[m][2], value[m][3], value[m][4]);

	}

	string attribute1, attribute2, attribute3, attribute4, attribute5;
	readAttributes(attributeFile, attribute1, attribute2, attribute3, attribute4, attribute5);
	deleteExtra(head, valueToDelete);
	sort(head, attribute1, attribute2, attribute3, attribute4, attribute5);
	deleteExtra(head, valueToDelete);
	printFormatted(head, output1.c_str());
	return 0;
}



bool isEmpty(node *head){
	if(head == NULL){
		return true;
	} else {
		return false;
	}

}
void insertAtFirst(node *&head, node *&last, string idV, string fNameV, string lNameV, string dobV, string gpaV){
	node *temp = new node;

	// Assign the values
	temp->identificationV = idV;
	temp->fNameV = fNameV;
	temp->lNameV = lNameV;
	temp->dobV = dobV;
	temp->gpaV = gpaV;
	temp->next = NULL;
	head = temp;
	last = temp;
}
void insert(node *&head, node *&last, string idV, string fNameV, string lNameV, string dobV, string gpaV){
	if(isEmpty(head)){
		insertAtFirst(head, last, idV, fNameV, lNameV, dobV, gpaV);
	} else {
		node *temp = new node;
		// Assign the values
		temp->identificationV = idV;
		temp->fNameV = fNameV;
		temp->lNameV = lNameV;
		temp->dobV = dobV;
		temp->gpaV = gpaV;
		temp->next = NULL;
		last->next = temp;
		last = temp;
	}
}
void remove(node *&head, node *&last){
	if(isEmpty(head)){
		cout << "The list is empty" << endl;
	} else if(head == last){
		delete head;
		head = NULL;
		last = NULL;
	} else {
		node *temp = new node;
		temp = head;
		head = head->next;
		delete temp;
	}

}
bool hasKey(node *cu, string V){
	if(cu != NULL && (cu->identificationV == V || cu->fNameV == V || cu->lNameV == V || cu->dobV == V || cu->gpaV == V)){
		return true;
	} else {
		return false;
	}
}
void removeAtValue(node *&head, string V){
	if(isEmpty(head)){
		cout << "The list is empty" << endl;
	} else {
		node *cu = head;
		node *prev = 0;
		if(cu != NULL && (cu->identificationV != V || cu->fNameV != V || cu->lNameV != V || cu->dobV != V || cu->gpaV != V)){
			prev = cu;
			cu = cu->next;
		}

		if(cu->identificationV == V || cu->fNameV == V || cu->lNameV == V || cu->dobV == V || cu->gpaV == V){
			/*
			prev->next = cu->next;
			delete cu;
			*/

			cu->identificationV = "", cu->fNameV = "", cu->lNameV = "", cu->dobV = "", cu->gpaV = "";
			prev->next = cu->next;
		}
	}

}
void showListDeleted(node *cu, string valueToDelete){
	if(isEmpty(cu)){
		cout << "The list is empty" << endl;
	} else {
		cout << "The list contains: " << endl;
		cout << "-------------------" << endl;
		while(cu != NULL){
			if((cu->identificationV == "" || cu->fNameV == "" || cu->lNameV == "" || cu->dobV == "" || cu->gpaV == "")){
				cu = cu->next;
			}
			if(hasKey(cu, valueToDelete)){
				cout << "Deleting Value: " << endl;
				removeAtValue(cu, valueToDelete);
			}
			//idV, fNameV, lNameV, dobV, gpaV
			cout << "ID: " << cu->identificationV << endl;
			cout << "First Name: " << cu->fNameV << endl;
			cout << "Last Name: " << cu->lNameV << endl;
			cout << "DOB: " << cu->dobV << endl;
			cout << "GPA: " << cu->gpaV << endl;
			cout << "-------------------" << endl;
			cu = cu->next;
		}
	}

}
void showList(node *cu){
	if(isEmpty(cu)){
		cout << "The list is empty" << endl;
	} else {
		cout << "The list contains: " << endl;
		cout << "-------------------" << endl;
		while(cu != NULL){
			if((cu->identificationV == "" || cu->fNameV == "" || cu->lNameV == "" || cu->dobV == "" || cu->gpaV == "")){
				cu = cu->next;
			}
			//idV, fNameV, lNameV, dobV, gpaV
			cout << "ID: " << cu->identificationV << endl;
			cout << "First Name: " << cu->fNameV << endl;
			cout << "Last Name: " << cu->lNameV << endl;
			cout << "DOB: " << cu->dobV << endl;
			cout << "GPA: " << cu->gpaV << endl;
			cout << "-------------------" << endl;
			cu = cu->next;
		}
	}

}
void deleteExtra(node *cu, string V){
	while(cu != NULL){
		if ((hasKey(cu, V))){
			cu->identificationV = "", cu->fNameV = "", cu->lNameV = "", cu->dobV = "", cu->gpaV = "";
			cu = cu->next;
		} else {
			cu = cu->next;
		}
	}
}
void printFormatted(node *cu, const char* filename){
	ofstream outputFile(filename);
	if(isEmpty(cu)){
		cout << "The list is empty";
	} else {
		while(cu != NULL){
			//idV, fNameV, lNameV, dobV, gpa
			if(cu->fNameV == ""){
				cu = cu->next;
			} else {
				outputFile << "{id:" << cu->identificationV << ",first:" << cu->fNameV << ",last:" << cu->lNameV << ",DOB:" << cu->dobV << ",GPA:" << cu->gpaV << "}" << endl;
				cu = cu->next;
			}

		}
	}
}
int getLineNumber(string file, int& number){
	string str;
	ifstream input(file);
	while(getline(input,str)){
		number++;
	}
	return number;
}
string removeDelimiters(string &line){
	replace(line.begin(), line.end(), '{', ' ');
	replace(line.begin(), line.end(), '}', ' ');
	replace(line.begin(), line.end(), ':', ' ');
	replace(line.begin(), line.end(), ',', ' ');
	return line;
}
string readAttributes(string file, string& idNumber, string& nameFirst, string& nameLast, string& birthDate, string& gradePoint){
	ifstream input(file);
	string str, temp1, temp2, temp3, temp4, temp5, arraySize[5];
	int count = 0, incr = 0;
	getLineNumber(file, count);
	while(getline(input, str)){
		arraySize[incr] = str;
		incr++;
	}

	for(int i = 0; i < count; i++){
		if(arraySize[i] == "id"){
			temp1 = arraySize[i];
		} else if (arraySize[i] == "first"){
			temp2 = arraySize[i];
		} else if (arraySize[i] == "last"){
			temp3 = arraySize[i];
		} else if (arraySize[i] == "DOB"){
			temp4 = arraySize[i];
		} else if (arraySize[i] == "gpa"){
			temp5 = arraySize[i];
		} else {
			cout << "ERROR" << endl;
			exit(0);
		}
	}
	idNumber = temp1, nameFirst = temp2, nameLast = temp3, birthDate = temp4, gradePoint = temp5;

	return idNumber, nameFirst, nameLast, birthDate, gradePoint;

}
void sort(node *head, string attribute1, string attribute2, string attribute3, string attribute4, string attribute5){
	int precedence = 0;
	if(attribute1 == "id"){
		precedence = 1;
	}
	if (attribute2 == "first"){
		precedence = 2;
	}
	if (attribute3 == "last"){
		precedence = 3;
	}
	if (attribute4 == "DOB"){
		precedence = 4;
	}
	if (attribute5 == "GPA"){
		precedence = 5;
	}

	//cout << "precedence: " << precedence << endl;

	if(precedence == 5){
		goto GPA;
	} else if (precedence == 4){
		goto DOB;
	} else if (precedence == 3){
		goto Last;
	} else if (precedence == 2){
		goto First;
	} else if (precedence == 1){
		goto ID;
	}

	ID:
	if(attribute1 == "id"){
		node *first;
		node *second;
		for(first = head; first->next != NULL; first = first->next){
			for(second = first->next; second != NULL; second = second->next){

				string idS1 = first->identificationV, idS2 = second->identificationV;
				//int idI1 = stoi(idS1), idI2 = stoi(idS2);
				//cout << "idS1: " << idS1 << " idS2: " << idS2 << endl;
				//cout << "idI1: " << idI1 << " idI2: " << idI2 << endl;

				if(idS1 > idS2){
					string tempID = first->identificationV;
					string tempfName = first->fNameV;
					string templName = first->lNameV;
					string tempDOB = first->dobV;
					string tempGPA = first->gpaV;

					first->identificationV = second->identificationV;
					first->fNameV = second->fNameV;
					first->lNameV = second->lNameV;
					first->dobV = second->dobV;
					first->gpaV = second->gpaV;

					second->identificationV = tempID;
					second->fNameV = tempfName;
					second->lNameV = templName;
					second->dobV = tempDOB;
					second->gpaV = tempGPA;
				} else if(idS1 == idS2){
					if(first->identificationV == second->identificationV && first->fNameV == second->fNameV && first->lNameV == second->lNameV && first->dobV == second->dobV && first->gpaV == second->gpaV){
						second->fNameV = "";
					}
				}

			}
		}
		goto leave;
	}

	First:
	if(attribute2 == "first"){
		node *first;
		node *second;
		for(first = head; first->next != NULL; first = first->next){
			for(second = first->next; second != NULL; second = second->next){

				string idS1 = first->fNameV, idS2 = second->fNameV;
				if(idS1 > idS2){
					string tempID = first->identificationV;
					string tempfName = first->fNameV;
					string templName = first->lNameV;
					string tempDOB = first->dobV;
					string tempGPA = first->gpaV;

					first->identificationV = second->identificationV;
					first->fNameV = second->fNameV;
					first->lNameV = second->lNameV;
					first->dobV = second->dobV;
					first->gpaV = second->gpaV;

					second->identificationV = tempID;
					second->fNameV = tempfName;
					second->lNameV = templName;
					second->dobV = tempDOB;
					second->gpaV = tempGPA;
				} else if(idS1 == idS2){
					if(first->identificationV == second->identificationV && first->fNameV == second->fNameV && first->lNameV == second->lNameV && first->dobV == second->dobV && first->gpaV == second->gpaV){
						second->fNameV = "";
					}
				}

			}
		}
		goto leave;
	}

	Last:
	if(attribute3 == "last"){
		node *first;
		node *second;
		for(first = head; first->next != NULL; first = first->next){
			for(second = first->next; second != NULL; second = second->next){

				string idS1 = first->lNameV, idS2 = second->lNameV;
				if(idS1 > idS2){
					string tempID = first->identificationV;
					string tempfName = first->fNameV;
					string templName = first->lNameV;
					string tempDOB = first->dobV;
					string tempGPA = first->gpaV;

					first->identificationV = second->identificationV;
					first->fNameV = second->fNameV;
					first->lNameV = second->lNameV;
					first->dobV = second->dobV;
					first->gpaV = second->gpaV;

					second->identificationV = tempID;
					second->fNameV = tempfName;
					second->lNameV = templName;
					second->dobV = tempDOB;
					second->gpaV = tempGPA;
				} else if(idS1 == idS2){
					if(first->identificationV == second->identificationV && first->fNameV == second->fNameV && first->lNameV == second->lNameV && first->dobV == second->dobV && first->gpaV == second->gpaV){
						second->fNameV = "";
					}
				}

			}
		}
		goto leave;
	}

	DOB:
	if(attribute4 == "DOB"){
		node *first;
		node *second;
		for(first = head; first->next != NULL; first = first->next){
			for(second = first->next; second != NULL; second = second->next){
				string idS1 = first->dobV, idS2 = second->dobV;
				//cout << idS1 << " " << idS2 << endl;
				if(idS1 > idS2){
					string tempID = first->identificationV;
					string tempfName = first->fNameV;
					string templName = first->lNameV;
					string tempDOB = first->dobV;
					string tempGPA = first->gpaV;

					first->identificationV = second->identificationV;
					first->fNameV = second->fNameV;
					first->lNameV = second->lNameV;
					first->dobV = second->dobV;
					first->gpaV = second->gpaV;

					second->identificationV = tempID;
					second->fNameV = tempfName;
					second->lNameV = templName;
					second->dobV = tempDOB;
					second->gpaV = tempGPA;
				} else if(idS1 == idS2){
					if(first->identificationV == second->identificationV && first->fNameV == second->fNameV && first->lNameV == second->lNameV && first->dobV == second->dobV && first->gpaV == second->gpaV){
						second->fNameV = "";
					}
				}
			}
		}
		goto leave;
	}

	GPA:
	if(attribute3 == "GPA"){
		node *first;
		node *second;
		for(first = head; first->next != NULL; first = first->next){
			for(second = first->next; second != NULL; second = second->next){

				string idS1 = first->gpaV, idS2 = second->gpaV;
				double idD1 = stod(idS1), idD2 = stod(idS2);
				if(idD1 > idD2){
					string tempID = first->identificationV;
					string tempfName = first->fNameV;
					string templName = first->lNameV;
					string tempDOB = first->dobV;
					string tempGPA = first->gpaV;

					first->identificationV = second->identificationV;
					first->fNameV = second->fNameV;
					first->lNameV = second->lNameV;
					first->dobV = second->dobV;
					first->gpaV = second->gpaV;

					second->identificationV = tempID;
					second->fNameV = tempfName;
					second->lNameV = templName;
					second->dobV = tempDOB;
					second->gpaV = tempGPA;
				} else if(idS1 == idS2){
					if(first->identificationV == second->identificationV && first->fNameV == second->fNameV && first->lNameV == second->lNameV && first->dobV == second->dobV && first->gpaV == second->gpaV){
						second->fNameV = "";
					}
				}

			}
		}
		goto leave;
	}
	leave:
	if(attribute1 == "" || attribute2 == "" || attribute3 == "" || attribute4 == "" || attribute5 == "" ){
		//cout << "No Attribute" << endl;
	} else {
		cout << "Error: Delete attribute not available!" << endl;
	}
}