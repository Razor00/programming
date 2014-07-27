#ifndef __HASH_H
#define __HASH_H

#include "stats.h"

#define TABLE_SIZE  (1<<12) //100
#define MULTIPLIER  31 //500009
#define MAX_ENTRIES 300000


#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

typedef struct ENTRY entry;

typedef unsigned long u64;
typedef unsigned int uint32_t;

struct ENTRY {
    u64 key;
    u64 value;
    struct ENTRY *next;
}__attribute__((packed));




struct HASH_TBL{
    int count;
    entry *ent;
};


entry * alloc_entry(u64 key, u64 value);
void print_hash_tbl();

#endif
