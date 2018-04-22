///////////////////////////////////////////////////////////////////////////////
//                   YOU MUST COMPLETE AND COMMENT YOUR CODE!
// Title:            Connecting Graphs
// Files:            distance.h , csv.h, edge_heap.h, graph.h, driver.cpp, graph.out, filtered_cities.csv
// Semester:         Algorithms Spring 2018
//
// Author:           Riley Kunkel
// Email:            r_kunkel@hotmail.com
// Description:
//       Takes a group of cordinates and connects them with edges to make a graph MAY TAKE HOURS TO RUN
/////////////////////////////////////////////////////////////////////////////////

// A simple representation of graph using STL
#include "graph.h"
#include "edge_heap.h"


using namespace std;

void randomEdges(graph &g, int numEdges) {
	int r1, r2;
	latlon from;
	latlon to;
	double d;
	for (int i = 0; i<numEdges; i++) {
		r1 = rand() % g.vertexList.size();
		r2 = rand() % g.vertexList.size();
		from = g.vertexList[r1]->loc;
		to = g.vertexList[r2]->loc;
		d = distanceEarth(from.lat, from.lon, to.lat, to.lon);
		g.addEdge(r1, r2, (int)d, true);
	}
}

/**
* loadGraphCSV - loads a graph with the given csv
* Params:
*     string filename  - filename to open
* Returns
*     graph
*/
graph loadGraphCSV(string filename, string stat = "")
{
	int zip;
	double lat;
	double lon;
	string city;
	string state;
	string county;

	strMapInt cityCheck;

	int i = 0;

	graph G;

	ifstream file(filename);

	for (CSVIterator loop(file); loop != CSVIterator(); ++loop)
	{
		zip = stoi((*loop)[0]);
		if ((*loop)[1].length() > 0)
		{
			lat = stod((*loop)[1]);
		}
		else
		{
			lat = 0.0;
		}

		if ((*loop)[2].length() > 0)
		{
			lon = stod((*loop)[2]);
		}
		else
		{
			lon = 0.0;
		}

		city = (*loop)[3];
		state = (*loop)[4];
		county = (*loop)[5];

		
		if (cityCheck.find(city) == cityCheck.end())
		{
			// Add the city as a key to the map.
			cityCheck[city] = 0;

			if (state == stat) {
				G.addVertex(city, state, lat, lon);
				i++;
			}
			else if(stat == "ALL" && state != "PR" && state != "GU" && state != "AK") {
				G.addVertex(city, state, lat, lon);
				i++;
			}
		}
	}

	return G;
}

/**
* filterDups - filters out duplicate cities and creates new output file
* Params:
*     string filename  - filename to open
*     string outfile   - filename to write to
* Returns
*     graph
*/
void filterDups(string filename, string outfile)
{
	int zip;
	double lat;
	double lon;
	string city;
	string state;
	string county;

	strMapInt cityCheck;

	int i = 0;


	ifstream file(filename);
	ofstream out(outfile);

	for (CSVIterator loop(file); loop != CSVIterator(); ++loop)
	{
		zip = stoi((*loop)[0]);
		if ((*loop)[1].length() > 0)
		{
			lat = stod((*loop)[1]);
		}
		else
		{
			lat = 0.0;
		}

		if ((*loop)[2].length() > 0)
		{
			lon = stod((*loop)[2]);
		}
		else
		{
			lon = 0.0;
		}

		city = (*loop)[3];
		state = (*loop)[4];
		county = (*loop)[5];


		if (cityCheck.find(city) == cityCheck.end())
		{
			// Add the city as a key to the map.
			cityCheck[city] = 0;
			out << zip << "," << lat << "," << lon << "," << city << "," << state << "," << county << "\n";

		}


	}

}


void filledgeHeap(graph &g, edgeHeap &eh, int frompos) {
	edge * e = NULL;
	double distance;
	latlon from;
	latlon to;
	for (int topos = 0; topos <= g.vertexList.size()-1; topos++)//creates edge frompos to topos 
	{
		from = g.vertexList[frompos]->loc;
		to = g.vertexList[topos]->loc;
		if (frompos != topos) {
			distance = distanceEarth(from.lat, from.lon, to.lat, to.lon);
			e = new edge(frompos, topos, distance); //makes edge
			eh.Insert(e);//adds edge to heap
		}
	}
}

//creates shortest distance edges for graph g
void addgraphEdges(graph &g, edgeHeap eh, int frompos, int edgesWanted) {
	edge * e = NULL;
	int edgesMade = 0;//Tracks edges made
	int attempt = 0;//Attempt to make edge 
	vertex v1 = *g.vertexList[frompos];
	while (edgesMade < edgesWanted && attempt < g.vertexList.size() - 1 && v1.E.size() < edgesWanted) {//While edgesMade are one less than edgesWanted and attempt to make edge is less than vertexList
		attempt++;
		edge e = *eh.Extract();//Extract edge from edgeHeap  
		vertex v = *g.vertexList[e.toID];//
		vertex v1 = *g.vertexList[frompos];
		if (v.E.size() < edgesWanted && v1.E.size() < edgesWanted) {// if vertex "a"'s edge degree over edgesWanted skips adding edge
			g.addEdge(frompos, e.toID, e.weight, false);// add edge on top of heap to graph g 
			edgesMade++;
		}
	}
	delete[] e;
}


void createSpanningTree(graph &g, string startcity, int edgesWanted)
{
	edgeHeap eh;
	
	int ln = g.searchGraphID(startcity);//Finds startcity id
	int frompos = 0;
	while (frompos < g.vertexList.size()) {
		vertex v = *g.vertexList[frompos];
		if (v.E.size() < edgesWanted) {//if frompos vertex's degree is less than edgesWanted 
			filledgeHeap(g, eh, frompos);
			addgraphEdges(g, eh, frompos, edgesWanted);
		}
		cout << frompos << endl;
		frompos++;
		int k = eh.Size();
		for (int m = 0; m < k-1; m++) {
			eh.Extract();
		}
	}
}




// Test Driver
//int argc, char **argv REPLACE
int main()
{
	ofstream outfile;
	outfile.open("graph.out");
	int edgesWanted = 3;
	
	//if (argc > 2) {
	//	max_vertices = stoi(argv[1]);
	//	max_edges = stoi(argv[2]);
	//}
	//else {
	//	cout << "Usage: ./graph max_vertices max_edges" << endl;
	//	exit(0);
	//}


	
	graph G = loadGraphCSV("filtered_cities.csv", "PR");
	createSpanningTree(G, "San Juan", edgesWanted);
	outfile << "San Juan, Puerto Rico" << endl;
	outfile << G.num_edges << " edges " << G.miles << " miles" << endl;

	//graph G1 = loadGraphCSV("filtered_cities.csv", "ALL");
	//createSpanningTree(G1, "Lebanon", edgesWanted);
	//outfile << "Lebanon, Kansas" << endl;
	//outfile << G1.num_edges << " edges " << G1.miles << " miles" << endl;


	//graph G2 = loadGraphCSV("filtered_cities.csv", "ALL");
	//createSpanningTree(G2, "Miami", edgesWanted);
	//outfile << "Miami, Florida" << endl;
	//outfile << G2.num_edges << " edges" << G2.miles << " miles" << endl;

	//graph G3 = loadGraphCSV("filtered_cities.csv", "ALL");
	//createSpanningTree(G3, "Dallas", edgesWanted);
	//outfile << "Dallas, Texas" << endl;
	//outfile << G3.num_edges << " edges" << G3.miles << " miles" << endl;

	//graph G4 = loadGraphCSV("filtered_cities.csv", "ALL");
	//createSpanningTree(G4, "Boston", edgesWanted);
	//outfile << "Boston, Massachusetts" << endl;
	//outfile << G4.num_edges << " edges" << G4.miles << " miles" << endl;


	

	//graphviz feature
	//outfile<<G.graphViz(true);
	
	
	//outs vertices with degree of edges
	//int *size = G.graphSize();
	//cout<<"V= "<<size[0]<<" E= "<<size[1]<<endl;
	// for(int i=0;i<G.vertexList.size();i++){
	//     cout<<(*G.vertexList[i])<<endl;
	// }
	return 0;
}
