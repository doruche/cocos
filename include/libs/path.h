/*
 * path manipulation helper functions
 */
#pragma once
#include <libs/prelude.h>

bool path_is_absolute(const char *path);
bool path_is_relative(const char *path);
const char* path_skipcomp(const char* path, char* comp_buf);
const char* path_basename(const char *path);
void path_dupparent(const char *path, char *buf);
void path_canonicalize(char* path, char* buf);