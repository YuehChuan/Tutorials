#include <iostream>  //printing to console
#include <stdlib.h>  //generating randomness
#include <algorithm> //shuffling arrays
#include <time.h>    //make the random number random
#include <math.h>    //power function
#include <limits.h>  //max integers
#include <vector>    //to store the path(s)

//define size of maze//
#define HEIGHT 25
#define WIDTH 25

//define directions left, right, up, and down//
enum struct direction {L,R,U,D};

//define a point, an {x,y} coordinate (and sometimes a direction)//
struct point {
  int x,y;
  direction d;
  point(int x_ = -1, int y_ = -1):x(x_),y(y_){};
  point(int x_, int y_, direction d_):x(x_),y(y_),d(d_){};
  bool inBounds() { return ( x>=0 && x<WIDTH && y>=0 && y<HEIGHT ) ? 1 : 0; }
  void print() { std::cout<<"{x: "<<x<<", y: "<<y<<"}\n"; };
  const bool operator==(const point& rhs) const { return ( x == rhs.x && y == rhs.y) ? 1 : 0; };
};

//define a heuristic//
float euclideanDistance(point a, point b) {
  return (pow( pow( a.x - b.x, 2.0) + pow( a.y - b.y, 2.0), 0.5 ));
}

//define a templated print//
template<class T>
void print(T arr[HEIGHT][WIDTH]) {
  for(int i=0; i<HEIGHT; i++) {
    for(int j=0; j<WIDTH; j++)
      std::cout<<arr[i][j];
    std::cout<<"\n";
  }
}

//overload print to display pretty mazes//
void print(int arr[HEIGHT][WIDTH], std::vector<point> path) {
  for(point p : path) { arr[p.y][p.x] = -1; }
  for(int i=0; i<HEIGHT+2; i++) {
    for(int j=0; j<WIDTH+2; j++) {
      if(!arr[i-1][j-1] || j == 0 || (j == WIDTH+1) || (i == 0) || (i == HEIGHT+1) )
        std::cout<<'|';
      else if (arr[i-1][j-1] == 1)
        std::cout<<' ';
      else if (arr[i-1][j-1] == -1)
        std::cout<<'.';
      else
        std::cout<<arr[i-1][j-1];
    }
    std::cout<<std::endl;
  }
}

//define random mazes using dfs and recursive stack//
void randomMaze(int maze[HEIGHT][WIDTH], point p) {
  //define 2nd neighbors, then shuffle for randomness//
  point rn[4] = {
      point(p.x-2, p.y, direction::L),
      point(p.x+2, p.y, direction::R),
      point(p.x, p.y+2, direction::U),
      point(p.x, p.y-2, direction::D)
  };
  std::random_shuffle(&rn[0], &rn[4]);

  /* For all 2nd degree neighbors, check if the neighbor is a wall
     If so, convert point to a path and add to stack */
  for(point cn : rn) {
    if(cn.inBounds() && !maze[cn.y][cn.x]) {
      if(cn.d == direction::L)
        maze[cn.y][cn.x+1] = 1;
      else if(cn.d == direction::R)
        maze[cn.y][cn.x-1] = 1;
      else if(cn.d == direction::U)
        maze[cn.y-1][cn.x] = 1;
      else if(cn.d == direction::D)
        maze[cn.y+1][cn.x] = 1;
      maze[cn.y][cn.x] = 1;
      randomMaze(maze, cn);
    }
  }
}

//A* a variation of Dijkstras algorithm//
std::vector<point> astar(int maze[HEIGHT][WIDTH], point s, point g) {
  //define sets for paths, distance, and visited//
  std::vector<point> paths[HEIGHT][WIDTH];
  float dist[HEIGHT][WIDTH] = { 0 };
  bool visited[HEIGHT][WIDTH] = { 0 };

  //initially all distances are INT_MAX (infinity)//
  for(int i=0; i<HEIGHT; i++)
    for(int j=0; j<WIDTH; j++)
      dist[i][j] = INT_MAX;

  //set current to starting point, calculate initial distance//
  point cur = s;
  dist[cur.y][cur.x] = euclideanDistance(s,g);

  //while current point is not at the goal//
  while( !(cur == g) ) {
    //update visited at current//
    visited[cur.y][cur.x] = 1;

    //neighboring points//
    point nb[4] = {
      point(cur.x-1,cur.y,direction::L),
      point(cur.x+1,cur.y,direction::R),
      point(cur.x,cur.y-1,direction::U),
      point(cur.x,cur.y+1,direction::D)
    };

    //calculate distance at neighbors and update distances if calculated distances are smaller//
    for(point cn : nb )
      if( cn.inBounds() && maze[cn.y][cn.x] &&
        (euclideanDistance(cn,g) + dist[cur.y][cur.x] + maze[cn.y][cn.x] < dist[cn.y][cn.x]) ) {
          dist[cn.y][cn.x] = euclideanDistance(cn,g) + dist[cur.y][cur.x] + maze[cn.y][cn.x];
          paths[cn.y][cn.x] = paths[cur.y][cur.x], paths[cn.y][cn.x].push_back(cur);
      }

    //select the next point to be current//
    cur = point(-1,-1);
    float md = INT_MAX;
    for(int i=0; i<HEIGHT; i++)
      for(int j=0; j<WIDTH; j++)
        if(!visited[i][j] && dist[i][j]!=INT_MAX && dist[i][j] < md)
          cur = point(j,i), md = dist[i][j];
  }

  //push the goal point to the path and return the path from start to goal//
  paths[g.y][g.x].push_back(g);
  return paths[g.y][g.x];

}

int main() {

  //seed random number generator//
  srand(time(NULL));

  //create random maze//
  int maze[HEIGHT][WIDTH] = { 0 };
  randomMaze(maze, point(rand()%WIDTH,rand()%HEIGHT) );

  //select random points//
  point s, g;
  while( !(s.inBounds() && g.inBounds()) || !(maze[s.y][s.x] && maze[g.y][g.x])  )
    s = point(rand()%HEIGHT,rand()%WIDTH), g = point(rand()%HEIGHT,rand()%WIDTH);

  //solve with a* algorithm//
  std::vector<point> path = astar(maze,s,g);

  //output maze in console//
  std::cout<<"\nStarting from: ";
  s.print();
  std::cout<<"Going to: ";
  g.print();
  std::cout<<"\n";
  print(maze,path);

  return 0;
}
