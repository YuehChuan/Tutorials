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
    /* subroutines */
    node* sibling(node* n) {
      node* s = NULL;
      if(n!=root)
        s = (n->up->left == n) ? n->up->right : n->up->left;
      return s;
    }
    node* findNode(int v_) {
      node* f = root;
      while(f && f->val != v_)
        f = (v_ < f->val) ? f->left : f->right;
      return f;
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
    node* inorderSuccessor(node* ntr) {
      if(ntr->right) {
        ntr = ntr->right;
        while(ntr->left)
          ntr = ntr->left;
      }
      else if(ntr->left)
         ntr = ntr->left;
      return ntr;
    }
    /* rotations (add subroutines) */
    void rotateLL(node* c, node* p, node* g) {
      node* t3 = p->right;
      p->clr = color::black;
      g->clr = color::red;
      attachBase(g,p);
      p->right = g;
      g->up = p;
      g->left = t3;
      if(t3)
        t3->up = g;
    }
    void rotateRR(node* c, node* p, node* g) {
      node* t3 = p->left;
      p->clr = color::black;
      g->clr = color::red;
      attachBase(g,p);
      p->left = g;
      g->up = p;
      g->right = t3;
      if(t3)
        t3->up = g;
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
      if(t2)
        t2->up = p;
      g->left = t3;
      if(t3)
        t3->up = g;
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
      if(t2)
        t2->up = g;
      p->left = t3;
      if(t3)
        t3->up = p;
    }
    /* print */
    char printColor(node* n) {
      char c;
      (n->clr == color::black) ? c = 'B' : c = 'R';
      return c;
    }
    void printCluster(node* n) { //prints a node, parent, sibling, and sibling children....to be used while debugging removal cases.
      node* s = sibling(n);
      node* p = n->up;
      node* sl = NULL;
      node* sr = NULL;
      if(s) {
        sl = s->left;
        sr = s->right;
      }
      std::cout<<"Cluster: {";
      std::cout<<"n: "<<n->val<<printColor(n)<<", ";
      (p) ? std::cout<<"p: "<<p->val<<printColor(p)<<", " : std::cout<<"p: NULL, ";
      (s) ? std::cout<<"s: "<<s->val<<printColor(s) : std::cout<<"s: NULL, ";
      (s && p->right==s) ? std::cout<<" Right, " : std::cout<<" Left, ";
      (sl) ? std::cout<<"sl: "<<sl->val<<printColor(sl)<<", " : std::cout<<"sl: NULL, ";
      (sr) ? std::cout<<"sr: "<<sr->val<<printColor(sr)<<"}" : std::cout<<"sr: NULL}";
      std::cout<<std::endl;
    }
    void print(node* n) {
      if(n->left)
        print(n->left);
      std::cout<<n->val<<printColor(n)<<" ";
      if(n->right)
        print(n->right);
    }
    /* assertion */
    int assert(node* n, node* p) {
      int lh, rh;
      if(n == NULL) {
        return 1;
      }
      else {
        if(n->up != p) {
          std::cout<<std::endl<<"POINTER violation: child does not point to parent."<<std::endl;
          std::cin.get();
        }
        if(n->clr == color::red) {
          if( (n->left && n->left->clr == color::red) || (n->right && n->right->clr == color::red) ) {
            std::cout<<"RED violation: "<<root->val<<std::endl;
            std::cin.get();
            return 0;
          }
        }
        lh = assert(n->left, n);
        rh = assert(n->right, n);
        if( (n->left && n->left->val > n->val) || (n->right && n->right->val < n->val) ) {
          std::cout<<"VALUE violation: "<<root->val<<std::endl;
          std::cin.get();
          return 0;
        }
        if(lh != 0 && rh != 0 && lh != rh) {
          std::cout<<"BLACK violation: "<<root->val<<std::endl;
          std::cin.get();
          return 0;
        }
        if(lh != 0 && rh != 0)
          return (n->clr == color::red) ? lh : lh + 1;
        else
          return 0;
      }
    }
    /* deletion */
    /* ||delete case 1||
       Situation: check if node is the root
       Resolution: if node is not the root proceed to case 2. *Termination case (1/3). */
    void delete_case1(node* n, node* s, node* p) {
      if(n!=root)
        delete_case2(n,s,p);
    }
    /* ||delete case 2||
       Situation: sibling is red, sibilng children are black or null, parent is black
       Resolution: single rotation left or right (according to sibling relation to parent), then paint parent red and sibling black.
    */
    void delete_case2(node* n, node* s, node* p) {
      if( (s->clr == color::red) &&
          (p->clr == color::black) &&
          !(s->right && s->right->clr == color::red) &&
          !(s->left && s->left->clr == color::red) ) {
        attachBase(p,s);
        p->clr = color::red;
        s->clr = color::black;
        if(p->right == s) {
          p->right = s->left;
          if(s->left)
            s->left->up = p;
          s->left = p;
        }
        else if(p->left == s) {
          p->left = s->right;
          if(s->right)
            s->right->up = p;
          s->right = p;
        }
        p->up = s;
      }
      delete_case3(n,sibling(n),p); //because of rotation, n's sibling can rotate to become the left or right child of sibling.
    }
    /* ||delete case 3||
       Situation: parent and sibling are black. Sibling's children are either black or null.
       Resolve: repaint the sibling red, and start deletion case 1 with parent. Otherwise, move to deletion case 4.
    */
    void delete_case3(node* n, node* s, node* p) {
      if( (p->clr == color::black) &&
          (s->clr == color::black) &&
          !(s->right && s->right->clr == color::red) &&
          !(s->left && s->left->clr == color::red) ) {
        s->clr = color::red;
        delete_case1(p,sibling(p),p->up);
      }
      else
        delete_case4(n,s,p);
    }
    /* ||delete case 4||
       Situation: parent is red, the sibling is black, and the children are either black or null.
       Resolve: repaint the sibling red, and the parent black. *termination case (2/3).
    */
    void delete_case4(node* n, node* s, node* p) {
      if( (p->clr == color::red) &&
          (s->clr == color::black) &&
          !(s->left && s->left->clr == color::red)  &&
          !(s->right && s->right->clr == color::red) ) {
        s->clr = color::red;
        p->clr = color::black;
      }
      else {
        delete_case5(n,s,p);
      }
    }
    /* ||delete case 5||
       Situation: sibling is black, the sibling is to the right of the parent, and the sibling's left child is red. OR the...
         sibling is to the left of the parent, and the sibling's right child is red.
       Resolve: rotation amongst the sibling and sibling's children cluster (either left or right), and then repaint the sibling's child..
         that was red to black, and the sibling from black to red.
    */
    void delete_case5(node* n, node* s, node* p) {
      if(s->clr == color::black) {
        if( (s->left && s->left->clr == color::red) &&
            !(s->right && s->right->clr == color::red) &&
            (p->right == s) ) {
          node* sl = s->left;
          node* slr = sl->right; //reattach sibling's left right node to sibling left
          p->right = sl;
          sl->up = p;
          sl->right = s;
          s->up = sl;
          s->left = slr;
          if(slr)
            slr->up = s;
          sl->clr = color::black;
          s->clr = color::red;
        }
        else if( (s->right && s->right->clr == color::red) &&
                 !(s->left && s->left->clr == color::red) &&
                 (p->left == s) ) {
          node* sr = s->right;
          node* srl = sr->left;  //reattach sibling's right left node to sibling right
          p->left = sr;
          sr->up = p;
          sr->left = s;
          s->up = sr;
          s->right = srl;
          if(srl)
            srl->up = s;
          sr->clr = color::black;
          s->clr = color::red;
        }
      }
      delete_case6(n,sibling(n),p);//because of rotation pass in sibling(n)**
    }
    /* ||delete case 6||
       Situation: sibling is black, sibling is to the right of the parent, and the sibling's right child is red. OR...
         sibling is to the left of the parent, and the sibling's left child is red.
       Resolve: rotate, repaint sibling's child from red to black, repaint the sibling to the color of the parent,
         and the parent to black. *termination case (3/3).
    */
    void delete_case6(node* n, node* s, node* p) {
      node* sl = s->left;
      node* sr = s->right;
      if( (p->right == s) &&
          (s->clr == color::black) &&
          (s->right && s->right->clr == color::red) ) {
        s->clr = p->clr;
        p->clr = color::black;
        attachBase(p,s);
        s->left = p;
        p->up = s;
        p->right = sl;
        if(sl)
          sl->up = p;
        if(sr)
          sr->clr = color::black;
      }
      else if( (p->left == s) &&
               (s->clr == color::black) &&
               (s->left && s->left->clr == color::red) ) {
        s->clr = p->clr;
        p->clr = color::black;
        attachBase(p,s);
        s->right = p;
        p->up = s;
        p->left = sr;
        if(sr)
          sr->up = p;
        if(sl)
          sl->clr = color::black;
      }
    }
  public:
    RedBlackTree() {
      root = NULL;
    }
    void print() {
      std::cout<<"Printing tree: "<<std::endl<<"[ ";
      print(root);
      std::cout<<" ]"<<std::endl;
    }
    int assert() {
      return assert(root,NULL);
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
          if(g->left == p && p->left == c)
            rotateLL(c,p,g);
           else if(g->right == p && p->right == c)
             rotateRR(c,p,g);
           else if(g->left == p && p->right == c)
             rotateLR(c,p,g);
           else if(g->right == p && p->left == c)
             rotateRL(c,p,g);
        }
      }
    }
    void removeNode(int v_) {
      node* ntr = findNode(v_);
      if(!ntr)
        return;
      node* ios = inorderSuccessor(ntr);
      ntr->val = ios->val;
      if(ios->clr == color::black) {
        if(ios->right && ios->right->clr == color::red) { //ios has the at most one child.//
          ios->val = ios->right->val;
          ios = ios->right;
        }
        else
          delete_case1(ios,sibling(ios),ios->up);
      }
      if(ios == root)
         root = NULL;
      else
         (ios->up->left == ios) ? ios->up->left = NULL : ios->up->right = NULL;
      delete ios;
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
