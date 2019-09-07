//============================================================================
// Name        : queueDesign.cpp
// Author      : Mital Patel 33% , Steven Stricklin 33% , Edgar Garza 33%
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// Received help for another group in class. Kevin Huynh



#include <iostream>
#include <queue>
#include <cmath>
#include <ctime>
using namespace std;



class customerType {
private:
	int customerNumber;
	int arrivalTime;
	int waitingTime;
	int transactionTime;
public:
	customerType(int number, int arrivalT, int waitT, int transT){
		setCustomerInfo(number, arrivalT, waitT, transT);
	}

	void setCustomerInfo(int number, int arrivalT, int waitT, int transT){
		customerNumber = number;
		arrivalTime = arrivalT;
		waitingTime = waitT;
		transactionTime = transT;
	}

	void setWaitingTime(int i){
		waitingTime = i;
	}

	int getWaitingTime(){
		return waitingTime;
	}

	int getArrivalTime(){
		return arrivalTime;
	}

	int getTransactionTime(){
		return transactionTime;
	}

	int getCustomerNumber(){
		return customerNumber;
	}

	void incrementWaitingTime(){
		waitingTime++;
	}


};

class serverType {
private:
	customerType *currentCustomer;
	string status;
	int transactionTime;
public:
	serverType(){
		status = "free";
		transactionTime = 0;
	}

	bool isFree() const{
		return (status == "free");
	}

	void setBusy(customerType *curr){
		status = "busy";
		currentCustomer = curr;
	}

	void setFree(){
		status = "free";
		currentCustomer = NULL;
	}

	void setTransactionTime(int t){
		transactionTime = t;
	}

	void setTransactionTime(){
		int time;
		time = currentCustomer->getTransactionTime();
		transactionTime = time;
	}

	int getRemainingTransactionTime(){
		return transactionTime;
	}

	void decreaseTransactionTime(){
		transactionTime--;
	}

	void setCurrentCustomer(customerType *curr){
		currentCustomer = curr;
	}

	int getCurrentCustomerNumber(){
		return currentCustomer->getCustomerNumber();
	}

	int getCurrentCustomerArrivalTime(){
		return (currentCustomer->getArrivalTime());
	}

	int getCurrentCustomerWaitingTime(){
		return (currentCustomer->getWaitingTime());
	}

	int getCurrentCustomerTransactionTime(){
		return (currentCustomer->getTransactionTime());
	}
};

class serverListType {
private:
	int numOfServers;
	serverType *servers;
public:
	serverListType(int num){
		servers = new serverType[num];
		numOfServers = num;
	}

	bool freeServer(int serverID){
		return (servers[serverID].isFree());
	}

	void setServerFree(int serverID){
		servers[serverID].setFree();
	}

	void setServerBusy(int serverID, customerType cCustomer){
		servers[serverID].setBusy(&cCustomer);
	}

	void decreaseTransaction(){
		for(int i = 0; i < numOfServers; i++){
			servers[i].decreaseTransactionTime();
		}
	}

	int getServerTransaction(int serverID){
		return (servers[serverID].getCurrentCustomerTransactionTime());
	}

	int getCustomerNumber(int serverID){
		return (servers[serverID].getCurrentCustomerNumber());
	}

	void printTransaction(){
		for(int i = 0; i < numOfServers; i++){
		}
	}

};

int main() {

	srand(time(NULL));
	int numOfServers = 5;
	queue<customerType> list;
	serverListType servers(numOfServers);
	serverType server;
	int numOfCustomers = 0;


	for(int i = 0; i < 100; i++){

		// Initalize Customer
		int cust = (rand() % 10) + 1;
		if(cust == 1){
			list.push(customerType(++numOfCustomers, i, i, cust));
			cout << "Customer " << numOfCustomers << " has entered the queue at " << i  << " seconds." << endl;
		}


		// Add Customer To Server
		for(int j = 0; j < numOfServers; j++){
			if(servers.freeServer(j) && !list.empty()){
				customerType temp = list.front();
				temp.setWaitingTime(i);
				servers.setServerBusy(j, temp);
				cout << "Server #" << j+1 << " is now serving customer " << temp.getCustomerNumber() << " at " << i << " seconds." << endl;
				list.pop();
			}
		}

		// Decrease Server Size
		servers.decreaseTransaction();



		// Remove Customer From Server
		for(int k = 0; k < numOfServers; k++){
			if(!servers.freeServer(k) && servers.getServerTransaction(k) == 0){
				cout << "Server #" << k+1 << " has finished helping customer " << servers.getCustomerNumber(k) + 1 <<  " at " << i << " seconds." << endl;
				servers.setServerFree(k);
			}
		}







	}




		for (int i = 0; i < 100; i++) {

			servers.decreaseTransaction();
			for (int k = 0; k < numOfServers; k++) {
				if (!servers.freeServer(k) && servers.getServerTransaction(k) == 0) {
					cout << "Server " << k + 1 << " has finished serving customer "
						<< servers.getCustomerNumber(k) + 1 << " at " << i << " seconds." << endl;
					servers.setServerFree(k);

				}
			}
		}


	cout << "Program terminated. Press enter to continue...";
	cin.get();

	return 0;
}














































































/*
 * //============================================================================
// Name        : queueDesign.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// Linked list of servers

#include <iostream>
#include <queue>
#include <cmath>
using namespace std;




////////////////////////////////////////////////////////////////////////
class customerType {
private:
	int customerNumber;
	int arrivalTime;
	int waitingTime;
	int transactionTime;
public:
	customerType(int number, int arrivalT = 0, int waitT = 0, int transT = 0);
	void setCustomerInfo(int number = 0, int arrivalT = 0, int waitT = 0, int transT = 0);
	void setWaitingTime(int);
	int getWaitingTime();
	int getArrivalTime();
	int getTransactionTime();
	int getCustomerNumber();
	void incrementWaitingTime();


};

void customerType::setCustomerInfo(int number, int arrivalT, int waitT, int transT){
	customerNumber = number;
	arrivalTime = arrivalT;
	waitingTime = waitT;
	transactionTime = transT;
}

customerType::customerType(int number, int arrivalT, int waitT, int transT){
	setCustomerInfo(number, arrivalT, waitT, transT);
}

void customerType::setWaitingTime(int tTime){
	waitingTime = tTime;
}

int customerType::getWaitingTime(){
	return waitingTime;
}

int customerType::getArrivalTime(){
	return arrivalTime;
}

int customerType::getTransactionTime(){
	return transactionTime;
}

int customerType::getCustomerNumber(){
	return customerNumber;
}

void customerType::incrementWaitingTime(){
	waitingTime++;
}



////////////////////////////////////////////////////////////////////////
class serverType {
private:
	customerType currentCustomer;
	string status;
	int transactionTime;
public:
	serverType();
	bool isFree();
	void setBusy();
	void setFree();
	void setTransactionTime(int t);
	void setTransactionTime();
	int getRemainingTransactionTime();
	void decreaseTransactionTime();
	void setCurrentCustomer(customerType);
	int getCurrentCustomerNumber();
	int getCurrentCustomerArrivalTime();
	int getCurrentCustomerWaitingTime();
	int getCurrentCustomerTransactionTime();
};

serverType::serverType(){
	status = "free";
	transactionTime = 0;
}

bool serverType::isFree(){
	return(status == "free");
}

void serverType::setBusy(){
	status = "busy";
}

void serverType::setFree(){
	status = "free";
}

void serverType::setTransactionTime(int t){
	transactionTime = t;
}

void serverType::setTransactionTime(){
	int time;
	time = currentCustomer.getTransactionTime();
	transactionTime = time;
}

int serverType::getRemainingTransactionTime(){
	return transactionTime;
}

void serverType::decreaseTransactionTime(){
	transactionTime--;
}

void serverType::setCurrentCustomer(customerType cCustomer){
	currentCustomer = cCustomer;
}

int serverType::getCurrentCustomerNumber(){
	currentCustomer.getCustomerNumber();
}

int serverType::getCurrentCustomerArrivalTime(){
	currentCustomer.getArrivalTime();
}

int serverType::getCurrentCustomerWaitingTime(){
	currentCustomer.getWaitingTime();
}

int serverType::getCurrentCustomerTransactionTime(){
	currentCustomer.getTransactionTime();
}

////////////////////////////////////////////////////////////////////////
class serverListType {
private:
	int numOfServers;
	serverType *servers;
public:
	serverListType(int num);
	~serverListType();
	int getFreeServerID() const;
	int getNumOfBusyServers() const;
	void setServerFree(int serverID);
	void setServerBusy(int serverID, customerType cCustomer);
	void setServerBusy(int serverID, customerType cCustomer, int tTime);
	void updateServers(ostream& outF);
};

serverListType::serverListType(int num){
	numOfServers = num;
	servers = new serverType[num];
}

serverListType::~serverListType(){
	delete [] servers;
}

int serverListType::getFreeServerID() const{
	int serverID = -1;
	for(int i = 0; i < numOfServers; i++){
		if(servers[i].isFree()){
			serverID = i;
			break;
		}
	}
	return serverID;
}

int serverListType::getNumOfBusyServers() const{
	int busyServers = 0;
	for(int i = 0 ; i < numOfServers; i++){
		if(!servers[i].isFree()){
			busyServers++;
		}
	}
	return busyServers;
}

void serverListType::setServerFree(int serverID){
	servers[serverID].setFree();
}

void serverListType::setServerBusy(int serverID, customerType cCustomer){
	int time = cCustomer.getTransactionTime();
	servers[serverID].setBusy();
	servers[serverID].setTransactionTime(time);
	servers[serverID].setCurrentCustomer(cCustomer);

}

void serverListType::setServerBusy(int serverID, customerType cCustomer, int tTime){
	servers[serverID].setBusy();
	servers[serverID].setTransactionTime(tTime);
	servers[serverID].setCurrentCustomer(cCustomer);

}

void serverListType::updateServers(ostream& outF){
	for(int i = 0; i < numOfServers; i++){
		if(!servers[i].isFree()){
			servers[i].decreaseTransactionTime();

			if(servers[i].getRemainingTransactionTime() == 0){
				outF << "From server number " << (i + 1) << " customer number "
				<< servers[i].getCurrentCustomerNumber() << " departed at clock unit " <<
				servers[i].getCurrentCustomerArrivalTime() + servers[i].getCurrentCustomerTransactionTime() << endl;
				servers[i].setFree();
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
class waitingCustomerQueueType: public queue<customerType>{
public:
	queue<customerType> q;
	waitingCustomerQueueType(int size = 100);
	void updateWaitingQueue();
};

void waitingCustomerQueueType::updateWaitingQueue(){
	customerType cust(1);
	cust.setWaitingTime(-1);
	int wTime = 0;

	q.push(cust);

	while(wTime != -1){
		cust = q.front();
		while(!q.empty()){
			q.pop();
		}
		wTime = cust.getWaitingTime();
		if(wTime == -1){
			break;
		}
		cust.incrementWaitingTime();
		q.push(cust);
	}

}

int factorial(int x){
	if(x == 0 || x == 1){
		return x;
	} else {
		return(x*factorial(x-1));
	}
}

double probability(double lambda, double k){
	double a = exp(-lambda);
	double b = lambda * k;
	double c = factorial(k);
	return ((a*b)/c);
}

void setSimulationParameters(int &sTime, int &numOfServers, int &transTime, int &tBetweenCArrival){
	sTime = 100;
	numOfServers = 1;
	transTime = 9;
	tBetweenCArrival = 4;
}




int main() {


	// When a server becomes free and the customer queue is nonempty, we can move the
	// customer at the front of the queue to the free server to be served.
	// Moreover, when a customer starts the transaction, the waiting time ends.
	// The waiting time of the customer is added to the total waiting time.
	// The general algorithm to start the transaction (supposing that serverID denotes the ID of the free server) is as follows:

	queue<customerType> queue1;
	customerType customer1(1);
	serverType server1;
	serverListType serverListType1(1);
	int time, custNumber, serverNumber, tranTime, timeBetween, totalWait = 0;
	setSimulationParameters(time, serverNumber, tranTime, timeBetween);

	//cout << "IDSF" << endl;

	int busyServers;
	queue1.push(customer1);
	if(server1.isFree()){
		custNumber = customer1.getCustomerNumber();
		serverListType1.setServerBusy(serverNumber, custNumber);
	}
Z
	if(server1.isFree()){
		cout << "OFF" << endl;
	} else {
		cout << "SKDKD" << endl;
	}
	int counter = 0;















	return 0;
}
 *
 */
