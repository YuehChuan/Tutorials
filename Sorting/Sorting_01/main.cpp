#include <iostream>

using namespace std;

void print(int* data, const int& size) {
  cout<<"[ ";
  for(int i=0; i<size; i++)
    cout<<data[i]<<" ";
  cout<<"]\n";
}

int sort(int* data, int low, int high) {
  int pivot = high--;
  while( low <= high ) {
    if( data[low] > data[pivot] )
      swap(data[low], data[high--]);
    else
      low++;
  }
  swap(data[low], data[pivot]);
  return low;
}

void quicksort(int* data, int low, int high) {
  if( low < high ) {
    int pivot = sort(data, low, high);
    quicksort(data, low, pivot-1);
    quicksort(data, pivot+1, high);
  }
}

int main() {

  int size = 6;
  int data[size] = {2, 6, 5, 1, 4, 3};

  print(data, size);

  quicksort(data, 0, size-1);

  print(data, size);

  return 0;
}
