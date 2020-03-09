include util;

int N = 8;
real x,y;

griglia(N);
numeri(N);

pair inizio = ( 1, 1.5);
int[] percorso = {dx, dx, dx, dx, dw, dw, dw, dw, dw, dw, dw, dx, dx, dx};

string mappa = 
    "........" +
    ".......Y" +
    "........" +
    "........" +
    "........" +
    ".Y......" +
    "........" +
    "..Y.....";

for(int i=0; i<N; ++i)
for(int j=0; j<N; ++j)
{
    if( substr(mappa, i*8 + j, 1) == "." ) continue;

    x = (j)*GRID_SIZE + .15 ;
    y = (N-i-1)*GRID_SIZE;

    if( substr(mappa, i*8 + j, 1) == "X" )
        label(graphic("fire.png", "scale=.09"), (x,y), NE );
    else
        label(graphic("fire2.png", "scale=.09"), (x,y), NE );
}

label(graphic("school.png", "scale=.04"), (7*GRID_SIZE+.1, 0*GRID_SIZE), NE );
label(graphic("hotel.png", "scale=.19"), (0*GRID_SIZE+.1, 7*GRID_SIZE), NE );

corsa(N, percorso, penna_luce);
