unitsize(1cm);
settings.tex = "pdflatex";


string[] Inizio = {"Alessandro Manzoni (3)", "Amerigo Vespucci (6)", "Cristoforo Colombo (1)", "Marco Polo (4)"};

real L = 6;

void classifica() {
    int N = Inizio.length;
    for (int i=0; i<N; ++i) {
        pen p = white;
        if (i == 0) p = paleyellow;
        if (i == 1) p = lightgray;
        if (i == 2) p = rgb(0.8,0.7,0.6);
        fill((0,-i) -- (L,-i) -- (L,-i-1) -- (0,-i-1) -- cycle, p);
        draw((0,-i) -- (L,-i), black+1);
        label(Inizio[i], (L/2,-i-0.5));
    }
    draw((0,0) -- (L,0) -- (L,-N) -- (0,-N) -- cycle, black+2);
}

void squalifica(int i) {
    draw((0.5,-i-0.2) -- (L-0.5,-i-0.8), red+3);
    draw((L-0.5,-i-0.2) -- (0.5,-i-0.8), red+3);
}

void sorpassa(int i) {
    fill((L-0.2,-i-0.65) -- (L-0.7,-i-0.65) -- (L-0.45,-i-0.25) -- cycle, heavygreen);
}

classifica();
draw((0,-5) -- (L,-5), white+2);
