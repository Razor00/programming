#ifndef __HASH_H
#define __HASH_H

#include "stats.h"

#define TABLE_SIZE  100
#define MULTIPLIER  500009
#define MAX_ENTRIES 300000


#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)


struct HASH_TBL{
    int count;
    entry *ent;
};

entry * alloc_entry(unsigned char* str, int str_len);
void print_hash_tbl();

#endif
