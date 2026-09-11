#include "util/string.h"

#include <stddef.h> // for NULL

long strlen(const char *str) {
    long i = 0;
    while (str[i] != '\0') { // count characters until the null terminator
        i++;
    }
    return i;
}

char *strstr(const char *haystack, const char *needle) {
    long i = 0;
    long nedlen = strlen(needle);
    long haylen = strlen(haystack);

    while (haystack[i] != '\0'){
        int yes = 1;
        if (haylen - i < nedlen) {
            return NULL; // not enough room left for needle to fit
        }

        long length = strlen(needle);
        for (long j = i; j-i < length; j++){
            if (haystack[j] != needle[j-i]){
                yes = 0;
                break;
            }
        }

        if (yes){
            char *r = (char *) &haystack[i]; // found a match starting here
            return r;
        }
        i++;
    }
    return NULL;
}

char *strncat(char *dest, const char *src, long n) {
    long len = strlen(dest);
    long i = 0;
    long j = len;
    if(n ==0 || strlen(src) == 0){
        return dest;
    }
    while(src[i]!='\0' && i < n){
        dest[j] = src[i]; // append characters from src onto the end of dest
        i++;
        j++;
    }
    dest[j] = '\0';
    return dest;
}

int strncmp(const char *s1, const char *s2, long n) {
    for (int i = 0; i < n; i++) {
        // cast to unsigned char so bytes like 0xFF compare correctly
        // instead of being treated as negative values
        unsigned long c1 = (unsigned char) s1[i];
        unsigned long c2 = (unsigned char) s2[i];

        if (c1 == '\0' && c2 != '\0'){
            return -1;
        }
        else if (c2 == '\0' && c1 != '\0'){
            return 1;
        }
        else if (c2 == '\0' && c1 == '\0'){
            return 0;
        }
        else if (c1 > c2){
            return 1;
        }
        else if (c1 < c2) {
            return -1;
        }
    }
    return 0;
}