#include <iostream>
#include <stdlib.h>
#include <time.h>

class RedBlackTree {
  private:
    enum struct color { red, black };
    struct node {
      int val;
      color clr;
      node* up;
      node* left;
      node* right;
      node(int v_, node* u_) : val(v_), clr(color::red), up(u_), left(NULL), right(NULL) { };
    };
    node* root;
    node* sibling(node* n) {
      node* s = NULL;
      if(n!=root)
        s = (n->up->left == n) ? n->up->right : n->up->left;
      return s;
    }
    node* walkTree(node* walker, int v_) {
      node* prev = NULL;
      while(walker) {
        prev = walker;
        walker = (v_ < walker->val) ? walker->left : walker->right;
      }
      return prev;
    }
    void attachBase(node* g, node* cp) {
      cp->up = g->up;
      if (g->up)
        (g->up->left == g) ? g->up->left = cp : g->up->right = cp;
      else
        root = cp;
    }
    void rotateLL(node* c, node* p, node* g) {
      node* t3 = p->right;
      p->clr = color::black;
      g->clr = color::red;
      attachBase(g,p);
      p->right = g;
      g->up = p;
      g->left = t3;
      if(t3) { t3->up = g; }
    }
    void rotateRR(node* c, node* p, node* g) {
      node* t3 = p->left;
      p->clr = color::black;
      g->clr = color::red;
      attachBase(g,p);
      p->left = g;
      g->up = p;
      g->right = t3;
      if(t3) { t3->up = g; }
    }
    void rotateLR(node* c, node* p, node* g) {
      node* t2 = c->left;
      node* t3 = c->right;
      c->clr = color::black;
      g->clr = color::red;
      attachBase(g,c);
      c->left = p;
      p->up = c;
      c->right = g;
      g->up = c;
      p->right = t2;
      if(t2) { t2->up = p; }
      g->left = t3;
      if(t3) { t3->up = g; }
    }
    void rotateRL(node* c, node* p, node* g) {
      node* t2 = c->left;
      node* t3 = c->right;
      c->clr = color::black;
      g->clr = color::red;
      attachBase(g,c);
      c->left = g;
      g->up = c;
      c->right = p;
      p->up = c;
      g->right = t2;
      if(t2) { t2->up = g; }
      p->left = t3;
      if(t3) { t3->up = p; }
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
      node* w = root;
      int nodeCount = 0;
      while(w) {
        if(v_ ==  w->val)
          return nodeCount;
        else {
          w = (v_ < w->val) ? w->left : w->right;
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
        node* walker = walkTree(root,v_);
        node* c = (v_ < walker->val) ? walker->left = new node(v_,walker) : walker->right = new node(v_,walker);
        node* p = walker;
        node* g = walker->up;
        while(sibling(p) && sibling(p)->clr == color::red && p->clr==color::red) { //recolor//
          p->clr = color::black;
          sibling(p)->clr = color::black;
          if(g!=root) {
            g->clr = color::red;
            c = g, p = c->up, g = p->up;
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
