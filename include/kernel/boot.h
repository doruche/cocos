#pragma once

#define NMEMZONE_MAX    16

#include "libs/prelude.h"

enum memzone_type {
    MEMZONE_K_TEXT = 0,
    MEMZONE_K_RODATA,
    MEMZONE_K_DATA,
    MEMZONE_K_BSS,
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
    u8* bootimage;
    memzone_t zones[NMEMZONE_MAX];
} bootinfo_t;

void kstart(bootinfo_t*);

void pm_init(bootinfo_t* bootinfo);
void kmalloc_init(void);
void timer_init(void);
void kvms_init(bootinfo_t* bootinfo);
void ipc_init(void);
void sched_init(u8* bootimage);