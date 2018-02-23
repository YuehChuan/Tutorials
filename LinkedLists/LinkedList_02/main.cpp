#include <iostream>

using namespace std;

struct node{
  int date;
  string description;
  node* next;
  node(int dt_, string desc_ ) : date(dt_), description(desc_), next(NULL) {};
};

class linkedlist {
  public:
     node* head;

     linkedlist() {
        head = NULL;
     }

     void addSortedNode(int dt_, string desc_ ) {
       //case 1: the list has not yet started
       if(!head) {
         head = new node(dt_,desc_);
       }
       else{
         node* cur = head;
         node* prev = NULL;
         node* temp = new node(dt_,desc_);
         while(cur && dt_ > cur->date) {
           prev = cur;
           cur = cur->next;
         }
         //case 2: dt_ is the smallest node in the list. Note, this also means the head of the list is now our temp node.
         if(!prev) {
           temp->next = head;
           head = temp;
         }
         //case 3: dt_ is in the middle of the list
         else if(prev && cur){
           prev->next = temp;
           temp->next = cur;
         }
         //case 4: dt_ is at the end of the list
         else if(!cur) {
           prev->next = temp;
         }
       }
     }

     void print() {
       node* temp = head;
       cout<<"Printing list: "<<endl<<"[";
       while(temp->next) {
         cout<<"{date: "<<temp->date<<", description: \""<<temp->description<<"\"}, "<<endl;
         temp = temp->next;
       }
       if(temp)
         cout<<"{date: "<<temp->date<<", description: \""<<temp->description<<"\"}";
       cout<<"]"<<endl;
     }
};

node* mergeLists(linkedlist a, linkedlist b) {
  node* temp_a = a.head;
  node* temp_b = b.head;
  node* runner;
  if( temp_a->date <= temp_b->date ) {
    runner = temp_a;
    temp_a = temp_a->next;
  }
  else {
    runner = temp_b;
    temp_b = temp_b->next;
  }
  node* head = runner;

  while(runner) {
    if(!temp_a) {
      runner->next = temp_b;
      break;
    }
    else if(!temp_b) {
      runner->next = temp_a;
      break;
    }
    if(temp_a->date <= temp_b->date) {
      runner->next = temp_a;
      temp_a = temp_a->next;
    }
    else {
      runner->next = temp_b;
      temp_b = temp_b->next;
    }
    runner = runner->next;
  }
  return head;
}

int main() {
  linkedlist ll_a;
  ll_a.addSortedNode(5,"I");
  ll_a.addSortedNode(4,"harder");
  ll_a.addSortedNode(6,"work");
  ll_a.addSortedNode(8,"luckier");
  ll_a.addSortedNode(7,"the");

  linkedlist ll_b;
  ll_b.addSortedNode(3,"The");
  ll_b.addSortedNode(10,"get");
  ll_b.addSortedNode(9,"I");

  ll_a.head = mergeLists(ll_a,ll_b);

  ll_a.print();

  return 0;
}
