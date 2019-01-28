#include <iostream>

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

    void print(node* n) {
      if(n->left)
        print(n->left);
      cout<<n->val<<" ";
      if(n->right)
        print(n->right);
    }

    void clear(node* n) {
      if(n->left)
        clear(n->left);
      if(n->right)
        clear(n->right);
      delete n;
    }

    int find_diameter(node* n, int& dmtr) {

      if(!n)
        return 0;

      int left = find_diameter(n->left, dmtr);
      int right = find_diameter(n->right, dmtr);

      if(left + right > dmtr)
        dmtr = left + right;

      if(left > right)
        return 1 + left;
      else
        return 1 + right;

    }

  public:

    BinaryTree() {
      root = NULL;
    }

    void print() {
      cout<<"[ ";
      print(root);
      cout<<"]\n";
    }

    void clear() {
      clear(root);
    }

    int diameter() {
      int sol = 0;
      find_diameter(root, sol);
      return sol;
    }

    void add(int val) {
      if(!root)
        root = new node(val);
      else {

        node* cur = root;
        node* prev = root;

        while(cur) {
          prev = cur;
          if(val < cur->val) {
            cur = cur->left;
            if(!cur)
              prev->left = new node(val);
          }
          else {
            cur = cur->right;
            if(!cur)
              prev->right = new node(val);
          }
        }
      }
    }
};

int main() {

  BinaryTree bt;

  int test_01[11] = {100, 150, 50, 75, 125, 74, 73, 76, 124, 130, 131};
  int test_02[23] = {100, 50, 150, 25, 75, 125, 175, 12, 70, 78, 123, 128, 225, 5, 65, 73, 79, 122, 126, 129, 250, 0, 275};
  int test_03[9] = {100, 75, 125, 50, 87, 112, 150, 25, 175};
  int test_04[9] = {100, 125, 75, 80, 85, 90, 70, 65, 60};

  cout<<"\nTest 01:\n";
  for(int i = 0; i<11; i++)
    bt.add(test_01[i]);
  bt.print();
  cout<<"Diameter: "<<bt.diameter()<<"\n\n";
  bt.clear();

  cout<<"Test 02:\n";
  for(int i = 0; i<23; i++)
    bt.add(test_02[i]);
  bt.print();
  cout<<"Diameter: "<<bt.diameter()<<"\n\n";
  bt.clear();

  cout<<"Test 03:\n";
  for(int i = 0; i<9; i++)
    bt.add(test_03[i]);
  bt.print();
  cout<<"Diameter: "<<bt.diameter()<<"\n\n";
  bt.clear();

  cout<<"Test 04:\n";
  for(int i = 0; i<9; i++)
    bt.add(test_04[i]);
  bt.print();
  cout<<"Diameter: "<<bt.diameter()<<"\n\n";
  bt.clear();

  return 0;
}
