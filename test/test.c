#include "util/string.h"
#include <stddef.h> 
#include <stdio.h>
#include "include/input.h"
#include <assert.h>
#include <stdlib.h>


int main() {
    const char *message = "hello";
    const char *small = "";
    printf("%zu\n", strlen(message));
    printf("%zu\n", strlen(small));

    const char *n = "";
    const char *h = "";
    assert(strstr(h,n) == NULL); 

    const char *n1 = "hello";
    const char *h1 = "hellohello";
    printf("%s\n", strstr(h1,n1));

    const char *n5 = "hello";
    const char *h5 = "abchello";
    printf("%s\n", strstr(h5,n5));

    const char *n2 = "";
    const char *h2 = "hellohello";
    printf("%s\n", strstr(h2,n2));

    const char *n3 = "hello";
    const char *h3 = "";
    assert(strstr(h3,n3) == NULL); 

    const char *n4 = "abc";
    const char *h4 = "lllllllab";
    strstr(h4,n4);
    assert(strstr(h4,n4) == NULL); 
    

    const char *equal1 = "hello";
    const char *equal2 = "hello";
    int equal3 = 5;
    assert(strncmp(equal1, equal2, equal3) == 0);

    const char *equal4 = "hello";
    const char *equal5 = "abclo";
    assert(strncmp(equal4, equal5, equal3) == 1);

    const char *d1 = "hello";
    const char *d2 = "hel09";
    int d3 = 2;
    assert(strncmp(d1, d2, d3) == 0);

    const char *d4 = "a";
    const char *d5 = "abcde";
    int d6 = 10;
    assert(strncmp(d4, d5, d6) == -1);

    const char *d7 = "aaaaa";
    const char *d8 = "hel09";
    int d9 = 5;
    assert(strncmp(d7, d8, d9) == -1);

    const char *d22 = "";
    assert(strncmp(d22, d8, d9) == -1);
    

    char samedes[20] = "hello";
    char *samesrc = "there";
    int samen = 5;
    printf("%s\n", strncat(samedes,samesrc, samen));

     char biggerdest[20] = "hello";
     char *biggersrc = "there";
    int bign = 10;
    printf("%s\n", strncat(biggerdest,biggersrc, bign));

     char emptdest[20] = "hello";
     char *emptsrc = "";
    printf("%s\n", strncat(emptdest,emptsrc, bign));

     char nuldest[20] = "";
     char *nulsrc = "h";
    printf("%s\n", strncat(nuldest,nulsrc, bign));

    
    int smalln = 2;
    printf("%s\n", strncat(samedes,samesrc, smalln));
    

    char *inp = "testing this rn";
    char **inptokens = (char **) malloc(sizeof(char *));
    long numtok = tokenize_input(inp, strlen(inp), &inptokens);
    printf("%d\n", numtok);
    for (int i = 0; i < numtok; i++) {
        printf("%s\n", inptokens[i]);
    }

    char *long1 = "\xFF";
    char *long2 = "a";
    assert(strncmp(long1, long2, 2) == 1);

    return 0;
}