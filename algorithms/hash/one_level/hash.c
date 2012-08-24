#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

#include "hash.h"

char mem_arr[1024*1024*50] = {0};


char *cur_ptr = mem_arr - sizeof(entry); // a little hack; so we remove the sizeof(entry) for end_ptr
char *end_ptr = mem_arr + sizeof(mem_arr) - 2 * sizeof(entry);

struct HASH_TBL hash_tbl [TABLE_SIZE] = {{0}};

int compute_hash(unsigned char *str)
{
	unsigned int h = 0;
	
	for (;*str;str++) {
		h = h * MULTIPLIER + *str;
	}
	return h%TABLE_SIZE;
}

void print_hash_tbl()
{	
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		printf(" bucket = %d = %d \n", i, hash_tbl[i].count);
	}
}

void * get_empty_slot(int sz)
{
	if (cur_ptr > end_ptr){
		print_hash_tbl();
		printf ("overflow \n");
		exit(0);
	}
	return (cur_ptr += sz);
//	return calloc(sz, 1);
}



entry * alloc_entry(unsigned char *str, int str_len)
{
	entry *ent = (entry *)get_empty_slot(sizeof(entry));
	ent->next = 0;

	memcpy(ent->macaddr, str, str_len);
	ent->macaddr[str_len] = '\0';

	return ent;
}

entry * get(unsigned char* str, int str_len)
{
	entry *e, *prev;

	int h = compute_hash(str);				

	e = hash_tbl[h].ent;		

	if (unlikely (str_len > MAX_STR_LEN))
			str_len = MAX_STR_LEN;

	if (unlikely(!e)) {
		hash_tbl[h].count = 1;
		hash_tbl[h].ent  = alloc_entry(str, str_len);
		return hash_tbl[h].ent;
	}	


	while (likely(e)) {
		if (unlikely(memcmp(str, e->macaddr, str_len) == 0)){
			return e;
		}
		prev = e;
		e = e->next;
	}
	hash_tbl[h].count++;
	return (prev->next = alloc_entry(str, str_len));
	
}

int main()
{
	char str[50];


	while (scanf("%s", str) != EOF){
//		printf (" %s - %s\n", str, get(str, strlen(str))->macaddr);	
		get(str, strlen(str));	
	}	
	print_hash_tbl();
}
