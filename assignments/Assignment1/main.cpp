/**
* Riley Kunkel
*also dont know if this is the right one will have to look at cou when i get home
*/

#include <iostream>
#include <ctime>

using namespace std;

//Create a container for our list data
struct node{
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
class intLinkedList{
  private:
  node* Head;
  public:
  intLinkedList(){
    Head = NULL;
  }
  void frontSert(int x){
    //empty list case
    if(!Head){
      Head = new node;
      Head->data = x;
      Head->next = NULL;
    }else{//not empty list
      node* T = new node;
      T->data = x;
      T->next = Head;
      Head = T;
    }
  }
  void orderedSert(int x){
    //empty list case
    if(!Head){
      Head = new node;
      Head->data = x;
      Head->next = NULL;
    }
    else{//not empty list
      node* T = new node;
      T->data = x;
      node* Temp = new node;
      Temp = Head;
      while(Temp->next != NULL && t->data > Temp->next->data){
        Temp = Temp->next;
      }
      if(Temp->Next == NULL){
      T = Temp->next;
      T->next = NULL
      }
      else{
        node* Temp2 = new node;
        Temp2 = Temp->Next;
        Temp->next=T;
        T-next = Temp2;
      }
    }
  }
  
  bool find(int key){
    node* result = Find(key);
    if(result){
      node* temp = Head;
      while(temp->next != result){
        temp = temp->next;
      }
      return true
    }
    return false
  }
  
  void Remove(int key){
    node* result = Find(key);
    if(result){
      node* temp = Head;
      while(temp->next != result){
        temp = temp->next;
      }
      temp->next = result->next;
      delete result;
    }
  }
  
  void print(){
    node* p = Head;
    while(p){
      cout<<p->data<<endl;
      p = p->next;
    }
  }
};

int main() {
  // seed random number generator
  srand(8734587);
  
  // ummmm
  cout << "Hello World!\n";
  
  // declare instance of intLinkedList turning
  // a class definition into an "object"
  intLinkedList mylist;
  
  //Load 10 random ints into our list
  for(int i=0;i<10;i++){
    mylist.frontSert(rand()%100);
  }
  
  //print the list
  mylist.print();
  
  //find some value
  cout<<mylist.Find(99)<<endl;
  
  //remove some value 
  mylist.Remove(58);
  
  //print the list again
  mylist.print();

  system("pause");
}
