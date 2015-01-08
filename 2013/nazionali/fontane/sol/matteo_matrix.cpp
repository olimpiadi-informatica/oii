#include<cstdlib>
#include<iostream>
#include<fstream>

using namespace std;



#define MAX_N 105
#define MAX_X 1000
#define MAX_Y 1000

bool map[MAX_X+1][MAX_Y+1];

int N, M;

int xc[MAX_N];
int yc[MAX_N];

int main() {
  #ifdef EVAL
  ifstream in("input.txt");
  ofstream out("output.txt");
  #else
  istream &in(cin);
  ostream &out(cout);
  #endif
  in >> N >> M;
  for(int i=0;i<N+1;i++) {
    int a, b;
    in >> a;
    in >> b;
    xc[i] = a;
    yc[i] = b;
  }

  for(int i=0;i<M;i++) {
    int a, b;
    in >> a;
    in >> b;
    if(a <= MAX_X &&  b <= MAX_Y)
      map[a][b] = true;
  }

  int max_distance = 0;
  int cur_distance = 0;
  int x = xc[0], y = yc[0];
  for(int i=0;i<N;i++) {
    int delta_x=0, delta_y=0;
    if(xc[i]!=xc[i+1])
      delta_x = xc[i]<xc[i+1]?1:-1;
    if(yc[i]!=yc[i+1])
      delta_y = yc[i]<yc[i+1]?1:-1;
    while(x != xc[i+1] || y != yc[i+1]) {
      x += delta_x;
      y += delta_y;
      cur_distance++;
      max_distance = max(cur_distance, max_distance);
      if(map[x][y])
        cur_distance = 0;
    }
  }

  int res = max(0, max_distance-100);
  out << res << endl;
  return 0;
}
