
#include <iostream>

using namespace std;

class Heap {

  private:
    int* tree;
    int max_size, size;

    void grow_tree() {
      max_size = max_size << 1 | 1;
      int* prev_tree = tree;
      tree = new int[max_size];
      for(int i=0; i<size; i++)
        tree[i] = prev_tree[i];
      delete[] prev_tree;
    }

    void swap(const int& i, const int& j) {
      const int temp_val = tree[i];
      tree[i] = tree[j];
      tree[j] = temp_val;
    }

    const int parent(const int& child) {
      return ( (child - 1)/2 );
    }

    const int left_child(const int& parent) {
      return ( parent*2 + 1 );
    }

    const int right_child(const int& parent) {
      return ( parent*2 + 2 );
    }

    void upHeap(const int child) {
      const int root = 0;
      if( child == root )
        return;
      else if( tree[child] > tree[parent(child)] ) {
        swap( child, parent(child) );
        upHeap( parent(child) );
      }
    }

    void downHeap(const int parent) {
      if( right_child(parent) >= size )
        return;
      int temp = parent;

      if( tree[temp] < tree[left_child(parent)] )
        temp = left_child(parent);

      if( tree[temp] < tree[right_child(parent)] )
        temp = right_child(parent);

      if( temp != parent ) {
        swap( parent, temp );
        downHeap(temp);
      }

    }

  public:
    Heap() : max_size(1), size(0), tree(new int[1]) {};

    void print() {
      cout<<"Heap:[ ";
      for(int i=0; i<size; i++)
        cout<<tree[i]<<" ";
      cout<<"]\n";
    }

    void insert(const int val) {
      if( size == max_size )
        grow_tree();
      tree[size] = val;
      upHeap(size++);
    }

    void remove() {
      const int root = 0;
      if( size == root )
        return;
      swap(root, --size);
      downHeap(root);
    }
};

int main() {
  Heap h;
  cout<<"Adding nodes to heap.\n";
  h.insert(5);
  h.print();
  h.insert(4);
  h.print();
  h.insert(3);
  h.print();
  h.insert(2);
  h.print();
  h.insert(1);
  h.print();
  h.insert(0);
  h.print();
  h.insert(7);
  h.print();
  cout<<"\nRemoving node(s) from heap.\n";
  h.remove();
  h.print();

  return 0;
}
