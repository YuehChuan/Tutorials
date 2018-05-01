#include <iostream>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 3

class BTree {
  private:
    struct node {
      int val;
      node* next;
      node(int v_) : val(v_), next(NULL) {};
    };
    struct block {
      node* head;
      block* up;
      block* down[MAX_SIZE];
      block(node* n_, block* b_) : up(b_), head(n_) {
        for(int i=0; i<MAX_SIZE; i++) { down[i] = NULL; }
      }
      const int insert(node* n) {
        int i = 0;
        node* prev = NULL;
        node* cur = head;
        while( (cur) && (n->val > cur->val) )
          prev = cur, cur = cur->next, i++;
        (prev) ? prev->next = n : head = n;
        n->next = cur;
        return i;
      }
      const int size() {
        int count = 0;
        node* n = head;
        while(n && ++count) { n = n->next; }
        return count;
      }
      const bool isLeaf() {
        for(int i=0;i<MAX_SIZE;i++)
          if(down[i])
            return false;
        return true;
      }
      node* splitOnMedian() {
        node* n = head;
        node* p = NULL;
        const int offset = (MAX_SIZE%2) ? (MAX_SIZE/2) : (MAX_SIZE/2-1);
        for(int i = 0; i<(offset); i++)
          p = n, n = n->next;
        p->next = NULL;
        return n;
      }
      void print() {
        std::cout<<"[ ";
        for(node* t=head;t;t=t->next)
          std::cout<<t->val<<" ";
        std::cout<<"] ";
      }
    };
    void assert(block* b, int level, int* ll) {
      //property 1: all leaf nodes must be same level
      if( (*b).isLeaf() && (*ll) == 0 )
        *ll = level;
      else if ( (*b).isLeaf() && (*ll) != level )
        std::cout<<"Property 1 error: leaf nodes must be same level."<<std::endl;

      //property 2: all blocks, except root, must have at least m/2-1 and no more than m-1 nodes
      if( b != root && ( (*b).size() < (MAX_SIZE/2-1) || (*b).size() > (MAX_SIZE-1) ) )
        std::cout<<"Property 2 error: block, except root, must have at least m/2-1 and at most m-1 nodes."<<std::endl;

      //property 3: all block that are not leaves and not the root (i.e. internal blocks) must have m/2 children.
      if( b != root && !(*b).isLeaf() ) {
        int childCount = 0;
        for(int i = 0; i<MAX_SIZE; i++)
          if(b->down[i])
            ++childCount;
        if( childCount < (MAX_SIZE/2) )
          std::cout<<"Property 3 error: internal blocks must have at least m/2 children."<<std::endl;
      }

      //property 4: if the root is not a leaf, the root must have at least two children
      if( b == root && !(*b).isLeaf() ) {
        int childCount = 0;
        for(int i = 0; i<MAX_SIZE; i++)
          if(b->down[i])
            ++childCount;
        if( childCount < 2 )
          std::cout<<"Property 4 error: if the root is no longer a leaf, the root must have at least two children."<<std::endl;
      }

      //property 5: a non-leaf block with n-1 nodes must have n children
      if( !(*b).isLeaf() ) {
        int cSize = (*b).size();
        int childCount = 0;
        for(int i = 0; i<MAX_SIZE; i++)
          if(b->down[i])
            ++childCount;
        if( (cSize + 1) != childCount )
          std::cout<<"Property 5 error: nonleaf blocks with n-1 nodes must have n children."<<std::endl;
      }

      //property 6: all values within a block must be in ascending order
      node* prev = NULL;
      node* cur = b->head;
      while(cur) {
        prev = cur, cur = cur->next;
        if( (cur) && (prev->val > cur->val) )
          std::cout<<"Property 6 error: all values within a block must be in ascending order"<<std::endl;
      }

      for(int i = 0; i<MAX_SIZE; i++)
        if(b->down[i])
          assert(b->down[i],(level+1),ll);

    }
    void print(block* b,node* n) {
      for(int i=0; i<MAX_SIZE; i++) {
        if(b->down[i])
          print(b->down[i],b->down[i]->head);
        if(n) {
          std::cout<<n->val<<" ";
          n = n->next;
        }
      }
    }
    /* search the b-tree for a given value, either the value is found and the function
     returns the block containing the given value, else the value is not found and
     the function returns the 'best fit' leaf. */
    block* search(int v_) {
      block* b = root;
      node* n = root->head;
      int i = 0;
      while( !(*b).isLeaf() ) {
        if( !n && b->down[i] )
         b = b->down[i], n = b->head, i = 0;
        else if(v_ == n->val)
          return b;
        else if(v_ < n->val)
          b = b->down[i], n = b->head, i = 0;
        else if(n)
          n = n->next, i++;
      }
      return b;
    }
    block* root;
  public:
    BTree() {
      root = NULL;
    }
    void print() {
      print(root,root->head);
      std::cout<<std::endl;
    }
    void assert() {
      int level = 0, ll = 0;
      assert(root,level,&ll);
    }
    void addNode(int v_) {
      if(!root)
        root = new block(new node(v_),NULL);
      else {
        block* b = search(v_);
        if( !(*b).isLeaf() )
          std::cout<<"Warning: value is already in the tree, OR search did not end at a leaf."<<std::endl;
        else {
          //apend new node onto leaf//
          node* n = new node(v_);
          (*b).insert(n);
          //split node//
          block* carry = NULL;
          while( (*b).size() >= MAX_SIZE ) {
            n = (*b).splitOnMedian();
            block* s = new block(n->next,b->up);
            n->next = NULL;
            if(carry) {
              const int offset = (MAX_SIZE%2 == 0) ? (MAX_SIZE/2) : (MAX_SIZE/2+1);
              for(int i=(offset); i<MAX_SIZE; i++) {
                s->down[i-(offset)] = b->down[i];
                s->down[i-(offset)]->up = s;
                b->down[i] = NULL;
              }
              s->down[(MAX_SIZE/2)] = carry;
              s->down[(MAX_SIZE/2)]->up = s;
              carry = NULL;
            }
            if( b == root ) {
              root = new block(n,NULL);
              root->down[0] = b, b->up = root;
              root->down[1] = s, s->up = root;
            }
            else {
              for(int i = (*b->up).insert(n) + 1; i<MAX_SIZE; i++) { //insert returns an int key //
                block* t = b->up->down[i];
                b->up->down[i] = s;
                s = t;
              }
              if(s)
                carry = s;
            }
            b = b->up;
          }
        }
      }
    }
};

int main() {
  BTree bt;
  srand(time(NULL));
  for(int i=1;i<500;i++) {
     bt.addNode(rand()%5000);
     bt.print();
     bt.assert();
     std::cout<<std::endl;
  }
  return 0;
}


