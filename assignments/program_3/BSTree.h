#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


//http://www.webgraphviz.com/

using namespace std;

struct node1 {
	string data;
	node1 *left;
	node1 *right;
	node1()
	{
		data = "";
		left = NULL;
		right = NULL;
	}
	node1(string w)
	{
		data = w;
		left = NULL;
		right = NULL;
	}
};

class BSTree
{
private:
	node1 *root;
	int count(node1 *);
	void insert(node1 *&, node1 *&);
	void print_node(node1 *, string);
	node1 *minValueNode(node1 *);
	node1 *deleteNode(node1 *&, string);
	int height(node1 *);
	void printGivenLevel(node1 *, int);
	void GraphVizGetIds(node1 *, ofstream &);
	void GraphVizMakeConnections(node1 *, ofstream &);

public:
	BSTree();
	~BSTree();
	int count();
	void insert(string);
	void deleteNode(string);
	void minValue();
	int height(string);
	string top();
	void printLevelOrder();
	void GraphVizOut(string);
	int search(string);
};