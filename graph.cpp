#include <iostream>
#include <string>
#include "graph.h"
#include <iomanip>
#define INFINITY 10000000000000000
using namespace std;

/*
   Graph class for use in Project 5.

   This provided code does not include any specific data structure
   for storing a graph, only a list of methods that will be called 
   from main. Based on the project handout and the lecture slides,
   select a method for storing the graph and implement it here.

*/

// Constructor for Graph. Read in data from the input
// and set up your data structures here.
Graph::Graph()
{
}

// Code for part 1. Print out the sequence of airports and price
// of the trip.
int getIndex(string *airport, string str, int num){
	for(int i =0; i < num; i++){
		if(str == airport[i]){
			return i;
		}
	}
	return -1;
}
void printpath(double *prev, int dest,double cost, string *airport, int src){
	if(prev[dest] == -1){
		return;
	}
	printpath(prev, prev[dest], cost, airport, src);
	string s = airport[dest];
	string t = airport[src];
	cout << s << " " ;
}
void printanswer(double *minCost, int num, double* prev,int src, string destination, string *airport, bool * visited){
	string source =airport [src];
	int dest = getIndex(airport, destination, num);

	double cost = minCost[dest];
	// not possible case
	if (cost == INFINITY || visited[dest] == false) {
		cout <<"not possible"<< endl;
		return;
	}

	cout << airport[src] << " ";
	printpath(prev, dest, cost, airport, src);
	cout<< setprecision(2)<< fixed << cost << endl;

}
/*
 * IMPORTANT QUESTION ABOUT MIN 
 *
 *
 */ 
int min(double minCost[], bool visited[], int v){
	double min = INFINITY;
	int min_index;
	for(int i =0; i < v; i++){
		if(visited[i] == false && minCost[i] <= min){ // Shou;d it be <= pr <
			min = minCost[i];
			min_index = i;
		}
	}
	
	return min_index;
}
void Graph::find_ticket(double **matrix, string* airport, int num_airport, double *cost, const string &source,const string &destination)
{
	int v = num_airport;
	double minCost[v];
	double prev[v];
	bool visited[v];
	
	for(int i =0; i < v; i++){
		minCost[i] = INFINITY;
		prev[i] = -1;
		visited[i] = false;
	}
	// get the index of source from the airpotrt array 
	int src = getIndex(airport, source, v); // maybe I can get the index of src from main rather thamn getting string
	minCost[src] = 0; 

	for(int i =0; i < v; i++){
		int u = min(minCost, visited, v);
		visited[u]=true;
		
		for(int j=0; j < v; j++){
			double alt = minCost[u]+matrix[u][j];
			if(!visited[j] && matrix[u][j] && ( alt < minCost[j])){
				minCost[j] = minCost[u] + matrix[u][j];
				prev[j] = u;	
			}

		}
	}
	printanswer(minCost, v, prev, src, destination, airport, visited);

}

// Code for part 2. Print out the tour sequence or "not possible"
// if not all cities can be visited.

double getMin(double **matrix,int i, double min,int min_i, int min_j, bool visited[], int num_airport){
	for(int j=0; j < num_airport; j++){
		if(matrix[i][j] && (matrix[i][j] < min) && !visited[j]){
			min = matrix[i][j];
			min_i = i;
			min_j = j;
		}
	}
	return min;	
}
double get_j(double **matrix,int i, double min,int min_i, int min_j, bool visited[], int num_airport){
	for(int j=0; j < num_airport; j++){
		if(matrix[i][j] && (matrix[i][j] < min) && !visited[j]){
			min = matrix[i][j];
			min_i = i;
			min_j = j;
		}
	}
	return min_j;	
}
void Graph::mst(double **matrix, int num_airport, string str_root, string *airport){
	int v = num_airport;
	int min_i =0;
	int min_j = 0;
	double **mstMatrix;
	mstMatrix = new double *[num_airport];
	for(int i=0; i < num_airport; i++){
		mstMatrix[i] = new double[num_airport];
	}

	bool visited[num_airport];
	for(int i =0; i < num_airport; i++){
		visited[i] = false;
	}
	
	string arr[num_airport];
	arr[0] = airport[0];
	visited[0] = true;
		
	for(int k =1; k < num_airport; k++){
		double min =INFINITY;	
		for(int i =0; i < num_airport; i++){
			if(arr[i] != ""){
				int u = getIndex(airport, arr[i], v);
				for(int j =0; j < num_airport; j++){
					if((matrix[u][j])&& (!visited[j]) && (matrix[u][j] < min)){
						min_i = u;
						min_j = j;
						min = matrix[u][j];
					}
				}
			}
			/*cout << "min " << min << endl;
			cout << "min_i " << min_i << endl;
			cout << "min_j " << min_j << endl;*/	
		}
		mstMatrix[min_i][min_j] = min;
		mstMatrix[min_j][min_i] = min;
		visited[min_i]  = true;
		visited[min_j] 	= true;
		
		arr[k] = airport[min_j];
	}
	
	/*for(int i =0; i < num_airport; i++){
		for(int j =0; j < num_airport; j++)
			cout<< setw(9) << mstMatrix[i][j] << "   "  ;
		cout << endl;
	}*/
	int flag = 1;
	for(int i =0; i < num_airport; i++){
		if(!visited[i]){
			flag = 0;
		}
	}
	for(int i =0; i < num_airport; i++){
		visited[i] = false;
	}
	if(flag == 1){
		eulerian_tour(str_root, mstMatrix, airport, visited, num_airport);
	}
	else{
		cout << "not possible" << endl;
	}

}
void Graph::eulerian_tour(string source, double **matrix, string *airport, bool *visited, int num_airports){
	cout << source << endl;
	int index = getIndex(airport, source, num_airports);
	visited[index] = true;
	for(int i =0; i < num_airports; i++){
		double value = matrix[index][i];
		if(value != 0 && !visited[i]){
			visited[i] = true;
			eulerian_tour(airport[i], matrix, airport, visited, num_airports);
		}
	}
}

