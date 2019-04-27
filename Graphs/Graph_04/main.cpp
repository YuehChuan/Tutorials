#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stdlib.h>

using namespace std;

struct node {
  string page;
  set<node*> links;
  float pr;
  node(string p_) : page(p_), pr(0) {};
  node(string p_, set<node*> l_) : page(p_), links(l_), pr(0) {};
  void print() {
    cout<<page<<",\t ";
    cout<<pr<<",\t links: { ";
    for(auto l : links)
      cout<<l->page<<" ";
    cout<<"}\n";
  }
};

class graph {
  private:
    set<node*> g;
  public:
    void addNode(string p_) {
      node* n = new node(p_);
      g.insert(n);
    }
    void addEdge(string p1_, string p2_) {
      node* n1 = NULL, *n2 = NULL;
      for(auto p : g) {
        if(p->page == p1_) { n1 = p; }
        else if(p->page == p2_) { n2 = p; }
      }
      //Note, links are now directed//
      if(n1 && n2)
        n1->links.insert(n2);
    }
    set<node*> getUniverse() {
      return g;
    }
    void print() {
      for(auto p : g)
        (*p).print();
    }
};

void pageRank(graph g) {
  set<node*> u = g.getUniverse();

  //map to hold future page rank//
  map<node*, float> m;

  int N = u.size();
  float d = 0.85;
  float rp = (float)(1-d)/N;
  float me = 0.09;

  for(auto p : u) { (*p).pr = (float)1/N; }

  bool cf = true;
  while(cf) {
    m.clear();

    float S = 0;
    for(auto p : u)
      if( (*p).links.empty() )
        S += (float)(d*p->pr)/N;

    for(auto p : u)
      for(auto l : (*p).links)
        m[l] += (float)p->pr/(*p).links.size();

    cf = false;
    for(auto p : u) {
      m[p] = rp + S + d*m[p];
      if( abs(m[p] - (*p).pr) > me )
        cf = true;
      (*p).pr = m[p];
    }
  }

}

int main() {
  graph g;
  string pages[5] = {"Mspc","Twtr","Amzn","Medm","Fb"};
  for(auto p : pages)
    g.addNode(p);

  g.addEdge("Mspc","Twtr");
  g.addEdge("Twtr","Medm");
  g.addEdge("Amzn","Twtr");
  g.addEdge("Amzn","Medm");
  g.addEdge("Medm","Twtr");
  g.addEdge("Medm","Mspc");
  g.addEdge("Medm","Amzn");
  g.addEdge("Medm","Fb");
  g.addEdge("Fb","Twtr");
  g.addEdge("Fb","Amzn");

  pageRank(g);

  g.print();

  return 0;
}
