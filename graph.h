#include <iostream>
#include <string>

using namespace std;

class Graph
{
	public:
		// Constructor
		Graph(); 
		
		// Part 1: Find a ticket using Dijkstra
		void find_ticket(double**matrix,string *airport,int num_airport,double*cost, const string &source,const string &destination); 
		
		// Part 2: Try to do a tour of all cities
	void mst(double **matrix, int num_airport, string src, string *airport);
	void eulerian_tour(string source, double **matrix, string *airport, bool *visited, int num_aiports); 
	
	// Add any needed private methods here
};
