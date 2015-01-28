/*
    VERSIONE POCO TESTATA
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cassert>

using namespace std;

#define MAX_P 1000010
int n,p,m;
int x0,y0;

class coord
{
    public:
        int x,y;
        coord()
        {
            coord(1,1);
        }
        coord(int a, int b)
        {
            x=a;
            y=b;
        }
};

bool operator<(const coord &a,const coord &b)
{
  if(a.x<b.x || (a.x==b.x && a.y<=b.y))
    return true;
  return false;
}

coord pescosi[MAX_P];
int esclusi;
bool puntiesclusi[MAX_P];

void percorri()
{
    int currp;

    //parti dal primo punto pescoso plausibile, intanto
    for(currp=0;currp<p && pescosi[currp].x<x0;currp++)
       puntiesclusi[currp]=true;

    //leggi e scarta
    int direction = -1;
    int xcurr=x0,ycurr=y0,y_lim=y0;
    for(;;)
    {
        int action, compressed_action;
        assert(scanf("%d",&compressed_action) == 1);
	if (compressed_action == 0) {
	  break;
	}

	if (direction == -1) {
	  if (compressed_action > 0) {
	    direction = 0;
	  } else {
	    direction = 1;
	  }
	}

	while (compressed_action != 0) {
	  if (compressed_action > 0) {
	    --compressed_action;
	    action = 0;
	  } else {
	    ++compressed_action;
	    action = 1;
	  }

	  //va a nord?
	  if(action==0)
	    {
	      ycurr++;
	      if(direction==0)
                y_lim=ycurr;
	    }
	  //va ad est?
	  else
	    {
	      //cerchiamo di escludere i punti fuori dalla figura
	      for(;pescosi[currp].x==xcurr;currp++)
		{
		  if(direction==0 && pescosi[currp].y>y_lim)
                    puntiesclusi[currp]=true;
		  if(direction==1 && pescosi[currp].y<y_lim)
                    puntiesclusi[currp]=true;
		}
	      xcurr++;
	      y_lim=ycurr;
	    }
	}
    }
	
    for(;pescosi[currp].x==xcurr;currp++)
    {
        if(direction==0 && pescosi[currp].y>y_lim)
            puntiesclusi[currp]=true;
        if(direction==1 && pescosi[currp].y<y_lim)
            puntiesclusi[currp]=true;
    }
    //ultimo ciclo per la eliminazione dei pescosi rimasti
    for(;currp<p;currp++)
        puntiesclusi[currp]=true;
}



int main()
{
    assert(scanf("%d",&p) == 1);
    assert(scanf("%d %d",&x0,&y0) == 2);
    for(int i=0;i<p;i++)
    {
       assert(scanf("%d %d",&pescosi[i].x,&pescosi[i].y) == 2);
    }
    sort(pescosi,pescosi+p);
    
    //ricerca di minimi e massimi
    percorri();
    percorri();
    
    for(int i=0;i<p;i++)
    {
        if(puntiesclusi[i]) esclusi++;
    }
    //ricerca dei punti pescosi inclusi
    printf("%d\n",p-esclusi);
}
