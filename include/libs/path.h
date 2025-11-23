/*
 * path manipulation helper functions
 */
#pragma once
#include <libs/prelude.h>

bool path_is_absolute(const char *path);
bool path_is_relative(const char *path);
const char* path_basename(const char *path);
