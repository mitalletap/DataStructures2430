//============================================================================
// Name        : ga5.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// Help received from Geeksforgeeks

// Mital Patel 50%, Steven Stricklin 50%



#include <iostream>
#include <list>
#include <time.h>
using namespace std;



class Graph {
private:
	int v;
	list<int> *adj;

public:
	Graph(int v);
	void addEdge(int a, int b);
	void addEdge(int a, int b, int c);
	void BFS(int r);
	void DFS(int r);
	void DFSHelper(int r, bool visited[]);
	void printAdjList();
	void print();

};


// Constructor
Graph::Graph(int v){
	// Variable Initialization
	this->v = v;
	adj = new list<int>[v];

}

// Add Edge
void Graph::addEdge(int a, int b){
	adj[a].push_back(b);
}


// BFS
void Graph::BFS(int r){
	// visited pointer for each root node
	bool *visited = new bool[v];

	// set all bool's to false
	for(int i = 0; i < v; i++){
		visited[i] = false;
	}

	list<int> queue;

	visited[r] = true;
	queue.push_back(r);


	// set up iterator
	list<int>::iterator i;

	while(!queue.empty()){
		r = queue.front();
		cout << r << "->";
		queue.pop_front();


		for(i = adj[r].begin(); i != adj[r].end(); ++i){
			if(!visited[*i]){
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
//		if(queue.empty()){
//			cout << "NULL" << endl;
//		}
	}
}

void Graph::DFSHelper(int r, bool visited[]){
	visited[r] = true;
	cout << r << "->";

	list<int>::iterator i;
	for(i = adj[r].begin(); i != adj[r].end(); ++i){
		if(!visited[*i]){
			DFSHelper(*i, visited);
		}
	}
}

void Graph::DFS(int r){
	bool *visited = new bool[v];

	// set all bool's to false
	for(int i = 0; i < v; i++){
		visited[i] = false;
	}

	DFSHelper(r, visited);
}

void Graph::printAdjList(){
	for (int i = 0; i < v; ++i){
		cout << "Adjacency list of vertex: (" << i << ",";
		for (auto x : adj[i])
			cout << x << ")";
	   cout << endl;
	}
}



int main() {
	int size, root, selection;
	time_t startWhole, startComp;
	startWhole = clock();

	cout << "What size graph would you like? ";
	cin >> size;

	Graph graph1(size);

	// Random Numbers
	srand(time(NULL));
	for(int i = 0; i < size; i++){
		int r1 = rand() % size;
		graph1.addEdge(i, r1);
	}

	cout << "Where would you like to start? ";
	cin >> root;

	cout << "Which sort would you like? " << endl;
	cout << "1. BFS" << endl;
	cout << "2. DFS" << endl;
	//cout << "3. BFS and DFS" << endl;
	cin >> selection;
	startComp = clock();

	if(selection > 0 && selection <= 2){
		switch(selection){
		case 1:
			cout << "BFS: ";
			graph1.BFS(root);
			cout << endl;
			graph1.printAdjList();
			break;
		case 2:
			cout << "DFS: ";
			graph1.DFS(root);
			cout << endl;
			graph1.printAdjList();
			break;
//		case 3:
//			cout << "BFS: ";
//			graph1.BFS(root);
//			cout << endl;
//			cout << "DFS: ";
//			graph1.DFS(root);
//			cout << endl;
			graph1.printAdjList();
//			break;
		}
	} else {
		cout << "Error! You chose incorrectly!" << endl;
	}

	startWhole = clock() - startWhole;
	startComp = clock() - startComp;
	cout << "It took the program " << startWhole << " ticks to run!" << endl;
	cout << "It took the computation " << startComp << " ticks to run!" << endl;

	return 0;
}



































































































/*
 * //============================================================================
// Name        : ga5.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// Help received from Geeksforgeeks

// Mital Patel 50%, Steven Stricklin 50%



#include <iostream>
#include <list>
#include <time.h>
using namespace std;


class Graph {
private:
	int v;
	list<int> *adj;

public:
	Graph(int v);
	void addEdge(int a, int b);
	void BFS(int r);
	void DFS(int r);
	void DFSHelper(int r, bool visited[]);
	void printAdjList();
	void print();

};


// Constructor
Graph::Graph(int v){
	// Variable Initialization
	this->v = v;
	adj = new list<int>[v];
}

// Add Edge
void Graph::addEdge(int a, int b){
	adj[a].push_back(b);
}

// BFS
void Graph::BFS(int r){
	// visited pointer for each root node
	bool *visited = new bool[v];

	// set all bool's to false
	for(int i = 0; i < v; i++){
		visited[i] = false;
	}

	list<int> queue;

	visited[r] = true;
	queue.push_back(r);


	// set up iterator
	list<int>::iterator i;

	while(!queue.empty()){
		r = queue.front();
		cout << r << "->";
		queue.pop_front();


		for(i = adj[r].begin(); i != adj[r].end(); ++i){
			if(!visited[*i]){
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
//		if(queue.empty()){
//			cout << "NULL" << endl;
//		}
	}
}

void Graph::DFSHelper(int r, bool visited[]){
	visited[r] = true;
	cout << r << "->";

	list<int>::iterator i;
	for(i = adj[r].begin(); i != adj[r].end(); ++i){
		if(!visited[*i]){
			DFSHelper(*i, visited);
		}
	}
}

void Graph::DFS(int r){
	bool *visited = new bool[v];

	// set all bool's to false
	for(int i = 0; i < v; i++){
		visited[i] = false;
	}

	DFSHelper(r, visited);
}

void Graph::printAdjList(){
	for (int i = 0; i < v; ++i){
		cout << "Adjacency list of vertex: (" << i << ",";
		for (auto x : adj[i])
			cout << x << ")";
	   cout << endl;
	}
}



int main() {
	int size, root, selection;
	time_t startWhole, startComp;
	startWhole = clock();

	cout << "What size graph would you like? ";
	cin >> size;

	Graph graph1(size);

	// Random Numbers
	srand(time(NULL));
	for(int i = 0; i < size; i++){
		int r1 = rand() % size;
		graph1.addEdge(i, r1);
	}

	cout << "Where would you like to start? ";
	cin >> root;

	cout << "Which sort would you like? " << endl;
	cout << "1. BFS" << endl;
	cout << "2. DFS" << endl;
	//cout << "3. BFS and DFS" << endl;
	cin >> selection;
	startComp = clock();

	if(selection > 0 && selection <= 2){
		switch(selection){
		case 1:
			cout << "BFS: ";
			graph1.BFS(root);
			cout << endl;
			break;
		case 2:
			cout << "DFS: ";
			graph1.DFS(root);
			cout << endl;
			break;
//		case 3:
//			cout << "BFS: ";
//			graph1.BFS(root);
//			cout << endl;
//			cout << "DFS: ";
//			graph1.DFS(root);
//			cout << endl;
//			break;
		}
	} else {
		cout << "Error! You chose incorrectly!" << endl;
	}

	graph1.printAdjList();



	startWhole = clock() - startWhole;
	startComp = clock() - startComp;
	cout << "It took the program " << startWhole << " ticks to run!" << endl;
	cout << "It took the computation " << startComp << " ticks to run!" << endl;

	return 0;
}
 *
 */
