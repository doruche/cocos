/*
 * elf64
 */

#pragma once

#include "libs/prelude.h"

#define ELF_MAGIC   "\x7f""ELF"

// number of bytes in e_ident[]
#define EI_NIDENT   16

typedef struct _elf_hdr_t {
    u8  e_ident[EI_NIDENT];
    u16 e_type;
    u16 e_machine;
    u32 e_version;
    u64 e_entry;
    u64 e_phoff;
    u64 e_shoff;
    u32 e_flags;
    u16 e_ehsize;
    u16 e_phentsize;
    u16 e_phnum;
    u16 e_shentsize;
    u16 e_shnum;
    u16 e_shstrndx;
} elf_hdr_t;

typedef struct _elf_phdr_t {
    u32 p_type;
#define PT_LOAD 0x00000001
    u32 p_flags;
#define PF_X    0x1
#define PF_W    0x2
#define PF_R    0x4
    u64 p_offset;
    u64 p_vaddr;
    u64 p_paddr;
    u64 p_filesz;
    u64 p_memsz;
    u64 p_align;
} elf_phdr_t;