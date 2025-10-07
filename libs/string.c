/*
 * string.c
 * string & memory manipulation functions.
 */

#include "libs/string.h"
#include "libs/types.h"

void*
memset(void* s, u8 c, usize n) {
    u8* p = (u8*)s;
    while (n--) {
        *p++ = c;
    }
    return s;
}

void*
memcpy(void* dest, const void* src, usize n) {
    u8* d = (u8*)dest;
    const u8* s = (const u8*)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

isize
memcmp(const void* s1, const void* s2, usize n) {
    const u8* p1 = (const u8*)s1;
    const u8* p2 = (const u8*)s2;
    for (usize i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return (isize)(p1[i] - p2[i]);
        }
    }
    return 0;
}

usize
strlen(const char* s) {
    const char* p = s;
    while (*p) {
        p++;
    }
    return (usize)(p - s);
}

char*
strcpy(char* dest, const char* src) {
    char* d = dest;
    while ((*d++ = *src++));
    return dest;
}

char*
strcat(char* dest, const char* src) {
    char* d = dest;
    while (*d) {
        d++;
    }
    while ((*d++ = *src++));
    return dest;
}

isize
strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (isize)(*(u8*)s1 - *(u8*)s2);
}