#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static FILE *fr, *fw;

// Declaring variables
static int R;
static int* A;
static int* B;
static int* T;

// Declaring functions
void pianifica(int R, int* A, int* B, int* T);

// Begin fast input library

static inline char fast_read_char() {
	char c = fgetc_unlocked(fr);
	// ignore whitespaces
	while (	c == 0x20 || c == 0x09 || c == 0x0a 
			|| c == 0x0b || c == 0x0c || c == 0x0d) c = fgetc_unlocked(fr);
	return c;
}

static inline int fast_read_int() { // speed x5
	short int minus = 0;
	int res = 0;
	char c = fgetc_unlocked(fr);
	while (c != '-' && (c < '0' || '9' < c)) c = fgetc_unlocked(fr);

	if (c == '-') minus = 1, c = fgetc_unlocked(fr);
	
	do{
		res = res * 10 + (c - '0');
		c = fgetc_unlocked(fr);
	}
	while ('0' <= c && c <= '9');
	
	if (minus) return -res;
	else return res;
}

static inline long long int fast_read_longint() {
	short int minus = 0;
	long long int res = 0;
	char c = fgetc_unlocked(fr);
	while (c != '-' && (c < '0' || '9' < c)) c = fgetc_unlocked(fr);

	if (c == '-') minus = 1, c = fgetc_unlocked(fr);
	
	do{
		res = res * 10ll + (long long int)(c - '0');
		c = fgetc_unlocked(fr);
	}
	while ('0' <= c && c <= '9');
	
	if (minus) return -res;
	else return res;
}

static inline double fast_read_real() { //TODO
	double x;
	fscanf(fr, "%lf", &x);
	return x;
}

static inline void fast_write_char(char c) {
	fputc_unlocked(c, fw);
}

static inline void fast_write_int(int x) { // speed x2
	static short int digits[16];
	if (x == 0) {
		fputc_unlocked('0', fw);
		return;
	}
	if (x < 0) {
		fputc_unlocked('-', fw);
		x = -x;
	}
	short int i = -1;
	while (x) {
		i++;
		digits[i] = x%10; 
		x /= 10;
	}
	for (; i >= 0; i--) fputc_unlocked('0' + digits[i], fw);
}

static inline void fast_write_longint(long long int x) { // speed x2
	static short int digits[32];
	if (x == 0) {
		fputc_unlocked('0', fw);
		return;
	}
	if (x < 0) {
		fputc_unlocked('-', fw);
		x = -x;
	}
	short int i = -1;
	while (x) {
		i++;
		digits[i] = x%(10ll); 
		x /= 10ll;
	}
	for (; i >= 0; i--) fputc_unlocked('0' + digits[i], fw);
}

static inline void fast_write_real(double x) { //TODO
	fprintf(fw, "%lf", x);
}

// End fast input library

int main() {
	#ifdef EVAL
		fr = fopen("input.txt", "r");
		fw = fopen("output.txt", "w");
	#else
		fr = stdin;
		fw = stdout;
	#endif

	// Iterators used in for loops
	int i0;

	// Reading input
	R = fast_read_int();
	A = (int*)malloc(R * sizeof(int));
	B = (int*)malloc(R * sizeof(int));
	for (i0 = 0; i0 < R; i0++) {
		A[i0] = fast_read_int();
		B[i0] = fast_read_int();
	}

	// Calling functions
	T = (int*)malloc(R * sizeof(int));
	pianifica(R, A, B, T);

	// Writing output
	for (i0 = 0; i0 < R; i0++) {
		fast_write_int(T[i0]);
		fast_write_char(' ');
	}
	fast_write_char('\n');
	
	fclose(fr);
	fclose(fw);
	return 0;
}
