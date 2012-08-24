#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

#include "hash.h"

char mem_arr[1024*1024*50] = {0};


char *cur_ptr = mem_arr - sizeof(entry); // a little hack; so we remove the sizeof(entry) for end_ptr
char *end_ptr = mem_arr + sizeof(mem_arr) - 2 * sizeof(entry);

struct HASH_TBL hash_tbl [TABLE_SIZE][SUB_TABLE_SIZE] = {};

int hash_multiplier[TABLE_SIZE*SUB_TABLE_SIZE]= { 
						100003,100019,100043,100049,100057,100069,100103,100109,100129,100151,
						100153,100169,100183,100189,100193,100207,100213,100237,100267,100271,
						100279,100291,100297,100313,100333,100343,100357,100361,100363,100379,
						100391,100393,100403,100411,100417,100447,100459,100469,100483,100493,
						100501,100511,100517,100519,100523,100537,100547,100549,100559,100591,
						100609,100613,100621,100649,100669,100673,100693,100699,100703,100733,
						100741,100747,100769,100787,100799,100801,100811,100823,100829,100847,
						100853,100907,100913,100927,100931,100937,100943,100957,100981,100987,
						100999,101009,101021,101027,101051,101063,101081,101089,101107,101111,
						101113,101117,101119,101141,101149,101159,101161,101173,101183,101197,
					};


struct HASH_TBL * get_table(unsigned char *str)
{
	unsigned int h1 = 0;
	unsigned char *ptr = str;
	for (;*ptr;ptr++) {
		h1 = h1 * MULTIPLIER + *str;
	}
	
	int mult = hash_multiplier[h1%TABLE_SIZE];

	unsigned int h2 = 0;	

	for (;*str;str++) {
		h2 = h2 * mult + *str;
	}
	return &hash_tbl[h1%TABLE_SIZE][h2%SUB_TABLE_SIZE];

}

void print_hash_tbl()
{	
	int i, j;
	for (i = 0; i < TABLE_SIZE; i++) {
		for (j = 0; j < SUB_TABLE_SIZE; j++) {
			printf(" bucket = %d -%d -%d \n", i, j, hash_tbl[i][j].count);
		}
	}
}

void print_hash_entries()
{
    int i,j,k;
    entry *e;
    for (i = 0; i < TABLE_SIZE; i++)
        for (j = 0; j < SUB_TABLE_SIZE; j++)
        if (hash_tbl[i][j].count) {
            e = hash_tbl[i][j].ent;
            k = 0;
            while(e) {
                printf(" table = %d , %d  entry = %d - %d \n", i, j, k++, e->st.in.l2_pkts);
                e = e->next;
            }
            printf("--------------------\n");
        }

}


void * get_empty_slot(int sz)
{
	if (unlikely(cur_ptr > end_ptr)){
		print_hash_tbl();
		printf ("overflow \n");
		exit(0);
	}
	return (cur_ptr += sz);		//this was possible of little hack at the top 
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

	struct HASH_TBL *tbl = get_table(str);				
	e = tbl->ent;

	if (unlikely(str_len > MAX_STR_LEN))
			str_len = MAX_STR_LEN;

	if (unlikely(!e)) {
		tbl->count = 1;
		tbl->ent   = alloc_entry(str, str_len);
		return tbl->ent;
	}	

	while (likely(e)) {
		if (unlikely(memcmp(str, e->macaddr, str_len) == 0)){
			return e;
		}
		prev = e;
		e = e->next;
	}
	tbl->count++;
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
	print_hash_entries();
	return 0;
}
