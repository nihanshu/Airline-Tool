#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

// Part 1: Find tickets for an airline passenger
void P5_part1(int num_airport, double **matrix, string* airport, double* cost )
{
	string cmd1,cmd2;
	Graph g;

	cin >> cmd1;
	while(cmd1 != "END") // Find tickets until END appears
	{
		cin >> cmd2;
		g.find_ticket(matrix, airport, num_airport, cost, cmd1, cmd2);
		cin >> cmd1;
	}
}

// Part 2: Perform an eulerian tour of the graph.
void P5_part2(int num_airport, double **matrix, string* airport)
{
	string cmd1;
	Graph g;

	cin >> cmd1;
	g.mst(matrix, num_airport, cmd1, airport);
	//g.eulerian_tour(cmd1, );
}
bool exist(string *airport, string port, int size){
	for (int i =0; i < size; i++){
		if(port == airport[i]){
			return true;
		}
	}
	return false;
}

void storeRoutes(string *src, string *dest, double *costArr, string *airport, int num_routes, int num_airport){
	int index =0;
	for(int i =0; i < num_routes; i++){
		double cost;
		string src_airport;
		string dest_airport;
		cin >> src_airport;
		if(!exist(airport, src_airport, num_airport)){
			airport[index] = src_airport;
			index++;
		}
		cin >> dest_airport;
		if(!exist(airport, dest_airport, num_airport)){
			airport[index] = dest_airport;
			index++;
		}
		cin >> cost;
		src[i] = src_airport;
		dest[i] = dest_airport;
		costArr[i] = cost;
	}
}

void displayAirport(string *airport, int num){
	cout << "Array of unique airport" << endl;	
	for (int i =0 ; i < num; i++){
		cout << airport[i] << endl;
	}

}
void displayroutes(string* src, string* dest, double *cost, int num){
	cout << "Printing routes" << endl;
	for(int i =0; i < num ; i++){
		cout << src[i] << " " << dest[i] << " " << cost[i] << endl;
	}
}
void sort(string *arr, int n) {

	bool swapped = true;
	int j = 0;
	string tmp;

	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < n - j; i++) {
			if (arr[i] > arr[i + 1]) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				swapped = true;
			}
		}
	}
}
int getIndex(string port, string* airport, int num){
	for(int i =0; i < num; i++){
		if(port == airport[i]){
			return i;
		}
	}
	//cout << "not found" << endl;
	return -1;
}
int main()
{
	int cmd;
	cin >> cmd;
	int num_airport;
	cin >> num_airport;
	int num_routes;
	cin >> num_routes;
	string airport[num_airport];
	double cost[num_routes];
	string srcAirports[num_routes];
	string destAirports[num_routes];
	double **adj_mat;
	adj_mat = new double *[num_airport];
	for(int i =0; i < num_airport; i++){
		adj_mat[i] = new double[num_airport];
	}
	storeRoutes(srcAirports, destAirports, cost, airport, num_routes, num_airport);

	sort(airport, num_airport);

	
	// intializing 2d matrix
//	for(int i =0 ; i < num_airport; i++){
//		for(int j =0; j < num_airport; j++){
//			adj_mat[i][j] = -1;
//		}
//	}
	// init end
	// storing start
	int index =0;
	while(index < num_routes){
		int srcIndex = getIndex(srcAirports[index], airport, num_airport);
		int destIndex = getIndex(destAirports[index], airport, num_airport);
		if (srcIndex == -1 || destIndex == -1){
			cout << "airport doesn't exist" << endl;
		}
		adj_mat[srcIndex][destIndex] = cost[index];
		adj_mat[destIndex][srcIndex] = cost[index];
		index++;
	}
	// storing done;
	// printng adjacent matrix
	// don't forget to remove it!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*	for(int i = 0; i < num_airport; i++){
		for(int j =0; j < num_airport; j++){
			cout << adj_mat[i][j] << " ";	
		}
		printf("\n");
	}*/
	// end
	
	if(cmd == 1) P5_part1( num_airport, adj_mat, airport, cost);
	else if(cmd == 2) P5_part2(num_airport, adj_mat, airport);
	return 0;
}
