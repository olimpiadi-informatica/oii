#include <stdio.h>
 
#define MAXN 1000000
#define MAXL 15000000
 
int value[MAXL];
int next[MAXL];
int last[MAXN + 1];
 
void Accendi(int N, int acceso[], int pulsante[]) {
    int i;
    int L = N + 1;
 
    /*
    for (int i = 1; i <= N; i++) {
        value[i] = 1;
        last[i] = i;
    } */
    asm volatile (
        "xor %%rcx, %%rcx;"
        "movl $0x01, %%ecx;"
        "loop1A:\n"
            "cmp %[N], %%ecx;"
            "jg out1A;"
            "lea (%[value], %%rcx, 4), %%rax;"
            "movl $0x01, (%%rax);"
            "lea (%[last], %%rcx, 4), %%rax;"
            "movl %%ecx, (%%rax);"
            "inc %%ecx;"
            "jmp loop1A;"
        "out1A:"
 
        "movl $0x02, %%ecx;"
        "xor %%r15, %%r15;"
        "loop1B:\n"
            "cmp %[N], %%ecx;"                       // if (i <= N)
            "jg out1B;"                              //   break
 
            "movl %%ecx, %%edx;"                     // j = i
            "loop2B:\n"
                "cmp %[N], %%edx;"                   // if (j <= N)
                "jg out2B;"                          //   break
 
                "movl %[L], %%r15d;"
                "lea (%[value], %%r15, 4), %%rax;"    // Aggiorna value[L]
                "movl %%ecx, (%%rax);"                //  .
                "lea (%[last], %%rdx, 4), %%rax;"     // Aggiorna next[last[j]]
                "xor %%ebx, %%ebx;"
                "movl (%%rax), %%ebx;"                //  .
                "lea (%[next], %%rbx, 4), %%rbx;"     //  .
                "movl %[L], (%%rbx);"                 //  .
                "movl %[L], (%%rax);"                 // Aggiorna last[j]
                "inc %[L];"                           // ++L
                "addl %%ecx, %%edx;"                  // j += i
                "jmp loop2B;"
            "out2B:\n"
            "inc %%ecx;"                              // ++i
            "jmp loop1B;"
        "out1B:\n"
 
        "xor %%rcx, %%rcx;"
        "movl %[N], %%ecx;"
        "loop1C:\n"
            "cmp $0x01, %%rcx;"
            "jl out1C;"
 
            "movl (%[acceso], %%rcx, 4), %%eax;"
            "cmpl $0x01, %%eax;"
            "jz endif;"
 
            "movl $0x01, (%[pulsante], %%rcx, 4);"
            "movl %%ecx, %%edx;"
            "loop2C:"
                "cmpl $0, %%edx;"
                "jz out2C;"
                "lea (%[value], %%rdx, 4), %%rbx;"
                "movl (%%rbx), %%r15d;"
                "lea (%[acceso], %%r15, 4), %%rbx;"
                "movl (%%rbx), %%r15d;"
                "xor $0x01, %%r15d;"
                "movl %%r15d, (%%rbx);"
                "lea (%[next], %%rdx, 4), %%rbx;"
                "movl (%%rbx), %%edx;"
                "jmp loop2C;"
            "out2C:\n"
            "endif:\n"
            "dec %%rcx;"
            "jmp loop1C;"
        "out1C:\n"
 
        : [L] "=r"(L)
        : "0"(L),
          [value] "r"(value),
          [next]  "r"(next),
          [last]  "r"(last),
          [N]     "r"(N),
          [acceso] "r"(acceso),
          [pulsante] "r"(pulsante)
        : "r15", "rax", "rbx", "rcx", "rdx"
    );
}
 
/*
int acceso[7]   = {0, 0,1,0,1,0,0};
int pulsante[7] = {0, 0,0,0,0,0,0};
 
int main() {
    Accendi(6, acceso, pulsante);
 
    int i;
    for (i = 1; i <= 6; i++) {
        printf("%d ", pulsante[i]);
    }
    printf("\n");
}*/
