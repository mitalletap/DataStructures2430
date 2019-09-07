//============================================================================
// Name        : extra2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// Received help for cplusplus.com


#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;


void checkDay(string d, int& day);
bool isNumber(string s);
bool isWeekday(string d);

class dayType {
private:
	string weekDay;
	//string weekDays[7];
	int day;
	//friend ostream &operator<<(ostream&, const dayType&){	}
public:
	string weekDays[7] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};
	dayType();
	dayType(string d);
	void setDay(string d);
	string getDay() const;
	void print() const;
	void nextDay() const;
	void prevDay() const;
	void addDays(int nDays);
};

dayType::dayType(){
	weekDay = "Sunday";
	day = 0;
}

dayType::dayType(string d){
	weekDay = d;
	checkDay(d, day);
}

void dayType::setDay(string d){
	weekDay = d;
}

string dayType::getDay() const{
	return weekDay;
}

void dayType::print() const{
	cout << "The weekday is: " << weekDay <<  "." << endl;
	//cout << "The day is: " << day <<  "." << endl;

}

void dayType::nextDay() const{
	if(day == 6){
		cout << "The next day is " << weekDays[0] << "." << endl;
	} else {
		 cout << "The next day is " << weekDays[day + 1] << "." << endl;
	}
}

void dayType::prevDay() const{
	string current;
	if(day == 0){
		cout << "The previous day is " << weekDays[6] << "." << endl;
	} else {
		cout << "The previous day is " << weekDays[day-1] << "." << endl;
	}
}

void dayType::addDays(int nDays){
	int finalDay = day + nDays;
	int weekdayFinal = finalDay % 7;
	cout <<  weekDays[weekdayFinal] << endl;
}




int main() {

	// Clock Initalization
	clock_t start, end;
	start = clock();
	double cpu_time;
	locale loc;
	bool success = false;
	string dayIn, temp;
	int selection, teleport;

	cout << "Welcome To The Program!" << endl;

	ChooseDay:
	cout << "Enter the day today: " << endl;
	cin >> dayIn;
	for(string::size_type i = 0; i < dayIn.length(); ++i){
		temp += toupper(dayIn[i], loc);
	}
	dayIn = temp;
	temp = " ";
	//cout << "DayIn: " << dayIn << endl;
	if(!isWeekday(dayIn)){
		cout << "Dont enter the DATE! Enter the DAY!" << endl;
		goto ChooseDay;
	}
	dayType myDay1(dayIn);



	FirstMenu:
	cout << "Choose an option!" << endl;
	cout << "1. View the current day" << endl;
	cout << "2. View the next day" << endl;
	cout << "3. View the previous day" << endl;
	cout << "4. View a day in the past or future" << endl;
	cout << "5. Choose another day" << endl;
	cout << "6. Exit" << endl;
	cout << "------------------------------" << endl;
	cin >> selection;

	if(0 < selection <= 6){
		goto Switch;
	} else {
		cout << "You didnt enter a number between 1-6!" << endl;
		goto FirstMenu;
	}


	Switch:
	switch(selection){
	case 1:
		temp = myDay1.getDay();
		cout << "The current day is: " << temp << "." << endl;
		cout << endl;
		temp = " ";
		goto FirstMenu;
		break;
	case 2:
		myDay1.nextDay();
		cout << endl;
		goto FirstMenu;
		break;
	case 3:
		myDay1.prevDay();
		cout << endl;
		goto FirstMenu;
		break;
	case 4:
		cout << "How many days forward or backwards would you like to go?" << endl;
		cin >> teleport;
		myDay1.addDays(teleport);
		goto FirstMenu;
		break;
	case 5:
		cout << "Choose another day" << endl;
		goto ChooseDay;
		break;
	case 6:
		cout << "Goodbye!" << endl;
		goto End;
		break;
	default:
		cout << "Error: Selection invalid!" << endl;
		goto FirstMenu;
		break;



	}



	/*

	// Code
	dayType myDay("Sunday");
	dayType temp("Friday");


	cout << "myDay.print(): " << endl;
	myDay.print();
	cout << endl;


	cout << "myDay.prevDay(): " << endl;
	myDay.prevDay();
	cout << "myDay.nextDay(): " << endl;
	myDay.nextDay();


	cout << "myDay.addDays(3): " << endl;
	myDay.addDays(3);



	cout << "temp.print(): " << endl;
	temp.print();
	cout << endl;

	cout << "temp.prevDay(): " << endl;
	cout << temp.prevDay() << endl;
	cout << "temp.nextDay(): " << endl;
	cout << temp.nextDay() << endl;

	*/













	End:
	end = clock();
	cpu_time = ((double) (end-start))/CLOCKS_PER_SEC;
	cout << "It took " << cpu_time << " seconds to run the program." << endl;
	return 0;
}



void checkDay(string d, int& day){
	if(d == "SUNDAY"){
		day = 0;
	} else if (d == "MONDAY"){
		day = 1;
	} else if (d == "TUESDAY"){
		day = 2;
	} else if (d == "WEDNESDAY"){
		day = 3;
	} else if (d == "THURSDAY"){
		day = 4;
	} else if (d == "FRIDAY"){
		day = 5;
	} else if (d == "SATURDAY"){
		day = 6;
	} else {
		cout << "Error! You didnt enter a day!" << endl;
		bool success = false;
	}
}

bool isNumber(string s){
	for(int i = 0; i < s.length(); i++){
		if(isdigit(s[0]) == true){
			return true;
		} else {
			return false;
		}
	}
}

bool isWeekday(string d){
	if(d == "SUNDAY" || "MONDAY" || "TUESDAY" || "WEDNESDAY" || "THURSDAY" || "FRIDAY" || "SATURDAY") {
		return true;
	} else {
		return false;
	}
}
