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
	int max = 19000;

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
			else if(stat == "ALL" && state != "PR") {
				G.addVertex(city, state, lat, lon);
				i++;
			}
		}

		if (i > max && max != 0) {
			return G;
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
// find the three closest vertices and create edges between them.
void createSpanningTree(graph &g, string cit, int am)
{
	latlon from;
	latlon to;
	double d;
	int ln = g.searchGraphID(cit);

	for (int num2 = ln; num2 <= g.vertexList.size()-2; num2++)//loop for "from"
	{
		edgeHeap eh;//creates heap
		vertex b = *g.vertexList[num2];//reference for vertex from 
		int k = b.E.size();//tracks from edges degree
		if (k <= am-2) {//if less then 2 degree goes in to to add edges
			for (int num1 = 0; num1 <= g.vertexList.size()-2; num1++)//loop for "to"
			{
				from = g.vertexList[num2]->loc;
				to = g.vertexList[num1]->loc;
				d = distanceEarth(from.lat, from.lon, to.lat, to.lon);
				edge * e = NULL;
				e = new edge(num2, num1, d); //makes edge
				eh.Insert(e);//adds edge to heap
			}
			eh.Extract();//removes first shortest path which is to itself 
			int em = 0;//tracks edges made
			int r = 0;
			int half = g.vertexList.size() / 2;
			while (em <= am-1 && r < half) {
				r++;
				edge e = *eh.Extract();//extract next edge which is the shortest
				int to = e.toID;//grabs to vertice id to check edge size
				vertex a = *g.vertexList[to];//a refferences g "to" vertice
				int z = a.E.size();
				if (z < am-1) {// if degree is less than 3
					g.addEdge(num2, to, (int)d, false);// add edge to graph
					em++;// increment edges made... if vertex a over 3 will skip and not increment
				}
			}
		}
	}


}




// Test Driver
//int argc, char **argv REPLACE
int main(int argc, char **argv)
{
	ofstream outfile;
	outfile.open("graph.out");
	int max_vertices = 18952;
	int max_edges = 190000;
	int am = 3;
	
	if (argc > 2) {
		max_vertices = stoi(argv[1]);
		max_edges = stoi(argv[2]);
	}
	else {
		cout << "Usage: ./graph max_vertices max_edges" << endl;
		exit(0);
	}


	
	graph G = loadGraphCSV("filtered_cities.csv", "PR");
	createSpanningTree(G, "San Juan", am);
	outfile << "San Juan, Puerto Rico" << endl;
	outfile << G.num_edges << " edges " << G.miles << " miles";

	graph G1 = loadGraphCSV("filtered_cities.csv", "ALL");
	createSpanningTree(G1, "Lebanon", am);
	outfile << "Lebanon, Kansas" << endl;
	outfile << G1.num_edges << " edges" << G1.miles << " miles" << endl;

	graph G2 = loadGraphCSV("filtered_cities.csv", "ALL");
	createSpanningTree(G2, "Miami", am);
	outfile << "Miami, Florida" << endl;
	outfile << G2.num_edges << " edges" << G2.miles << " miles" << endl;

	graph G3 = loadGraphCSV("filtered_cities.csv", "ALL");
	createSpanningTree(G3, "Dallas", am);
	outfile << "Dallas, Texas" << endl;
	outfile << G3.num_edges << " edges" << G3.miles << " miles" << endl;

	graph G4 = loadGraphCSV("filtered_cities.csv", "ALL");
	createSpanningTree(G4, "Boston", am);
	outfile << "Boston, Massachusetts" << endl;
	outfile << G4.num_edges << " edges" << G4.miles << " miles" << endl;


	

	//graphviz feature
	//outfile<<G.graphViz(true);
	
	
	//outs vertices with degree of edges
	/*int *size = G.graphSize();
	cout<<"V= "<<size[0]<<" E= "<<size[1]<<endl;
	 for(int i=0;i<G.vertexList.size();i++){
	     cout<<(*G.vertexList[i])<<endl;
	 }*/
	return 0;
}