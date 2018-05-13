#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15

void printGraph(int graph[SIZE][SIZE]) {
  std::cout<<"Printing graph:\n";
  for(int i=0; i<SIZE; i++)
    std::cout<<"\t"<<i;
  std::cout<<"\n";
  for(int i=0; i<SIZE; i++) {
    std::cout<<i<<"\t";
    for(int j=0; j<SIZE; j++)
        std::cout<<graph[i][j]<<"\t";
    std::cout<<"\n";
  }
  std::cout<<"\n";
}

void printDistance(int distance[SIZE]) {
  std::cout<<"Printing distance:\n";
  for(int i=0; i<SIZE; i++) {
    std::cout<<"[i: "<<i<<", d: ";
    (distance[i]!=INT_MAX) ? std::cout<<distance[i] : std::cout<<-1;
    std::cout<<"]\n";
  }
}

void dijkstraDistance(int graph[SIZE][SIZE], int cur) {
  int distance[SIZE];
  bool visited[SIZE];
  int mindistance;
  for(int i=0; i<SIZE; i++)
    distance[i] = INT_MAX, visited[i] = false;

  distance[cur] = 0;

  while(cur!=-1) {
    for(int i=0; i<SIZE; i++)
      distance[i] = (graph[cur][i] && (graph[cur][i]+distance[cur] < distance[i])) ? graph[cur][i]+distance[cur] : distance[i];

    visited[cur] = true, cur = -1, mindistance = INT_MAX;
    for(int i=0; i<SIZE; i++)
      if(!visited[i] && (distance[i] < mindistance))
        cur = i, mindistance = distance[i];
  }

  printDistance(distance);

}

int main() {

  int graph[SIZE][SIZE] = { 0 };
  srand(time(NULL));
  for(int i=0; i<SIZE; i++)
    for(int j=0; j<i; j++)
      graph[j][i] = graph[i][j] = (rand()%SIZE == (j || i) ) ? 0 : rand()%500;

  printGraph(graph);
  dijkstraDistance(graph,0);

  return 0;
}
