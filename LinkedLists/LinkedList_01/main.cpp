#include <iostream>

using namespace std;

class linkedlist {
  private:
    struct node {
      int val;
      node* next;
      node(int v_) : val(v_), next(NULL) {};
    };
    node* head;
  public:
    linkedlist () {
      head = NULL;
    }
    void addNode(int v_) {
      if(!head) {
        head = new node(v_);
      }
      else {
        node* temp = new node(v_);
        temp->next = head;
        head = temp;
      }
    }
    void printList() {
      node* temp = head;
      cout << "[ ";
      while(temp) {
        cout << temp->val << " ";
        temp = temp->next;
      }
      cout << "]\n";
    }
};

int main() {
  linkedlist ll;
  ll.addNode(3);
  ll.addNode(1);
  ll.addNode(2);
  ll.addNode(4);
  ll.printList();
  return 0;
}
