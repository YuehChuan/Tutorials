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
       if(!head) {
         head = new node(v_);
       }
       else{
         node* cur = head;
         node* prev = NULL;
         node* temp = new node(v_);
         while(cur && v_ > cur->val)
           prev = cur, cur = cur->next;
         if(!prev)
           temp->next = head, head = temp;
         else if(prev && cur)
           prev->next = temp, temp->next = cur;
         else if(!cur)
           prev->next = temp;
       }
     }
     void print() {
       node* temp = head;
       cout<<"[ ";
       while(temp->next) {
         cout<<temp->val<<", ";
         temp = temp->next;
       }
       if(temp)
         cout<<temp->val;
       cout<<"]"<<endl;
     }
};

int main() {
  linkedlist ll;
  ll.addSortedNode(3);
  ll.addSortedNode(1);
  ll.addSortedNode(2);
  ll.addSortedNode(4);
  ll.print();
  return 0;
}
