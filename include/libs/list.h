/*
 * intrusive circular double linked list
 */

#pragma once

#include "libs/prelude.h"


// the two are actually the same, but for clarity we define both

typedef struct _list_elem_t {
    struct _list_elem_t* prev;
    struct _list_elem_t* next;
} list_elem_t;
typedef list_elem_t list_t;

#define headof(list) (((list_t*)list)->next)
#define tailof(list) (((list_t*)list)->prev)
#define sentinelof(list) ((list_t*)list)

void    list_init(list_t* list);
void    list_push_front(list_t* list, list_elem_t* elem);
void    list_push_back(list_t* list, list_elem_t* elem);
list_elem_t* list_peak_front(list_t* list);
list_elem_t* list_pop_front(list_t* list);
list_elem_t* list_pop_back(list_t* list);
list_elem_t* list_remove(list_elem_t* elem);
bool    elem_in_list(list_elem_t* elem);
bool    list_is_empty(list_t* list);
bool    list_contains(list_t* list, list_elem_t* elem);
usize   list_length(list_t* list);

#define list_head(name) \
    static list_t name = { &(name), &(name) }

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)


// we do not check null pointers,
// as in a circular list there should be no null pointers.
// if that happens, it is a bug in the code using the list.

#define list_foreach(iter, list) \
    for (list_elem_t* iter = headof(list); iter != sentinelof(list); iter = iter->next)

#define list_foreach_safe(iter, list, next) \
    for (list_elem_t* iter = headof(list), *next = (iter ? iter->next : NULL); \
         iter != sentinelof(list); \
         iter = next, next = iter->next)

