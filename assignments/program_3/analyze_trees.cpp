//Riley Kunkel
//Algorithms Program 3
//Part 2

#include <iostream>
#include <fstream>
#include <sstream>
#include "avlTree.h"
#include "BSTree.h"


using namespace std;


int main(int argc, char **argv)
{
	avlTree avl;
	BSTree bs;
	ifstream infile;
	string sline;
	ofstream outfile;
	
	//Word beginning with M to help ballance bs tree
	bs.insert("mallard");

	//Fill AVL and BS with words
	infile.open("adverbs.txt");
	while (!infile.eof()) {
		getline(infile, sline);
		avl.insert(sline);
		bs.insert(sline);
	}
	infile.close();
	
	infile.open("adjectives.txt");
	while (!infile.eof()) {
		getline(infile, sline);
		avl.insert(sline);
		bs.insert(sline);
	}
	infile.close();

	infile.open("animals.txt");
	while (!infile.eof()) {
		getline(infile, sline);
		avl.insert(sline);
		bs.insert(sline);
	}
	infile.close();

	infile.open("verbs.txt");
	while (!infile.eof()) {
		getline(infile, sline);
		avl.insert(sline);
		bs.insert(sline);
	}
	infile.close();

	infile.open("tenthousandwords.txt");
	string word;
	int avlc = 0;
	int bsc = 0;
	while (!infile.eof()) {
		infile >> word;
		avlc = avlc + avl.search(word);
		bsc = bsc + bs.search(word);

	}

	outfile.open("analysis.out");
	outfile << "The number of AVL Comparisons is " << avlc << "\n";
	outfile << "The number of BS Comparisons is " << bsc << "\n";

	system("pause");
	return 0;
}