#include"heap.h"
#include<stdio.h>
int main()
{
	int i;
	hnode myarr[] = { 
			{0, '0' , 0, 0, 0},
			{45, 'a' , 0, 0, 0},
		 	{13, 'b' , 0, 0, 0},
			{12, 'c' , 0, 0, 0},
			{16, 'd' , 0, 0, 0},
			{9,  'e' , 0, 0, 0},
			{5,  'f' , 0, 0, 0},
		};
	
	int lenarr = 0;
//	for(i = (lenarr+1)/2 ; i >=1; i--)
//		min_heap(arr, i);
	int freq;
	char ch;
	int val=0;
	hnode temp={0,'0',0,0,0};
	while(scanf("%d %c", &freq, &ch) != -1 ) {
	//	printf("%d\n", val);
	//	getc(stdin);
		printf("freq = %d \tch = %c \n", freq, ch);
		temp.freq = freq;
		temp.ch   = ch;
		insert_pq(temp);
	}
	/*for(i = 1; i<=lenarr; i++)
		insert_pq(myarr[i]);
	for(i = 1; i <=lenarr; i++ )
		printf("%d\n", myarr[i].freq); */
//	printf("After sorting\n");
//	sort();
//	printf("Elements After sorting\n");
	huffcode();	
/*	for(i = 1; i <=5; i++ ){
		printf("\n%c:", myarr[i].ch); 
		mynode(myarr[i]);
	}*/
	tree_traverse();
	printf("\n");	
}
