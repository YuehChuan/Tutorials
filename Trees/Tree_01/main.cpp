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
        walker = (v_ < walker->val) ? walker->left : walker->right;
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
        walker = (v_ < walker->val) ? walker->left : walker->right;
      }
      if(!walker)
        return;
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
        prev->left = (temp->right) ? temp->right : NULL;
      }
      else if(prev->right == temp){
        prev->right = (temp->left) ? temp->left : NULL;
      }
      walker->val = temp->val;
      delete temp;
    }
    BinaryTree() { root = NULL; }
};

int main() {
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
  return 0;
}
