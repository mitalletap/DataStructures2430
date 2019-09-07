//============================================================================
// Name        : cpp.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================






// OVERVIEW

//============================//
// What does this program do? //
//============================//

// This program takes in an XMP file (metadata file) for a photo and allows you to make edits on the image based on certain parameters

//=======================================================//
// What does it implement from what we learned in class? //
//=======================================================//

// The concepts that this program implements from the course are:


//========================//
// Outline of the program //
//========================//

// PART 1: READING THE INPUT FILE
// The first part of this program reads the input file
// There are 2 conditions it must meet to proceed to the rest of the program
// 1. Must have the extension of ".xmp"
// 2. Must not be a corrupted file


// PART 2: PARSING THE DATA FROM THE FILE
// The file contains many lines, however, the data we need begins with "crs:"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>
using namespace std;

#define DEFAULT_VALUE 0

struct attributeLine {
	string attribute;
	double value;
	attributeLine *next;
	attributeLine *prev;
} *head;

class DLL {
    public:
        void createList(string att, int val);
        void addValue(string att, int val);
        void resetValue(string att);
        void editValue(string att);
        bool searchValue(string att);
        void displayDLL();
        void writeToFile(string input, string output, int numOfLines);
        void sort();
        DLL(){
            head = NULL;
        }
};

void menu(DLL list1, string input, string outputFile, int numOfLines);
string menu2();

void DLL::createList(string att, int val){
	attributeLine *h, *temp;
	temp = new attributeLine;
	temp->attribute = att;
	temp->value = val;
	if(head == NULL){
		temp->prev = NULL;
		head = temp;
	} else {
		h = head;
		while(h->next != NULL){
			h = h->next;
		}
		h->next = temp;
		temp->prev = h;
	}
	cout << "List Created!" << endl;
}

void DLL::addValue(string att, int val){
    if (head == NULL){
        createList(att, val);
        return;
    } else {
		struct attributeLine *temp;
		temp = new attributeLine;
		temp->prev = NULL;
		temp->attribute = att;
		temp->value = val;
		temp->next = head;
		head->prev = temp;
		head = temp;
    }
}

void DLL::resetValue(string att){
	attributeLine *curr = head;
	while(curr != NULL){
		if(curr->attribute == att){
			curr->value = 0;
			curr = curr->next;
		} else {
			curr = curr->next;
		}
	}
	cout << "Value has been reset!" << endl;
}

void DLL::editValue(string att){
	attributeLine *curr = head;
	double newValue = 0;
	cout << "Enter A New Value:" << endl;
	cin >> newValue;
	if(newValue > -101 && newValue < 101){
		while(curr != NULL){
			if(curr->attribute == att){
				curr->value = newValue;
				curr = curr->next;
			} else {
				curr = curr->next;
			}
		}
		cout << "Value Updated!" << endl;
		cout << endl;
	} else {
		cout << "Error: Please Enter A Value Between -100 & 100" << endl;
		cout << endl;
	}

}

bool DLL::searchValue(string att){
	attributeLine *curr = head;
	while(curr != NULL){
		if(curr->attribute == att){
			return true;
		} else {
			curr = curr->next;
		}
	}
	return false;

}

void DLL::displayDLL(){
	cout << "===================" << endl;
	attributeLine *h = head;
	while(h != NULL){
		cout << h->attribute << endl;
		cout << h->value << endl;
		cout << endl;
		h = h->next;
	}
	cout << "===================" << endl;
}

void removeDelimiters(string &temp){
	replace(temp.begin(), temp.end(), ':', ' ');
	replace(temp.begin(), temp.end(), '=', ' ');
	replace(temp.begin(), temp.end(), '>', ' ');
	replace(temp.begin(), temp.end(), '"', ' ');
}

bool isValue(string str){
	if(str == "Exposure2012" || str == "Saturation" || str == "Contrast2012" || str == "Tint" || str == "Sharpness" || str == "VignetteAmount" || str == "Vibrance"){
		return true;
	} else {
		return false;
	}
}

void DLL::writeToFile(string input, string output, int numOfLines){
	ifstream inputFile(input);
	ofstream outputFile(output);
	string str, att, id, type;
	attributeLine *curr = head;

	for(int i = 0; i < numOfLines; i++){
		getline(inputFile, str);
		string temp1 = str;
		temp1.erase(remove(temp1.begin(), temp1.end(), ' '), temp1.end());
		string front = temp1.substr(0,9);
		if(front == "dc:format"){
			string temp = str;
			outputFile << temp << endl;
			attributeLine *h = head;
			while(h != NULL){
				outputFile << "   crs:" << h->attribute << "==" << '"'<< h->value << '"' << endl;
				h = h->next;
			}


		} else {
			outputFile << str << endl;
			//cout << str << endl;
		}
	}





	cout << "Saving..." << endl;
	cout << "Saved! Goodbye!" << endl;
}

bool isXMP(string input){
	int size = input.length();
	string fileExtension = input.substr(size-4, size);
	return (fileExtension == ".xmp");
}

void getLineNumber(string input, int& numOfLines){
	ifstream inputFile(input);
	string str;
	while(!inputFile.eof()){
		getline(inputFile, str);
		numOfLines++;
	}
}

void menu(DLL list1, string input, string output, int numOfLines){
	cout << "Select an option: " << endl;
	cout << "1. View Current List" << endl;
	cout << "2. Edit List Value" << endl;
	cout << "3. Reset List Value" << endl;
	cout << "4. Save and Exit" << endl;
	int selection;
	cin >> selection;
	cout << endl;
	string sel;
	switch(selection) {
		case 1:
			list1.displayDLL();
			menu(list1, input, output, numOfLines);
			break;
		case 2:
			sel = menu2();
			if(list1.searchValue(sel)){
				list1.editValue(sel);
			} else {
				cout << "Value is set to default" << endl;
				list1.editValue(sel);
			}
			menu(list1, input, output, numOfLines);
			break;
		case 3:
			sel = menu2();
			list1.resetValue(sel);
			menu(list1, input, output, numOfLines);
			break;
		case 4:
			list1.writeToFile(input, output, numOfLines);
			//exit(0);
	}
}

string menu2(){
	cout << "Select an option: " << endl;
	cout << "1. Contrast" << endl;
	cout << "2. Exposure" << endl;
	cout << "3. Vibrance" << endl;
	cout << "4. Vignette" << endl;
	cout << "5. Sharpness" << endl;
	cout << "6. Saturation" << endl;
	cout << "7. Tint" << endl;
	int value;
	string selection;
	cin >> value;
	if(0 < value && value < 8){
		switch(value){
			case 1:
				selection = "Contrast2012";
				break;
			case 2:
				selection = "Exposure2012";
				break;
			case 3:
				selection = "Vibrance";
				break;
			case 4:
				selection = "VignetteAmount";
				break;
			case 5:
				selection = "Sharpness";
				break;
			case 6:
				selection = "Saturation";
				break;
			case 7:
				selection = "Tint";
				break;
		}
	} else {
		cout << "Please select again!" << endl;
		menu2();
	}

	return selection;
}

bool hasExistingParameters(string input, int numOfLines){
	ifstream inputFile(input);
	string str;
	int count1 = 0, count2 = 0, temp1 = 0, temp2 = 0;
	for(int i = 0; i < numOfLines; i++){
		getline(inputFile, str);
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		if(str.substr(0,11) == "crs:RawFile"){
			temp1 = count1;
		} else if(str.substr(0,11) == "crs:Version"){
			temp2 = count2;
		}
		count1++;
		count2++;
	}
	if(temp1 > temp2 && temp2 != 0){
		return true;
	} else {
		return false;
	}
}

void readDefaultXMPFile(DLL list1, string xmpFile){
	string temp, type, attribute, id;
	removeDelimiters(temp);
	stringstream ss(temp);
	temp.erase(temp.begin(), temp.begin()+4);
	while(ss >> type >> attribute >> id){
		if(isValue(attribute)){
			double x = stod(id);
			list1.addValue(attribute, x);
		}
	}
}

int main() {

	DLL list1, list2;
	string userInput;
	cout << "Enter the file name (EXCLUDNG extension): " << endl;
	cin >> userInput;
	string input1 = userInput + ".xmp", output1 = userInput + "_output.txt", str, xmpFile = "default.xmp";
	ifstream inputFile(input1);
	int numOfLines = 0;
	string attributes[7] = {"Tint", "Saturation", "Sharpness", "VignetteAmount", "Vibrance", "Exposure2012", "Contrast2012"};

	if(inputFile.good() && isXMP(input1)){
		cout << "File Opened Successfully!" << endl;
	} else if(!isXMP(input1)){
		cout << "Error: File Must Have An XMP File Extension!" << endl;
		cout << "Exiting Program..." << endl;
		exit(0);
	} else {
		cout << "Error: File Could Not Be Opened!" << endl;
		cout << "Exiting Program..." << endl;
		exit(0);
	}



	getLineNumber(input1, numOfLines);


	int cnt = 0;
	string type, attribute, id;
	for(int i = 0; i < numOfLines; i++){
	getline(inputFile, str);
	string temp = str;
	temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
	string front = temp.substr(0,4);
	string line = temp.substr(0,11);
	if(front == "crs:"){
			string temp1 = str;
			removeDelimiters(temp1);
			stringstream ss(temp1);
			temp1.erase(temp1.begin(), temp1.begin()+4);
			while(ss >> type >> attribute >> id){
				if(isValue(attribute)){
					double x = stod(id);
					list1.addValue(attribute, x);
				}
			}
			cnt++;
		}
	}

	menu(list1, input1, output1, numOfLines);



//		for(int i = 0; i < 7; i++){
//			list1.addValue(attributes[i], 0);
//		}

		//menu(list1, input1, output1, numOfLines);

}






























































































/*
V2
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>
#include <iterator>

using namespace std;

#define DEFAULT_VALUE 0

struct attributeLine {
	string attribute;
	double value;
	attributeLine *next;
	attributeLine *prev;
} *head;

class DLL {
    public:
        void createList(string att, int val);
        void addValue(string att, int val);
        void resetValue(string att);
        void editValue(string att);
        bool searchValue(string att);
        void displayDLL();
        void writeToFile(string input, string output, int numOfLines);
        DLL(){
            head = NULL;
        }
};

void menu(DLL list1, string input, string outputFile, int numOfLines);
string menu2();

void DLL::createList(string att, int val){
	attributeLine *h, *temp;
	temp = new attributeLine;
	temp->attribute = att;
	temp->value = val;
	if(head == NULL){
		temp->prev = NULL;
		head = temp;
	} else {
		h = head;
		while(h->next != NULL){
			h = h->next;
		}
		h->next = temp;
		temp->prev = h;
	}
	cout << "List Created!" << endl;
}

void DLL::addValue(string att, int val){
    if (head == NULL){
        createList(att, val);
        return;
    } else {
		struct attributeLine *temp;
		temp = new attributeLine;
		temp->prev = NULL;
		temp->attribute = att;
		temp->value = val;
		temp->next = head;
		head->prev = temp;
		head = temp;
    }
}

void DLL::resetValue(string att){
	attributeLine *curr = head;
	while(curr != NULL){
		if(curr->attribute == att){
			curr->value = 0;
			curr = curr->next;
		} else {
			curr = curr->next;
		}
	}
	cout << "Value has been reset!" << endl;
}

void DLL::editValue(string att){
	attributeLine *curr = head;
	double newValue = 0;
	cout << "Enter A New Value:" << endl;
	cin >> newValue;
	if(newValue > -101 && newValue < 101){
		while(curr != NULL){
			if(curr->attribute == att){
				curr->value = newValue;
				curr = curr->next;
			} else {
				curr = curr->next;
			}
		}
		cout << "Value Updated!" << endl;
		cout << endl;
	} else {
		cout << "Error: Please Enter A Value Between -100 & 100" << endl;
		cout << endl;
	}

}

bool DLL::searchValue(string att){
	attributeLine *curr = head;
	while(curr != NULL){
		if(curr->attribute == att){
			return true;
		} else {
			curr = curr->next;
		}
	}
	return false;

}

void DLL::displayDLL(){
	attributeLine *h = head;
	if(h == NULL){
		cout << "Values Are Defaulted!" << endl;
		cout << endl;
	} else {
		cout << "===================" << endl;
		while(h != NULL){
			cout << h->attribute << endl;
			cout << h->value << endl;
			cout << endl;
			h = h->next;
		}
		cout << "===================" << endl;
	}
}


void removeDelimiters(string &temp){
//	int size = temp.length();
//	for(int i = 0; i < size; i++){
//		if(temp[i] == 34){
//			cout << temp[i] << endl;
//		}
//	}
	replace(temp.begin(), temp.end(), ':', ' ');
	replace(temp.begin(), temp.end(), '=', ' ');
	replace(temp.begin(), temp.end(), '>', ' ');
	replace(temp.begin(), temp.end(), '"', ' ');
}

bool isValue(string str){
	if(str == "Exposure2012" || str == "Saturation" || str == "Contrast2012" || str == "Tint" || str == "Sharpness" || str == "VignetteAmount" || str == "Vibrance"){
		return true;
	} else {
		return false;
	}
}

void DLL::writeToFile(string input, string output, int numOfLines){
	ifstream inputFile(input);
	ofstream outputFile(output);
	string str, att, id, type;
	attributeLine *curr = head;

	for(int i = 0; i < numOfLines; i++){
		getline(inputFile, str);
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		string front = str.substr(0,4);
		if(front == "dc:f" && head == NULL){
			cout << str << endl;
			while(curr != NULL){
				str = "";
				outputFile << "crs:" << curr->attribute << "=" << '"'<< curr->value << '"' << endl;
				curr = curr->next;
			}
		}
		if(front == "crs:"){
			string temp = str;
			removeDelimiters(temp);
			temp.erase(temp.begin(), temp.begin()+4);
			stringstream ss(temp);
			while(ss >> att >> id){
				if(isValue(att)){
					str = "";
					outputFile << "crs:" << curr->attribute << "=" << '"'<< curr->value << '"' << endl;
					curr = curr->next;
				} else {
					outputFile << "crs:" << att << "=" << '"'<< id << '"' << endl;
				}

			}
		} else {
			outputFile << str << endl;
		}
	}
	inputFile.close();
	outputFile.close();

//	ifstream newIn(output);
//	fstream outputCorrect(input, ios::out);
//	str = "";
//	for(int i = 0; i < numOfLines; i++){
//		getline(newIn, str);
//		outputCorrect << str << endl;
//	}






	cout << "Saving..." << endl;
	cout << "Saved! Goodbye!" << endl;
}

bool isXMP(string input){
	int size = input.length();
	string fileExtension = input.substr(size-4, size);
	return (fileExtension == ".xmp");
}

void getLineNumber(string input, int& numOfLines){
	ifstream inputFile(input);
	string str;
	while(!inputFile.eof()){
		getline(inputFile, str);
		numOfLines++;
	}
}

void menu(DLL list1, string input, string output, int numOfLines){
	cout << "Select an option: " << endl;
	cout << "1. View Current List" << endl;
	cout << "2. Edit List Value" << endl;
	cout << "3. Reset List Value" << endl;
	cout << "4. Save and Exit" << endl;
	int selection;
	cin >> selection;
	cout << endl;
	string sel;
	switch(selection) {
		case 1:
			list1.displayDLL();
			menu(list1, input, output, numOfLines);
			break;
		case 2:
			sel = menu2();
			if(list1.searchValue(sel)){
				list1.editValue(sel);
			} else {
				cout << "Value is set to default" << endl;
				list1.editValue(sel);
			}
			menu(list1, input, output, numOfLines);
			break;
		case 3:
			sel = menu2();
			list1.resetValue(sel);
			menu(list1, input, output, numOfLines);
			break;
		case 4:
			list1.writeToFile(input, output, numOfLines);
			//exit(0);
	}
}

string menu2(){
	cout << "Select an option: " << endl;
	cout << "1. Contrast" << endl;
	cout << "2. Exposure" << endl;
	cout << "3. Vibrance" << endl;
	cout << "4. Vignette" << endl;
	cout << "5. Sharpness" << endl;
	cout << "6. Saturation" << endl;
	cout << "7. Tint" << endl;
	int value;
	string selection;
	cin >> value;
	if(0 < value && value < 8){
		switch(value){
			case 1:
				selection = "Contrast2012";
				break;
			case 2:
				selection = "Exposure2012";
				break;
			case 3:
				selection = "Vibrance";
				break;
			case 4:
				selection = "VignetteAmount";
				break;
			case 5:
				selection = "Sharpness";
				break;
			case 6:
				selection = "Saturation";
				break;
			case 7:
				selection = "Tint";
				break;
		}
	} else {
		cout << "Please select again!" << endl;
		menu2();
	}

	return selection;
}

int main() {

	DLL list1, list2;
	string input1 = "DSC04008.xmp", input2 = "DSC04027.xmp", output1 = "DSC04008_output.xmp", output2 = "DSC04027_output.xmp", str;
	ifstream inputFile(input1);
	int numOfLines = 0;

	if(inputFile.good() && isXMP(input1)){
		cout << "File Opened Successfully!" << endl;
	} else if(!isXMP(input1)){
		cout << "Error: File Must Have An XMP File Extension!" << endl;
		cout << "Exiting Program..." << endl;
		exit(0);
	} else {
		cout << "Error: File Could Not Be Opened!" << endl;
		cout << "Exiting Program..." << endl;
		exit(0);
	}



	getLineNumber(input1, numOfLines);

	int cnt = 0;
	string type, attribute, id;
	for(int i = 0; i < numOfLines; i++){
		getline(inputFile, str);
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		string front = str.substr(0,4);
		string line = str.substr(0,15);
		if(front == "crs:"){
			if(line == "crs:RawFileName"){
				list1.addValue("Tint", DEFAULT_VALUE);
				list1.addValue("Saturation", DEFAULT_VALUE);
				list1.addValue("Sharpness", DEFAULT_VALUE);
				list1.addValue("VignetteAmount", DEFAULT_VALUE);
				list1.addValue("Vibrance", DEFAULT_VALUE);
				list1.addValue("Exposure2012", DEFAULT_VALUE);
				list1.addValue("Contrast2012", DEFAULT_VALUE);
			} else {
				string temp = str;
				removeDelimiters(temp);
				stringstream ss(temp);
				temp.erase(temp.begin(), temp.begin()+4);
				while(ss >> type >> attribute >> id){
					if(isValue(attribute)){
						double x = stod(id);
						list1.addValue(attribute, x);
					}
				}
				cnt++;
			}
		}
	}
	menu(list1, input1, output1, numOfLines);





















}
 *
 */
















































































































































































































































































/*
 * //============================================================================
// Name        : cpp.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================






// OVERVIEW

//============================//
// What does this program do? //
//============================//

// This program takes in an XMP file (metadata file) for a photo and allows you to make edits on the image based on certain parameters

//=======================================================//
// What does it implement from what we learned in class? //
//=======================================================//

// The concepts that this program implements from the course are:


//========================//
// Outline of the program //
//========================//

// PART 1: READING THE INPUT FILE
// The first part of this program reads the input file
// There are 2 conditions it must meet to proceed to the rest of the program
// 1. Must have the extension of ".xmp"
// 2. Must not be a corrupted file


// PART 2: PARSING THE DATA FROM THE FILE
// The file contains many lines, however, the data we need begins with "crs:"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>
using namespace std;



struct attributeLine {
	string attribute;
	double value;
	attributeLine *next;
	attributeLine *prev;
} *head;

class DLL {
    public:
        void createList(string att, int val);
        void addValue(string att, int val);
        void resetValue(string att);
        void editValue(string att);
        bool searchValue(string att);
        void displayDLL();
        void writeToFile(string input, string output, int numOfLines);
        void sort();
        DLL(){
            head = NULL;
        }
};

void menu(DLL list1, string input, string outputFile, int numOfLines);
string menu2();

void DLL::createList(string att, int val){
	attributeLine *h, *temp;
	temp = new attributeLine;
	temp->attribute = att;
	temp->value = val;
	if(head == NULL){
		temp->prev = NULL;
		head = temp;
	} else {
		h = head;
		while(h->next != NULL){
			h = h->next;
		}
		h->next = temp;
		temp->prev = h;
	}
	cout << "List Created!" << endl;
}

void DLL::addValue(string att, int val){
    if (head == NULL){
        createList(att, val);
        return;
    } else {
		struct attributeLine *temp;
		temp = new attributeLine;
		temp->prev = NULL;
		temp->attribute = att;
		temp->value = val;
		temp->next = head;
		head->prev = temp;
		head = temp;
    }
}

void DLL::resetValue(string att){
	attributeLine *curr = head;
	while(curr != NULL){
		if(curr->attribute == att){
			curr->value = 0;
			curr = curr->next;
		} else {
			curr = curr->next;
		}
	}
	cout << "Value has been reset!" << endl;
}

void DLL::editValue(string att){
	attributeLine *curr = head;
	double newValue = 0;
	cout << "Enter A New Value:" << endl;
	cin >> newValue;
	if(newValue > -101 && newValue < 101){
		while(curr != NULL){
			if(curr->attribute == att){
				curr->value = newValue;
				curr = curr->next;
			} else {
				curr = curr->next;
			}
		}
		cout << "Value Updated!" << endl;
		cout << endl;
	} else {
		cout << "Error: Please Enter A Value Between -100 & 100" << endl;
		cout << endl;
	}

}

bool DLL::searchValue(string att){
	attributeLine *curr = head;
	while(curr != NULL){
		if(curr->attribute == att){
			return true;
		} else {
			curr = curr->next;
		}
	}
	return false;

}

void DLL::displayDLL(){
	cout << "===================" << endl;
	attributeLine *h = head;
	while(h != NULL){
		cout << h->attribute << endl;
		cout << h->value << endl;
		cout << endl;
		h = h->next;
	}
	cout << "===================" << endl;
}

void removeDelimiters(string &temp){
//	int size = temp.length();
//	for(int i = 0; i < size; i++){
//		if(temp[i] == 34){
//			cout << temp[i] << endl;
//		}
//	}
	replace(temp.begin(), temp.end(), ':', ' ');
	replace(temp.begin(), temp.end(), '=', ' ');
	replace(temp.begin(), temp.end(), '>', ' ');
	replace(temp.begin(), temp.end(), '"', ' ');
}

bool isValue(string str){
	if(str == "Exposure2012" || str == "Saturation" || str == "Contrast2012" || str == "Tint" || str == "Sharpness" || str == "VignetteAmount" || str == "Vibrance"){
		return true;
	} else {
		return false;
	}
}

void DLL::writeToFile(string input, string output, int numOfLines){
	ifstream inputFile(input);
	ofstream outputFile(output);
	string str, att, id, type;
	attributeLine *curr = head;

	for(int i = 0; i < numOfLines; i++){
		getline(inputFile, str);
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		string front = str.substr(0,4);
		if(front == "crs:"){
			string temp = str;
			removeDelimiters(temp);
			temp.erase(temp.begin(), temp.begin()+4);
			stringstream ss(temp);
			while(ss >> att >> id){
				if(isValue(att)){
					str = "";
					outputFile << "crs:" << curr->attribute << "=" << '"'<< curr->value << '"' << endl;
					curr = curr->next;
				} else {
					outputFile << "crs:" << att << "=" << '"'<< id << '"' << endl;
				}

			}
		} else {
			outputFile << str << endl;
		}
	}





	cout << "Saving..." << endl;
	cout << "Saved! Goodbye!" << endl;
}

bool isXMP(string input){
	int size = input.length();
	string fileExtension = input.substr(size-4, size);
	return (fileExtension == ".xmp");
}

void getLineNumber(string input, int& numOfLines){
	ifstream inputFile(input);
	string str;
	while(!inputFile.eof()){
		getline(inputFile, str);
		numOfLines++;
	}
}

void menu(DLL list1, string input, string output, int numOfLines){
	cout << "Select an option: " << endl;
	cout << "1. View Current List" << endl;
	cout << "2. Edit List Value" << endl;
	cout << "3. Reset List Value" << endl;
	cout << "4. Save and Exit" << endl;
	int selection;
	cin >> selection;
	cout << endl;
	string sel;
	switch(selection) {
		case 1:
			list1.displayDLL();
			menu(list1, input, output, numOfLines);
			break;
		case 2:
			sel = menu2();
			if(list1.searchValue(sel)){
				list1.editValue(sel);
			} else {
				cout << "Value is set to default" << endl;
			}
			menu(list1, input, output, numOfLines);
			break;
		case 3:
			sel = menu2();
			list1.resetValue(sel);
			menu(list1, input, output, numOfLines);
			break;
		case 4:
			list1.writeToFile(input, output, numOfLines);
			//exit(0);
	}
}

string menu2(){
	cout << "Select an option: " << endl;
	cout << "1. Contrast" << endl;
	cout << "2. Exposure" << endl;
	cout << "3. Vibrance" << endl;
	cout << "4. Vignette" << endl;
	cout << "5. Sharpness" << endl;
	cout << "6. Saturation" << endl;
	cout << "7. Tint" << endl;
	int value;
	string selection;
	cin >> value;
	if(0 < value && value < 8){
		switch(value){
			case 1:
				selection = "Contrast2012";
				break;
			case 2:
				selection = "Exposure2012";
				break;
			case 3:
				selection = "Vibrance";
				break;
			case 4:
				selection = "VignetteAmount";
				break;
			case 5:
				selection = "Sharpness";
				break;
			case 6:
				selection = "Saturation";
				break;
			case 7:
				selection = "Tint";
				break;
		}
	} else {
		cout << "Please select again!" << endl;
		menu2();
	}

	return selection;
}

int main() {

	DLL list1, list2;
	string input1 = "DSC04008.xmp", input2 = "DSC04027.xmp", output1 = "DSC04008_output.xmp", output2 = "DSC04027_output.xmp", str;
	ifstream inputFile(input1);
	int numOfLines = 0;

	if(inputFile.good() && isXMP(input1)){
		cout << "File Opened Successfully!" << endl;
	} else if(!isXMP(input1)){
		cout << "Error: File Must Have An XMP File Extension!" << endl;
		cout << "Exiting Program..." << endl;
		exit(0);
	} else {
		cout << "Error: File Could Not Be Opened!" << endl;
		cout << "Exiting Program..." << endl;
		exit(0);
	}



	getLineNumber(input1, numOfLines);

	int cnt = 0;
	string type, attribute, id;
	for(int i = 0; i < numOfLines; i++){
		getline(inputFile, str);
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		string front = str.substr(0,4);
		if(front == "crs:"){
			string temp = str;
			removeDelimiters(temp);
			stringstream ss(temp);
			temp.erase(temp.begin(), temp.begin()+4);
			while(ss >> type >> attribute >> id){
				if(isValue(attribute)){
					double x = stod(id);
					list1.addValue(attribute, x);
				}
			}
			cnt++;
		}
	}
	menu(list1, input1, output1, numOfLines);





















}
 *
 */
