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
    int findNode(int v_) {
      int traversalCount = 0;
      node* walker = root;
      while(walker) {
        if(v_ == walker->val) {
          return traversalCount;
        }
        (v_ < walker->val) ? walker = walker->left : walker = walker->right;
        traversalCount++;
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
        if(prev->left == temp)
          prev->left = NULL;
        else if(prev->right == temp)
          prev->right = NULL;
        walker->val = temp->val;
        delete temp;
      }
    }
};

int main() {
  srand(time(NULL));
  BinaryTree bt;
  for(int i=0;i<100000;i++) {
    bt.addNode(rand()%9999999999);
  }
  bt.addNode(2024561111);
  bt.print();
  cout<<"It took "<<bt.findNode(2024561111)<<" traversals to find the desired phone number."<<endl;
  return 0;
}
