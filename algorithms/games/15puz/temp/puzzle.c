#include<stdio.h>
#include"puzzle.h"

LIST *head = 0;
NODE INODE;
int LIVENODES = 0;


void min_heap(int, int);
int remove_pq(NODE *);
void insert_pq(NODE);
void findGoalvalue(NODE *);


/*void inline swap(char *a, char *b)
{
	char c = *a;
	*a = *b;
	*b = c;
}*/


void print(NODE node)
{
	int i;
	printf("\n");
	for(i = 0; i <4; i++) {
		printf("%d\t%d\t%d\t%d\n", node.arr[i*4+1],node.arr[i*4+2], 
					node.arr[i*4+3], node.arr[i*4+4]);
	}
	printf("\n");
	usleep(1000000);
	system("clear");
}

void printlist()
{
	LIST *list = head;
	printf("**********************STARTING OF LIST *********************\n");
	while(list != 0){
		print(list->node);
		list = list->next;	
	}
	printf("**********************END OF LIST *********************\n");
}

void traverse(NODE node)
{
	int i=0;
//	int *stk = (int *)malloc(sizeof(int)*(node.depth+1));
	char *stk = (char *)malloc(sizeof(char)*(node.depth+1));
	stk[i++] = node.dir;
	
	TREENODE* tnode = node.paddr;
	while(tnode != 0 ){
		printf("%d\t", stk[i-1]);
		stk[i++] = tnode->dir;
		tnode = tnode->paddr;
	}
		printf("%d\t", stk[i-1]);
	printf(" the depth of the tree is %d\n", i);
	int j = 0;
	printf(" the order is\n");
	print(INODE);
	for(j = i-2; j >= 0; j--){
		swap(INODE.arr[INODE.spos], INODE.arr[INODE.spos+stk[j]], char);
		INODE.spos  += stk[j];
		print(INODE);
	}
	
	free(stk);
	printf(" the number of live nodes = %d\n", LIVENODES);
}

NODE getFirstNode(TREENODE** paddr)
{
	NODE node;
	remove_pq(&node);
	TREENODE *ptree = (TREENODE *)malloc(sizeof(TREENODE));
	ptree->dir   = node.dir;
	ptree->paddr = node.paddr;
	*paddr	     = ptree;
	LIVENODES--;
	return(node);
}
/*NODE getFirstNode(TREENODE** paddr)
{
	NODE node;
	LIST *tmp = head;
	if( head != 0 ) {
		node =	head->node;
		head = head->next;
		/**************adding into tree node*******************/
//		TREENODE *ptree = (TREENODE *)malloc(sizeof(TREENODE));
//		ptree->dir   = node.dir;
//		ptree->paddr = node.paddr;
//		*paddr	     = ptree;
		/*********************************************************/
//		free(tmp);
//	}
//	else {
//		printf("List not empty\n");
//	}
//	LIVENODES--;
//	return(node);
//}*/
/*void insertNode(NODE node)
{
	findGoalvalue(&node);
	LIST *tlist = head;	
	LIST *plist = 0;
	LIST *tmp = (LIST *)malloc(sizeof(LIST));	
		
	tmp->node = node;
	tmp->next = 0;
	while(tlist != 0) {
		if(tlist->node.gvalue > tmp->node.gvalue){
			break;
		}
		plist = tlist;
		tlist = tlist->next;
	}
	if( plist != 0 ){	
		tmp->next = plist->next;
		plist->next = 	tmp;
	}
	else{
		if( head != 0 )
			tmp->next = head;
		head = tmp;
	}
	LIVENODES++;
	
}*/



void insertNode(NODE node)
{
	findGoalvalue(&node);
	insert_pq(node);
	LIVENODES++;
	
}

void findGoalvalue(NODE *node)
{
	int i;
	node->gvalue = -1;
	for(i = 1; i <= 16; i++ ) {
		if(node->arr[i] != i)
			node->gvalue++;
	}
	if( node->gvalue == 0 ) {
		printf("The puzzle is solved\n");
		printf(" the depth of the tree is = %d\n", node->depth);
		traverse(*node);
		exit(0);
	}
	node->gvalue += node->depth;
	
}

int lessvalue(NODE *node,int xvalue)
{
	findGoalvalue(node);
	
	return((node->gvalue+xvalue+1)%2);
}



	
void solveFifteen()
{
	NODE node[4];
	NODE inode;	
	int r;
	int c;
	int spos;
	int i;
	TREENODE *paddr = 0;
		

	while(1) {
		inode = getFirstNode(&paddr);	
		inode.depth++;
		inode.paddr = paddr;
		node[0] = node[1] = node[2] = node[3] = inode;
		
		spos = inode.spos-1;
		r = spos/4;
		c = spos%4+1;
		spos++;

		if( r>=1 ){		// up direction
			swap(node[0].arr[spos], node[0].arr[spos-4], char);
			node[0].spos 	= spos-4;
			node[0].dir	= -4;
			insertNode(node[0]);
			
		}
		
		if( r<=2 ){		// down direction
			swap(node[1].arr[spos], node[1].arr[spos+4], char);
			node[1].spos  	= spos+4;
			node[1].dir	= 4;
			insertNode(node[1]);
		}
		
		if( c>=2 ){		//left direction
			swap(node[2].arr[spos], node[2].arr[spos-1], char);
			node[2].spos 	= spos-1;
			node[2].dir	= -1;
			insertNode(node[2]);
			
		}
		
		if( c<=3 ){		// right direction
			swap(node[3].arr[spos], node[3].arr[spos+1], char);
			node[3].spos 	= spos+1;
			node[3].dir	= 1;
			insertNode(node[3]);
		}
	}
}


int main()
{	
	int i;
	int num;
	NODE node;
	
	for(i = 1; i <=16; i++){
		scanf("%d",&num);
		node.arr[i] = num;
		if( num == 0 )
			node.spos = i;
	}
		
	node.depth	=  0;
	node.gvalue     = -1;
	node.paddr 	=  0;
	node.dir	= -10;

 	int spos, r, c, x;
	spos = node.spos-1;
        r = spos/4;
        c = spos%4+1;
        x = (r+c+1)%2;
	
	//if( lessvalue(&node, x) != 1 ){
		//exit(0);
	//}
	//print(node);
	INODE = node;
	insertNode(node);
	printf(" the size of node is %d\n", sizeof(NODE));
	solveFifteen();
	
}		
