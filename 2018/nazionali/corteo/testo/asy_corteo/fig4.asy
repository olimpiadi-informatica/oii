unitsize(1cm);
settings.tex = "pdflatex";
import grafi;

pair[] posizioni = { (0,2), (2,2), (4,2), (2,0) };
int[][] E = {
	{0, 1},
	{1, 2},
	{1, 3}
};
int[] colE = {2,0,0};
pair spazi = (0,2);
pair tab = (2,2);
main(posizioni, E, colE);
label(scale(0.05) * graphic("spazi.png"), spazi+(0.0,0.8));
label(scale(0.05) * graphic("tab.png"), tab+(0.0,0.8));
