#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

#include "hash.h"

char mem_arr[1024*1024*50] = {0};


char *cur_ptr = mem_arr - sizeof(entry); // a little hack; so we remove the sizeof(entry) for end_ptr
char *end_ptr = mem_arr + sizeof(mem_arr) - 2 * sizeof(entry);

struct HASH_TBL hash_tbl [TABLE_SIZE] = {{0}};

uint32_t compute_hash(unsigned long long key)
{
    uint32_t hash, i;
    unsigned char *k = (char *)&key;
    int len = sizeof(key)/sizeof(*k);

    for (hash = i = 0; i < len; ++i) {
        hash += k[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & (TABLE_SIZE);
}
#if 0
unsigned int h = 0;

for (;*str;str++) {
    h = h * MULTIPLIER + *str;
}

return h%TABLE_SIZE;
}
#endif
void print_hash_tbl()
{	
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		printf(" bucket = %d = %d \n", i, hash_tbl[i].count);
	}
}

void *get_empty_slot(int sz)
{
#if 0
	if (cur_ptr > end_ptr){
		print_hash_tbl();
		printf ("overflow \n");
		exit(0);
	}
	return (cur_ptr += sz);
#endif
	return calloc(sz, 1);
}



entry *alloc_entry(u64 key, u64 value)
{
	entry *ent = (entry *)get_empty_slot(sizeof(entry));
    ent->key = key;
    ent->value = value;
	ent->next = 0;

	return ent;
}

entry *get(u64 key, u64 value)
{
	entry *e;
	int h;
   
    h = compute_hash(key);				

	e = hash_tbl[h].ent;		
	if (unlikely(!e)) {
		hash_tbl[h].count = 1;
	    hash_tbl[h].ent  = alloc_entry(key, value);
		return hash_tbl[h].ent;
	}	

    entry *p;
	while (likely(e)) {
        if (key == e->key)
			return e;
		p = e;
		e = e->next;
	}
	
    hash_tbl[h].count++;
	return (p->next = alloc_entry(key, value));
	
}

int main()
{
    u64 key, value;
 
    long op, err;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int index = 0;
    int k = 10;

    while (k) {
        printf("Enter [1-insert|2-lookup|3-delete]:");
        scanf("%d", &op);
        int p = 0;
        while (p <= 10) {
             index = index++ %10;
             if (arr[index])    
                 break;
        }
        switch (op) {

            case 1:
                printf("Please enter: key :");
                scanf("%ld", &key);
                printf("Inserting key = %d, addr = %u\n", arr[index]);
                err = insert_key(key);
                if (err) {
                    printf("Error inserting key, value pair\n");
                }
            break;

            case 2:
                printf("Please enter: key :");
                scanf("%ld", &key);
                printf("value = %d\n", get_key_value(key));
            break;

            case 3:
                printf("Please enter: key\n");
                scanf("%ld ", &key);
                remove_key(key);
            break;
 
        }
    }
}
