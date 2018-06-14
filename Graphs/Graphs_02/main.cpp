#include <iostream>  //printing to console
#include <stdlib.h>  //generating randomness
#include <algorithm> //shuffling arrays
#include <time.h>    //make the random number random
#include <math.h>    //power function
#include <limits.h>  //max integers

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

//define a heuristic, a weighted distance//
float euclideanDistance(point a, point b) {
  return (pow( pow( a.x - b.x, 2.0) + pow( a.y - b.y, 2.0), 0.5 ));
}

//Define print, templated for int and float//
void print(int arr[HEIGHT][WIDTH]) {
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

/* Generate a maze using a depth first search and recursive stack.
   Randomly select a point's neighbor (L,R,U,D). Check boundary
   conditions At that point and check if there is a wall. If
   there is a wall convert that wall to a path. Note, move in increments of two.
*/
void randomMaze(int maze[HEIGHT][WIDTH], point p) {
  //define 2nd neighbors, then shuffle for randomness//
  point rn[4] = {
      point(p.x-2, p.y, direction::L),
      point(p.x+2, p.y, direction::R),
      point(p.x, p.y+2, direction::U),
      point(p.x, p.y-2, direction::D)
  };
  std::random_shuffle(&rn[0], &rn[4]);

  /* For all neighbors check if the neighbor point is a wall.
     If neighbor point is a wall, convert point to a path and add to stack. */
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

/* A* is a variation of Dijkstras algorithm.
   full explanation: http://www..... */
void astar(int maze[HEIGHT][WIDTH], point s, point g) {
  //define sets for distance and visited, and initialize sets//
  float dist[HEIGHT][WIDTH] = { 0 };
  bool visited[HEIGHT][WIDTH] = { 0 };
  for(int i=0; i<HEIGHT*WIDTH; i++) { dist[(int)floor(i/HEIGHT)][(i%WIDTH)] = INT_MAX; }

  //set current to starting point//
  point cur = s;
  dist[cur.y][cur.x] = euclideanDistance(s,g);

  //while current point is not at the goal//
  while( !(cur == g) ) {
    //update visited at current//
    visited[cur.y][cur.x] = 1;

    //neighbors//
    point nb[4] = {
      point(cur.x-1,cur.y),
      point(cur.x+1,cur.y),
      point(cur.x,cur.y-1),
      point(cur.x,cur.y+1)
    };

    //calculate distance at neighbors and possibly update.//
    for(point cn : nb )
      if( cn.inBounds() && maze[cn.y][cn.x] &&
        (euclideanDistance(cn,g) + dist[cur.y][cur.x] + maze[cn.y][cn.x] < dist[cn.y][cn.x]) )
          dist[cn.y][cn.x] = euclideanDistance(cn,g) + dist[cur.y][cur.x] + maze[cn.y][cn.x];

    //select the next point to be current//
    cur = point(-1,-1);
    float md = INT_MAX;
    for(int i=0; i<HEIGHT; i++)
      for(int j=0; j<WIDTH; j++)
        if(!visited[i][j] && dist[i][j]!=INT_MAX && dist[i][j] < md)
          cur = point(j,i), md = dist[i][j];
  }

  for(int i=0; i<HEIGHT*WIDTH; i++) { visited[(int)floor(i/HEIGHT)][(i%WIDTH)] = 0; }
  while( !(s == cur) ) {
    visited[cur.y][cur.x] = 1;
    maze[cur.y][cur.x] = -1;
    point nb[4] = {
      point(cur.x-1,cur.y),
      point(cur.x+1,cur.y),
      point(cur.x,cur.y-1),
      point(cur.x,cur.y+1)
    };
    float md = INT_MAX;
    for(point cn : nb) {
      if( cn.inBounds() && dist[cn.y][cn.x] < md && !visited[cn.y][cn.x] )
        md = dist[cn.y][cn.x], cur = cn;
    }
  }
  maze[cur.y][cur.x] = -1;
  print(maze);
}

int main() {
  srand(time(NULL));
  //generate a maze//
  int maze[HEIGHT][WIDTH] = { 0 };
  randomMaze(maze, point(rand()%WIDTH,rand()%HEIGHT) );
  //generate a start and goal point. Points must be on the path//
  point s,g;
  while( !(s.inBounds() && g.inBounds()) || !(maze[s.y][s.x] && maze[g.y][g.x])  ) {
    s = point(rand()%HEIGHT,rand()%WIDTH), g = point(rand()%HEIGHT,rand()%WIDTH);
  }

  std::cout<<"\nStarting from: ";
  s.print();
  std::cout<<"Going to: ";
  g.print();
  std::cout<<"\n";
  astar(maze,s,g);
  std::cout<<"\n";
  return 0;
}
