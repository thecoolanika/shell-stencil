#include "util/string.h"

#include <stddef.h> // for NULL

long strlen(const char *str) {
    long i = 0;
    while (str[i] != '\0') { // walk forward until the null terminator
        i++;
    }
    return i; // i is the number of characters before '\0'
}

char *strstr(const char *haystack, const char *needle) {
    long i = 0;
    long nedlen = strlen(needle);
    long haylen = strlen(haystack);

    while (haystack[i] != '\0'){
        int yes = 1; // assume a match starting at position i until proven otherwise
        if (haylen - i < nedlen) {
            return NULL; // not enough characters left in haystack to fit needle, so no match is possible
        }

        long length = strlen(needle);
        // compare needle against haystack starting at position i
        for (long j = i; j-i < length; j++){
            if (haystack[j] != needle[j-i]){
                yes = 0; // mismatch found, abandon this starting position
                break;
            }
        }

        if (yes){
            char *r = (char *) &haystack[i]; // match found: return pointer to where it starts in haystack
            return r;
        }
        i++; // try the next starting position
    }
    return NULL; // reached end of haystack with no match
}

char *strncat(char *dest, const char *src, long n) {
    long len = strlen(dest); // find current end of dest string
    long i = 0; // index into src
    long j = len; // index into dest, starting at its current end
    if(n ==0 || strlen(src) == 0){
        return dest; // nothing to append
    }
    // copy up to n characters from src onto the end of dest
    while(src[i]!='\0' && i < n){
        dest[j] = src[i];
        i++;
        j++;
    }
    dest[j] = '\0'; // null-terminate the concatenated result
    return dest;
}

int strncmp(const char *s1, const char *s2, long n) {
    for (int i = 0; i < n; i++) {
        // handle cases where one string ends before the other within the first n chars
        if (s1[i] == '\0' && s2[i] != '\0'){
            return -1; // s1 is "shorter"/comes first
        }
        else if (s2[i] == '\0' && s1[i] != '\0'){
            return 1; // s2 is "shorter"/comes first
        }
        else if (s2[i] == '\0' && s1[i] == '\0'){
            return 0; // both strings ended at the same point within n chars: equal
        }
        else if ((unsigned long) s1[i] > (unsigned long) s2[i]){
            return 1; // s1 is lexicographically greater at this position
        }
        else if ((unsigned long) s1[i] < (unsigned long) s2[i]) {
            return -1; // s1 is lexicographically less at this position
        }
        // otherwise characters match, continue to next index
    }
    return 0; // first n characters are identical
}