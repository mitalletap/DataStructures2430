//============================================================================
// Name        : hw4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <queue>
#define INF 0x3f3f3f
using namespace std;

typedef pair<double , double> iPair;

class Graph {
	int vertex;
	list< pair<double, double> > *adj;
public:
	Graph(int v);
	void addEdge(double x, double y, double z);
	void shortestPath(double s);
};

Graph::Graph(int v){
	this->vertex = v;
	adj = new list<iPair>[v];
}

void Graph::addEdge(double x, double y, double z){
	adj[x].push_back(make_pair(y,z));
	adj[y].push_back(make_pair(x,z));
}

void Graph::shortestPath(double s){
	priority_queue<iPair, vector<iPair>, greater<iPair> > pq;
	vector<double> distance(vertex, INF);
	pq.push(make_pair(0,s));
	distance[s] = 0;

	while(!pq.empty()){
		double t = pq.top().second;
		pq.pop();

		list<pair<double,double> >::iterator i;
		for(i = adj[t].begin(); i != adj[t].end(); ++i){
			double v = (*i).first;
			double w = (*i).second;

			if(distance[t] > distance[v] + w){
				distance[v] = distance[t] + w;
				pq.push(make_pair(distance[v], v));
			}
		}
	}
	cout << "Distance from source: " << endl;
	for(double i = 0; i < vertex; ++i){
		cout << distance[i] << endl;
	}
}


double main(){
	double vertex = 10;
	Graph g(vertex);
	g.addEdge(0, 1, 4.2);
	g.addEdge(0, 7, 8.5);
	g.addEdge(1, 2, 8.3);
	g.addEdge(1, 7, 11.6);
	g.addEdge(2, 3, 7.8);
	g.addEdge(2, 8, 2.2);
	g.addEdge(2, 5, 4.9);
	g.addEdge(3, 4, 9.0);
	g.addEdge(3, 5, 14.2);
	g.addEdge(4, 5, 10.6);

	g.shortestPath(0);
}






















































/*
 * //============================================================================
// Name        : hw4.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct set {
	int start;
	int end;
	double size;
};




int main() {

	string input = "input41.txt", str, start, end, size;
	ifstream inputFile(input);
	vector<set> vec1;

	while(!inputFile.eof()){
		getline(inputFile, str);
		set set1;
		istringstream ss(str);
		while(ss >> start >> end >> size){
			int x = stoi(start);
			int y = stoi(end);
			double z = stod(size);
			cout << "number: " << x << "-" << y << "-" << z << endl;

			set1.start = x;
			set1.end = y;
			set1.start = z;
			vec1.push_back(set1);
		}
		//cout << str << endl;
	}

	cout << endl;



//	for(int i = 0; i < vec1.size(); i++){
//		cout << "Start: " << vec1[i].start << endl;
//		cout << "End: "<< vec1[i].end << endl;
//		cout << "Size: "<< vec1[i].size << endl;
//	}










	return 0;
}
 *
 */


















