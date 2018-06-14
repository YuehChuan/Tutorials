#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

void printGraph(int graph[SIZE][SIZE]) {
  std::cout<<"Printing graph:\n";
  for(int i=0; i<SIZE; i++)
    std::cout<<"\t"<<i<<":";
  std::cout<<"\n";
  for(int i=0; i<SIZE; i++) {
    std::cout<<i<<":\t";
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

void dijkstrasAlgorithm(int graph[SIZE][SIZE], int cur) {

  //create arrays for distance and visited//
  int distance[SIZE];
  bool visited[SIZE];

  //initialize distance and visited to unreachable and unvisited//
  for(int i=0; i<SIZE; i++)
    distance[i] = INT_MAX, visited[i] = false;

  //at the starting node, set distance to zero//
  distance[cur] = 0;

  //iterate as long as a node is reachable and unvisited//
  while(cur!=-1) {

    //for neighbor nodes compare a tenative and assigned dist//
    for(int i=0; i<SIZE; i++)
      if((graph[cur][i]+distance[cur]<distance[i])&&graph[cur][i])
        distance[i] = graph[cur][i]+distance[cur];

    //mark the current node as visited, and find the next node//
    visited[cur] = true, cur = -1;
    int mindistance = INT_MAX;
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
  dijkstrasAlgorithm(graph,0);

  return 0;
  
}
