/*
 * string.h
 * string & memory manipulation functions.
 */

#pragma once

#include "libs/prelude.h"

void*   memset(void* s, u8 c, usize n);
void*   memcpy(void* dest, const void* src, usize n);
isize   memcmp(const void* s1, const void* s2, usize n);
usize   strlen(const char* s);
char*   strcpy(char* dest, const char* src);
char*   strncpy(char* dest, const char* src, usize n);
char*   strcat(char* dest, const char* src);
isize   strcmp(const char* s1, const char* s2);
char*   strdup(const char* s);

result_t    str2isize(const char* s, isize* out);
