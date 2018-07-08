#include <iostream>
#include <stdlib.h>

using namespace std;

class doublylinkedlist {
  private:
    struct node {
      int val;
      node* next;
      node* prev;
      node(int v_) : val(v_),next(NULL),prev(NULL) {};
    };
    node* head;
    node* tail;
  public:
    doublylinkedlist() {
      head = NULL;
      tail = NULL;
    }
    void printFromHead() {
      node* temp = head;
      cout<<"[ ";
      while(temp) {
        cout<<temp->val<<" ";
        temp = temp->next;
      }
      cout<<"]"<<endl;
    }
    void printFromTail() {
       node* temp = tail;
       cout<<"[ ";
       while(temp) {
         cout<<temp->val<<" ";
         temp = temp->prev;
       }
       cout<<"]"<<endl;
    }
    void addFromHead(int v_) {
      if(head == NULL && tail == NULL) {
        head = new node(v_);
        tail = head;
      }
      else {
        node* cur = head;
        while(cur && v_ > cur->val) {
          cur = cur->next;
        }
        if(cur == head) {
          cur->prev = new node(v_);
          cur->prev->next = head;
          head = cur->prev;
        }
        else if(cur) {
          cur->prev->next = new node(v_);
          cur->prev->next->next = cur;
          cur->prev->next->prev = cur->prev;
          cur->prev = cur->prev->next;
        }
        else if(!cur) {
          tail->next = new node(v_);
          tail->next->prev = tail;
          tail = tail->next;
        }
      }
    }
    void addFromTail(int v_) {
      if(head == NULL && tail == NULL) {
        tail = new node(v_);
        head = head;
      }
      else {
        node* cur = tail;
        while(cur && v_ <= cur->val) {
          cur = cur->prev;
        }
        if(cur == tail) {
          cur->next = new node(v_);
          cur->next->prev = tail;
          tail = cur->next;
        }
        else if(cur) {
          cur->next->prev = new node(v_);
          cur->next->prev->prev = cur;
          cur->next->prev->next = cur->next;
          cur->next = cur->next->prev;
        }
        else if(!cur) {
          head->prev = new node(v_);
          head->prev->next = head;
          head = head->prev;
        }
      }
    }
};

int main() {
  doublylinkedlist dll;
  dll.addFromHead(3);
  dll.addFromHead(1);
  dll.addFromHead(2);
  dll.addFromHead(4);
  dll.printFromHead();
  dll.printFromTail();
  return 0;
}
