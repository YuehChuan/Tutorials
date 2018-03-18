#include <iostream>
#include <stdlib.h>
#include <time.h>

class RedBlackTree {
  private:
    enum struct color { red, black };
    struct node {
      int val;
      color clr;
      node* parent;
      node* left;
      node* right;
      node(int v_, node* p_) : val(v_), clr(color::red), parent(p_), left(NULL), right(NULL) { };
    };
    node* root;
    node* sibling(node* n) {
      node* t = NULL;
      if(n!=root) { t = (n->parent->left == n) ? n->parent->right : n->parent->left; }
      return t;
    }
    void attachBase(node* g, node* cp) {
      cp->parent = g->parent;
      if (g->parent)
        (g->parent->left == g) ? g->parent->left = cp : g->parent->right = cp;
      else
        root = cp;
    }
    void rotateLL(node* c, node* p, node* g) {
      node* t3 = p->right;
      p->clr = color::black;
      g->clr = color::red;
      attachBase(g,p);
      p->left = c;
      c->parent = p;
      p->right = g;
      g->parent = p;
      g->left = t3;
      if(t3) { t3->parent = g; }
    }
    void rotateRR(node* c, node* p, node* g) {
      node* t3 = p->left;
      p->clr = color::black;
      g->clr = color::red;
      attachBase(g,p);
      p->left = g;
      g->parent = p;
      p->right = c;
      c->parent = p;
      g->right = t3;
      if(t3) { t3->parent = g; }
    }
    void rotateLR(node* c, node* p, node* g) {
      node* t2 = c->left;
      node* t3 = c->right;
      c->clr = color::black;
      g->clr = color::red;
      attachBase(g,c);
      c->left = p;
      p->parent = c;
      c->right = g;
      g->parent = c;
      p->right = t2;
      if(t2) { t2->parent = p; }
      g->left = t3;
      if(t3) { t3->parent = g; }
    }
    void rotateRL(node* c, node* p, node* g) {
      node* t2 = c->left;
      node* t3 = c->right;
      c->clr = color::black;
      g->clr = color::red;
      attachBase(g,c);
      c->left = g;
      g->parent = c;
      c->right = p;
      p->parent = c;
      g->right = t2;
      if(t2) { t2->parent = g; }
      p->left = t3;
      if(t3) { t3->parent = p; }
    }
    void print(node* n) {
      if(n->left)
        print(n->left);
      std::cout<<n->val;
      (n->clr == color::black) ? std::cout<<"B " : std::cout<<"R ";
      if(n->right)
        print(n->right);
    }
    int assert(node* n) {
      int lh, rh;
      if(n == NULL) {
        return 1;
      }
      else {
        if(n->clr == color::red) {
          if( (n->left && n->left->clr == color::red) || (n->right && n->right->clr == color::red) ) {
            std::cout<<"RED violation: "<<root->val<<std::endl;
            return 0;
          }
        }
        lh = assert(n->left);
        rh = assert(n->right);
        if( (n->left && n->left->val > n->val) || (n->right && n->right->val < n->val) ) {
          std::cout<<"VALUE violation: "<<root->val<<std::endl;
          return 0;
        }
        if(lh != 0 && rh != 0 && lh != rh) {
          std::cout<<"BLACK violation: "<<root->val<<std::endl;
          return 0;
        }
        if(lh != 0 && rh != 0)
          return (n->clr == color::red) ? lh : lh + 1;
        else
          return 0;
      }
    }
  public:
    RedBlackTree() {
      root = NULL;
    }
    int findNodeCount(int v_) {
      node* walker = root;
      int nodeCount = 0;
      while(walker) {
        if(v_ ==  walker->val)
          return nodeCount;
        else {
          walker = (v_ < walker->val) ? walker->left : walker->right;
          nodeCount++;
        }
      }
      return -1;
    }
    void addNode(int v_) {
      if(!root) {
        root = new node(v_,NULL);
        root->clr = color::black;
      }
      else {
        node* walker = root;
        while(walker) {
          if(walker->left && v_ < walker->val)
            walker = walker->left;
          else if(walker->right && v_ >= walker->val)
            walker = walker->right;
          else {
            node* c = (v_ < walker->val) ? walker->left = new node(v_,walker) : walker->right = new node(v_,walker);
            node* p = walker;
            node* g = walker->parent;
            while(sibling(p) && sibling(p)->clr == color::red && p->clr==color::red) { //recolor//
              p->clr = color::black;
              sibling(p)->clr = color::black;
              if(g!=root) {
                g->clr = color::red;
                c = g, p = c->parent, g = p->parent;
              }
            }
            if(g && p->clr == color::red && (!sibling(p) || sibling(p)->clr == color::black)) { //restructure//
              if(g->left == p && p->left == c) {
                rotateLL(c,p,g);
              }
              else if(g->right == p && p->right == c) {
                rotateRR(c,p,g);
              }
              else if(g->left == p && p->right == c) {
                rotateLR(c,p,g);
              }
              else if(g->right == p && p->left == c) {
                rotateRL(c,p,g);
              }
            }
            walker = NULL;
          }
        }
      }
    }
    void print() {
      std::cout<<"Printing tree: "<<std::endl<<"[ ";
      print(root);
      std::cout<<" ]"<<std::endl;
    }
    int assert() {
      return assert(root);
    }
};

int main() {
  RedBlackTree rbt;
  srand(time(NULL));
  int randomNumberToFind;
  int randomPlacement = rand()%3000000;
  for(int i=0;i<3000000;i++) {
    int randomNumber = 202*10000000+(rand()%900 + 100)*1000+rand()%9000+1000;
    if(i == randomPlacement)
      randomNumberToFind = randomNumber;
    rbt.addNode(randomNumber);
  }
  std::cout<<std::endl<<"Looking for "<<randomNumberToFind<<"..."<<std::endl;
  std::cout<<"Found after "<<rbt.findNodeCount(randomNumberToFind)<<" traversals."<<std::endl;
  rbt.assert();
  return 0;
}
