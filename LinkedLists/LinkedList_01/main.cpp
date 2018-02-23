
#include <iostream>

using namespace std;

class linkedlist {
  public:
      struct node {
        int date;
        string description;
        node* next;
        node(int dt_, string desc_ ) : date(dt_), description(desc_), next(NULL) {};
      };

      node* head;

      linkedlist () {
        head = NULL;
      }

      void addNode(int dt_, string desc_) {
        if(!head) {
          head = new node(dt_, desc_);
        }
        else {
          node* temp = new node(dt_, desc_);
          temp->next = head;
          head = temp;
        }
      }

      void printList() {
        node* temp = head;
        while(temp) {
          cout << temp->date << endl;
          cout << temp->description << endl;
          temp = temp->next;
        }
      }

      void sortList() {
        node* temp = head;
        //start from the head of the list and start sorting//
        while(temp) {
          //set the runner and smallest to the temp node//
          node* runner = temp;
          node* smallest = temp;
          //find the smallest node that is left in the list//
          while(runner) {
            if(runner->date < smallest->date) {
              smallest = runner;
            }
            runner = runner->next;
          }
          //swap the values//
          int dt_ = temp->date;
          string desc_ = temp->description;
          temp->date = smallest->date;
          temp->description = smallest->description;
          smallest->date = dt_;
          smallest->description = desc_;
          //move to the next node on the list//
          temp = temp->next;
        }
      }

      void removeNode(int dt_) {
        node* temp = head;
        if(temp->date == dt_) {
          head = head->next;
          delete temp;
        }
        else {
          node* prev = temp;
          while(temp && temp->date != dt_) {
            prev = temp;
            temp = temp->next;
          }
          if(temp) {
            prev->next = temp->next;
            delete temp;
          }
        }
      }
};


int main() {
    
    linkedlist ll;
    ll.addNode(20181201,"Demo 1");
    ll.addNode(20171230,"Demo 2");
    ll.addNode(20180601,"Demo 3");
    ll.addNode(20170603,"Demo 4");
    cout<<"PRINTING INPUT:"<<endl;
    ll.printList();
    
    cout<<"PRINTING SORTED INPUT:"<<endl;
    ll.sortList();
    ll.printList();
    
    cout<<"PRINTING LIST AFTER HEAD NODE REMOVED"<<endl;
    ll.removeNode(20170603); 
    ll.printList();
    
    cout<<"PRINTING LIST AFTER ANOTHER NODE REMOVED"<<endl;
    ll.removeNode(20180601);
    ll.printList();
    
    return 0;

}
