/**
* Riley Kunkel
*1-22-18
*/

#include <iostream>

using namespace std;

//Create a container for our list data
struct node {
	int data;
	node* next;
};

/**
* Class: intLinkedList
* Purpose:
*     Implements a singly linked list that holds integers.
* Methods:
*     void  frontSert(int x)
*     node* find(int key)
*     node* remove(int key)
*     void  print()
*/
class intLinkedList {
private:
	node * Head;
public:
	intLinkedList() {
		Head = NULL;
	}
	void frontSert(int x) {
		//empty list case
		if (!Head) {
			Head = new node;
			Head->data = x;
			Head->next = NULL;
		}
		else {//not empty list
			node* T = new node;
			T->data = x;
			T->next = Head;
			Head = T;
		}
	}

	node* Find(int key) {
		node* temp = Head;
		while (temp) {
			if (temp->data == key) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}

	void orderedSert(int x) {
		if (!Head)
			frontSert(x);
		else {
			node* prev = Head;
			node* temp = new node;
			temp->data = x;

			if (prev->data > temp->data)
			{
				temp->next = prev;
				Head = temp;
			}
			else
			{
				while (prev->next != NULL && prev->next->data < temp->data)
				{
					prev = prev->next;
				}
				temp->next = prev->next;
				prev->next = temp;
			}
		}
	}

  
	void Remove(int key) {
		node* result = Find(key);
		if (result) {
			node* temp = Head;
			while (temp->next != result) {
				temp = temp->next;
			}
			temp->next = result->next;
			delete result;
		}
	}

	void print() {
		node* p = Head;
		while (p) {
			cout << p->data << endl;
			p = p->next;
		}
	}
};

int main() {
	intLinkedList mylist;
	int k = 0;
	while (k < 50) {
		mylist.orderedSert(k);
		k++;
	}
	mylist.Remove(38);
	mylist.print();
	mylist.orderedSert(38);
	mylist.print();

	system("pause");
}
