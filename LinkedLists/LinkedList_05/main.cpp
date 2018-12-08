#include <iostream>

using namespace std;

class Stack {

  private:
    struct node {
      int value;
      node* link;
      node(int v_) : value(v_), link(NULL) {};
    };

    node* top;

  public:
    void push(int v_) {
      if(!top)
        top = new node(v_);
      else {
        node* temp = new node(v_);
        temp->link = top;
        top = temp;
      }
    }

    void pop() {
      if(top) {
        node* temp = top;
        top = top->link;
        delete temp;
      }
    }

    const int peek() {
      if(top)
        return top->value;
    }

    void print() {
      if(top) {
        cout<<"TOP -- ";
        node* temp = top;
        while(temp->link) {
          cout<<"["<<temp->value<<"] -> ";
          temp = temp->link;
        }
        cout<<"["<<temp->value<<"]\n";
      }
      else
        cout<<"TOP -- []\n";
    }

    Stack() {
      top = NULL;
    }

};

int main() {
  Stack s;
  s.print();


  s.push(1);
  cout<<"**PUSH**\n";
  s.print();

  s.push(2);
  cout<<"**PUSH**\n";
  s.print();

  s.pop();
  cout<<"**POP**\n";
  s.print();

  s.push(3);
  cout<<"**PUSH**\n";
  s.print();

  s.push(4);
  cout<<"**PUSH**\n";
  s.print();

  s.pop();
  cout<<"**POP**\n";
  s.print();

  s.pop();
  cout<<"**POP**\n";
  s.print();

  s.pop();
  cout<<"**POP**\n";
  s.print();

  return 0;

}
