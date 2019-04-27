#include <iostream>

using namespace std;

class Queue {
  private:
    struct node {
      node* link;
      int value;
      node(int v_) : value(v_), link(NULL) {};
    };
    node* front;
    node* rear;
  public:
    void enqueue(int v_) {
      node* temp = new node(v_);
      if(!front) //case 1: the queue is empty.
        front = rear = temp;
      else { //case 2: the queue has nodes.
        temp->link = rear;
        rear = temp;
      }
    }
    void dequeue() {
      if(!front) {
        //case 1: the queue is empty, do nothing.
      }
      else if(front == rear) { //case 2: the queue has one node.
        node* t = front;
        front = rear = NULL;
        delete t;
      }
      else { //case 3: the queue has more than one node.
        node* t = front;
        node* s = rear;
        while( s->link != front )
          s = s->link;
        front = s; 
        s->link = NULL;
        delete t;
      }
    }
    void print() {
      cout<<"REAR -- ";
      node* t = rear;
      if(t) {
        while(t->link) {
          cout<<"[ "<<t->value<<" ] -> ";
          t = t->link;
        }
        cout<<"[ "<<t->value<<" ] -- FRONT\n\n";
      }
      else
        cout<<"[ ] -- FRONT\n\n";
    }
    Queue() {
      front = NULL;
      rear = NULL;
    }
};

int main() {
  Queue q;
  
  q.print(); //test empty queue
  
  q.enqueue(1); //test queue with one node//
  q.print();
  
  q.enqueue(2); //test queue with more than one node//
  q.print();
  
  q.dequeue(); //test dequeue to one node//
  q.print();
  
  q.enqueue(3);
  q.enqueue(4);  
  q.dequeue(); //test dequeue with more than one node//
  q.print();
  
  return 0;
}
