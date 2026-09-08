#include "util/string.h"

#include <stddef.h> // for NULL

long strlen(const char *str) {
    long i = 0;
    while (str[i] != '\0') {
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
            return NULL;
        }

        long length = strlen(needle);
        for (long j = i; j-i < length; j++){
            if (haystack[j] != needle[j-i]){
                yes = 0;
                break;
            }
        }

        if (yes){
            char *r = (char *) &haystack[i];
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
        dest[j] = src[i];
        i++;
        j++;
    }
    dest[j] = '\0';
    return dest;
}

int strncmp(const char *s1, const char *s2, long n) {
    for (int i = 0; i < n; i++) {
        if (s1[i] == '\0' && s2[i] != '\0'){
            return -1;
        }
        else if (s2[i] == '\0' && s1[i] != '\0'){
            return 1;
        }
        else if (s2[i] == '\0' && s1[i] == '\0'){
            return 0;
        }
        else if (s1[i] > s2[i]){
            return 1;
        }
        else if (s1[i] < s2[i]) {
            return -1;
        }
    }
    return 0;
}
