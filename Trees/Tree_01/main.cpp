#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class BinaryTree {
  private:
    struct node {
      int val;
      node* left;
      node* right;
      node(int v_) : val(v_), left(NULL), right(NULL) {};
    };
    node* root;
    void print(node* temp) {
      if(temp->left)
        print(temp->left);
      cout<<temp->val<<" ";
      if(temp->right)
        print(temp->right);
    }
  public:
    void addNode(int v_) {
      if(!root)
        root = new node(v_);
      else {
        node* walker = root;
        while(walker) {
          if(v_ < walker->val) {
            if(walker->left)
              walker = walker->left;
            else {
              walker->left = new node(v_);
              walker = NULL;
            }
          }
          else {
            if(walker->right)
              walker = walker->right;
            else {
              walker->right = new node(v_);
              walker = NULL;
            }
          }
        }
      }
    }
    int findNodeCount(int v_) {
      int count = 0;
      node* walker = root;
      while(walker) {
        if(v_ == walker->val)
          return count;
        (v_ < walker->val) ? walker = walker->left : walker = walker->right;
        count++;
      }
      return -1;
    }
    void print() {
      cout<<"Printing binary tree:"<<endl<<"[ ";
      print(root);
      cout<<"]"<<endl;
    }
    /* Bonus function to remove nodes from the binary tree. */
    void removeNode(int v_) {
      node* walker = root;
      node* prev = walker;
      while(walker) {
        if(v_ == walker->val)
          break;
        prev = walker;
        (v_ < walker->val) ? walker = walker->left : walker = walker->right;
      }
      if(!walker)
        return;
      else {
        node* temp = walker;
        if(walker->right) {
          temp = walker->right;
          while(temp->left) {
            prev = temp;
            temp = temp->left;
          }
          if(temp == walker->right)
            walker->right = temp->right;
        }
        else if(walker->left) {
          temp = walker->left;
          while(temp->right) {
            prev = temp;
            temp = temp->right;
          }
          if(temp == walker->left)
            walker->left = temp->left;
        }
        if(prev->left == temp) {
          (temp->right) ? prev->left = temp->right : prev->left = NULL;
        }
        else if(prev->right == temp){
          (temp->left) ? prev->right = temp->left : prev->right = NULL;
        }
        walker->val = temp->val;
        delete temp;
      }
    }
    BinaryTree() { root = NULL; }
};

int main() {

  BinaryTree bt;
  bt.addNode(10);
  bt.addNode(20);
  bt.addNode(30);
  bt.addNode(25);
  bt.addNode(24);
  bt.addNode(21);
  bt.addNode(22);
  bt.addNode(23);

  bt.removeNode(20);
  bt.print();

/*
  srand(time(NULL));
  int randomNumberToFind;
  int randomPlacement = rand()%100000;
  BinaryTree bt;
  for(int i=0;i<100000;i++) {
    int randomNumber = 202*10000000+(rand()%900 + 100)*1000+rand()%9000+1000;
    if(i == randomPlacement)
      randomNumberToFind = randomNumber;
    bt.addNode(randomNumber);
  }
  bt.print();
  cout<<endl<<"Looking for "<<randomNumberToFind<<"..."<<endl;
  cout<<"Found after "<<bt.findNodeCount(randomNumberToFind)<<" traversals."<<endl;
*/
  return 0;
}
