unitsize(1cm);
include roundedpath;
include math;
settings.tex = "pdflatex";


path coast = (-1.3,-1 ) .. (-0.5,-1) .. (0,-1) .. (1,-1.5) .. (2,-1) .. (3,0.5) .. (4,1.5) .. (5,1.5) .. (6,2.6) .. (7,3.5) .. (8,3.5) .. (9.3,3);

path sand = (-1.3,-0.5) .. (0,-0.3) .. (0.5,0.3) .. (1,0.8) .. (2,0.8) .. (3,1.3) .. (4,2.1) .. (5,2.7) .. (6,2.9) .. (7,3.8) .. (8.5,3.4) .. (9.3,3.2);

path upper = (9.3,6) -- (-1.3, 6);
path lower = (9.3,-2) -- (-1.3, -2);



pen[][] gc1 = {{lightcyan, cyan}, {heavycyan,mediumblue}};
pen[][] gc2 = {{cyan,deepcyan}};

latticeshade(coast -- lower -- cycle, gc1);
latticeshade(coast, true, cyan+8, gc2);



pen[][] go = {{lightolive, olive, lightolive, olive, lightolive}, {olive, lightolive, olive, lightolive, olive}, {olive, lightolive, olive, lightolive, olive}, {olive, lightolive, olive, lightolive, olive},{lightolive, olive, lightolive, olive, lightolive}};

latticeshade(coast -- upper -- cycle, go);
draw(coast, lightolive+2);



pen[][] gg1 = {{grey, palegray}, {mediumgray,lightgray}};
pen[][] gg2 = {{lightgrey, mediumgray}};

latticeshade(sand  -- upper -- cycle, gg1);
latticeshade(sand, true, gray+2.5, gg2);


path p = (0,0){NE} .. (1,1) .. (2,1) .. (3,1.5) .. (4,2.5) .. (5,3) .. (6,3) .. (7,5) .. {right}(8,4);

real L = arclength(p);
real C = arclength(coast);

draw(arcpoint(p, 0.1*L) .. (1.1,0) .. (0.8,-0.5) .. {down}arcpoint(coast, 0.2*C), brown+1.5);
draw(arcpoint(p, 0.3*L){down} .. (2.5,0.5) .. {SE}arcpoint(coast, 0.35*C), brown+1.5);
draw(arcpoint(p, 0.4*L) .. (3.8,1.7) .. {down}arcpoint(coast, 0.5*C), brown+1.5);
draw(arcpoint(p, 0.5*L) .. (4.5,2.2) .. {down}arcpoint(coast, 0.6*C), brown+1.5);
draw(arcpoint(p, 0.7*L){down} .. {SE}arcpoint(coast, 0.75*C), brown+1.5);

draw(p, black+2);

label("0", arcpoint(coast, 0.2*C) +0.2*SE);
label("1", arcpoint(coast, 0.35*C)+0.2*SE+0.2*S);
label("2", arcpoint(coast, 0.5*C) +0.2*SE+0.3*S);
label("3", arcpoint(coast, 0.6*C) +0.2*SE+0.4*S);
label("4", arcpoint(coast, 0.75*C)+0.2*SE+0.5*S);

label(scale(0.5)*"50m", (1.3,-0.3));
label(scale(0.5)*"40m", (2.2,0.5));
label(scale(0.5)*"20m", (4.1,1.8));
label(scale(0.5)*"30m", (4.9,2.2));
label(scale(0.5)*"10m", (6.5,3.2));

label(scale(0.5)*"0m",  arcpoint(p, 0.0*L) +0.4*S);
label(scale(0.5)*"10m", arcpoint(p, 0.1*L) +0.4*N);
label(scale(0.5)*"30m", arcpoint(p, 0.3*L) +0.4*N);
label(scale(0.5)*"40m", arcpoint(p, 0.4*L) +0.5*N);
label(scale(0.5)*"50m", arcpoint(p, 0.5*L) +0.4*N);
label(scale(0.5)*"70m", arcpoint(p, 0.7*L) +0.3*W);
label(scale(0.5)*"100m",arcpoint(p, 1.0*L) +0.4*S);

clip( (-1,-2) -- (9,-2) -- (9,6) -- (-1,6) -- cycle );


currentpicture = yscale(0.5) * currentpicture;

label(scale(0.18)*graphic("ring.png"), (-0.2,0.6));
label(scale(0.1)*graphic("hotel.png"), (8.1,2.4));
