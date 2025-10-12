#include "libs/list.h"
#include "libs/types.h"

static void
list_insert(list_elem_t* prev, list_elem_t* next, list_elem_t* elem) {
    prev->next = elem;
    next->prev = elem;
    elem->prev = prev;
    elem->next = next;
}

void
list_init(list_t* list) {
    headof(list) = sentinelof(list);
    tailof(list) = sentinelof(list);
}

void
list_push_front(list_t* list, list_elem_t* elem) {
    list_insert(sentinelof(list), headof(list), elem);
}

void
list_push_back(list_t* list, list_elem_t* elem) {
    list_insert(tailof(list), sentinelof(list), elem);
}

bool
list_is_empty(list_t* list) {
    return headof(list) == sentinelof(list);
}

bool
list_contains(list_t* list, list_elem_t* elem) {
    list_elem_t* cur = headof(list);
    while (cur != sentinelof(list)) {
        if (cur == elem) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

usize
list_length(list_t* list) {
    usize len = 0;
    list_elem_t* cur = headof(list);
    while (cur != sentinelof(list)) {
        len++;
        cur = cur->next;
    }
    return len;
}

list_elem_t*
list_remove(list_t* list, list_elem_t* elem) {

#ifdef DEBUG
// a safety check along with a huge performance hit
    if (!list_contains(list, elem)) {
        #include "kernel/misc/log.h"
        warn("list_remove: element not in list");
        return NULL;
    }
#endif

    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    // cut off the links
    elem->prev = NULL;
    elem->next = NULL;

    return elem;
}

list_elem_t*
list_pop_front(list_t* list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    return list_remove(list, headof(list));
}

list_elem_t*
list_pop_back(list_t* list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    return list_remove(list, tailof(list));
}