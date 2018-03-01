//****************************************************************************
// Title: Crazy Word =Generator
// Files: AVLTree.cpp, AVLTree.h, BSTree.cpp, BSTree.h,
//		  generate_words.cpp, tenthousandwords.txt, analyze_trees.cpp,
//		  adjectives.txt, adverbs.txt, animals.txt, nouns.txt, verbs.txt
// Author:Riley Kunkel
// Description: This program allows to do following. 
// Part 1: creates 10000 crazy words without duplicates
// Part 2: compare the performance of AVL Tree and Binary Search Tree
//****************************************************************************


#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <sstream>

using namespace std;

string pickAdverb();
string pickAdjective();
string pickAnimal();
string pickVerb();

int main1()
{	
	srand(time(NULL));
	ofstream outfile;
	outfile.open("tenthousandwords.txt");
	bool inf = false;
	for (int i = 1; i <= 1000; i++) {
		string crazy_word;
		string adverb = pickAdverb();
		string adjective = pickAdjective();
		string animal = pickAnimal();
		string verb = pickVerb();
		string arry[1000];

		crazy_word = adverb + " " + adjective + " " + animal + " " + verb;
		
		//Brute force search for repeats
		int k = 1;
		while (k < 1000) {
			if (crazy_word == arry[k]) {
				inf = true;
			}
			k++;
		}

		if (inf == false){
			arry[i-1] = crazy_word;
			outfile << crazy_word << "\n";
		}
	
	}

	system("pause");
	return 0;
}
// Random search for adverb
string pickAdverb() {
	string adverb;
	ifstream infile;
	infile.open("adverbs.txt");
	if (infile.is_open()) {
		int random = rand() % 100 + 1;
		int i = 1;
		while (i <= random) {
			getline(infile, adverb);
			i++;
		 }
		return adverb;
	}
	else{
		cout << "Unable to Open";
	}	
	infile.close();
}
// Random search for adjective
string pickAdjective() {
	string adjective;
	ifstream infile;
	infile.open("adjectives.txt");
	if (infile.is_open()) {
		int random = rand() % 150 + 1;
		int i = 1;
		while (i <= random) {
			getline(infile, adjective);
			i++;
		}
		return adjective;
	}
	else {
		cout << "Unable to Open";
	}
	infile.close();
}
// Random search for animal
string pickAnimal() {
	string animal;
	ifstream infile;
	infile.open("animals.txt");
	if (infile.is_open()) {
		int random = rand() % 150 + 1;
		int i = 1;
		while (i <= random) {
			getline(infile, animal);
			i++;
		}
		return animal;
	}
	else {
		cout << "Unable to Open";
	}
	infile.close();
}
// Random search for verb
string pickVerb() {
	string verb;
	ifstream infile;
	infile.open("verbs.txt");
	if (infile.is_open()) {
		int random = rand() % 150 + 1;
		int i = 1;
		while (i <= random) {
			getline(infile, verb);
			i++;
		}
		return verb;
	}
	else {
		cout << "Unable to Open";
	}
	infile.close();
}
