/*
 * =====================================================================================
 *
 *       Filename:  group.c
 *
 *    Description:  group of liars
 *
 *        Version:  1.0
 *        Created:  12/31/2010 01:18:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  madan, madanpandiri@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	NEUTRAL = 0,
	LIAR,
	NON_LIAR,
	ALLEGED_LIAR,
	ALLEGED_NON_LIAR
}GRP_VAL;

int t[5][5];
int g[5];
const int const max_group_value = 5;

void print()
{
	int i;
	for (i = 0; i < max_group_value; i++)
		printf("%d ", g[i]);

}



int consistent_alleged_group(int np, GRP_VAL value, char *store_group)
{
	int i = 0;
	for (i = 0; i < max_group_value; i++){
		if(t[np][i] == ALLEGED_LIAR){
			if (g[i] != NEUTRAL && g[i] != ALLEGED_LIAR)
					return 0;
		}
	}
	for (i = 0; i < max_group_value; i++){
		if(t[np][i] == ALLEGED_LIAR){
			store_group[i] = g[i];
			g[i] = ALLEGED_LIAR;
		}
	}
	return 1;
}

void restore_alleged_group(char *store_group)
{
	int i = 0;
	for (i = 0; i < max_group_value; i++)
		g[i] = store_group[i];
}

void find_group(int np)
{
	if (np == max_group_value){
		print();
		exit(0);
	}
	
	if (g[np] == ALLEGED_NON_LIAR || g[np] == ALLEGED_LIAR) {
		find_group(np+1);
		return;
	}
	
	char *store_group = malloc(max_group_value);
	
	g[np] = LIAR;
	if (consistent_alleged_group(np, LIAR, store_group)){ 
		find_group(np+1);	
		restore_alleged_group(store_group);
	}
	
	g[np] = NON_LIAR;
	if (consistent_alleged_group(np, NON_LIAR, store_group)){ 
		find_group(np+1);	
		restore_alleged_group(store_group);
	}
	free(store_group);
}

int main()
{
	find_group(5);		
}
