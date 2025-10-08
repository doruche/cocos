#ifndef _K_BOOT_H
#define _K_BOOT_H 1

#define NMEMZONE_MAX    16

#ifndef __DEFONLY__

#include "libs/types.h"

enum memzone_type {
    MEMZONE_KERNEL = 0,
    MEMZONE_FREE,
    MEMZONE_DEV,
    MEMZONE_NONE,
};

typedef struct _memzone_t {
    u64 start;
    u64 end;
    enum memzone_type type;
} memzone_t;

typedef struct _bootinfo_t {
    memzone_t zones[NMEMZONE_MAX];
} bootinfo_t;

void kstart(bootinfo_t*);

#endif

#endif