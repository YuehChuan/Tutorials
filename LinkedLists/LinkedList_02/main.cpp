#include <iostream>

using namespace std;

struct node{
  int val;
  node* next;
  node(int v_) : val(v_), next(NULL) {};
};

class linkedlist {
  public:
     node* head;

     linkedlist() {
        head = NULL;
     }

     void addSortedNode(int v_) {
       //case 1: the list has not yet started
       if(!head) {
         head = new node(v_);
       }
       else{
         node* cur = head;
         node* prev = NULL;
         node* temp = new node(v_);
         while(cur && v_ > cur->val)
           prev = cur, cur = cur->next;
         //case 2: v_ is the smallest node in the list.
         if(!prev)
           temp->next = head, head = temp;
         //case 3: v_ is in the middle of the list
         else if(prev && cur)
           prev->next = temp, temp->next = cur;
         //case 4: v_ is at the end of the list
         else if(!cur)
           prev->next = temp;
       }
     }

     void print() {
       node* temp = head;
       cout<<"Printing list: "<<endl<<"[";
       while(temp->next) {
         cout<<temp->val<<", ";
         temp = temp->next;
       }
       if(temp)
         cout<<temp->val;
       cout<<"]"<<endl;
     }
};

/*
//bonus code to be used in merging linked lists//
node* mergeLists(linkedlist a, linkedlist b) {
  node* temp_a = a.head;
  node* temp_b = b.head;
  node* runner;
  if( temp_a->val <= temp_b->val )
    runner = temp_a, temp_a = temp_a->next;
  else
    runner = temp_b, temp_b = temp_b->next;
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
    if(temp_a->val <= temp_b->val)
      runner->next = temp_a, temp_a = temp_a->next;
    else
      runner->next = temp_b, temp_b = temp_b->next;
    runner = runner->next;
  }
  return head;
}
*/

int main() {
  linkedlist ll;
  ll.addSortedNode(3);
  ll.addSortedNode(1);
  ll.addSortedNode(2);
  ll.addSortedNode(4);
  ll.print();
  return 0;
}
