#include<stdio.h>
struct TREENODE {
	int no;
	int dir;
	struct TREENODE* paddr;
};

typedef struct TREENODE TREENODE;

struct NODE {
	int arr[17];
	int gvalue; 
	int spos; 
	int depth;
	int no;
	int dir;
	TREENODE *paddr;
};

typedef struct NODE NODE;

struct LIST {
	NODE node;
	struct LIST *next;
};
typedef struct LIST LIST;

LIST *head = 0;
const int INCRLEN = 10;
NODE INODE;


void findGoalvalue(NODE *, int);
void inline swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}


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


void traverse(NODE node)
{
	int *arr = (int *)malloc(sizeof(int)*(node.depth+1));
	int i=0;
	arr[i++] = node.dir;
	TREENODE* tnode = node.paddr;
	while(tnode != 0 && (i <=node.depth))	{
		arr[i++] = tnode->dir;
		tnode = tnode->paddr;
	}
	int j = 0;
	printf(" the order is\n");
	print(INODE);
	for(j = i-2; j >= 0; j--){
//		printf("%d\t", arr[j]);
		swap(&INODE.arr[INODE.spos], &INODE.arr[INODE.spos+arr[j]]);
		INODE.spos  += arr[j];
		print(INODE);
	}
	
	free(arr);
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

NODE getFirstNode(TREENODE** paddr)
{
	NODE node;
	LIST *tmp = head;
	static int first = 1;
	if( head != 0 ) {
		node =	head->node;
		head = head->next;
		/**************adding into tree node*******************/
		TREENODE *ptree = (TREENODE *)malloc(sizeof(TREENODE));
		ptree->no    = node.no;
		ptree->dir   = node.dir;
		ptree->paddr = node.paddr;
		*paddr	     = ptree;
		//printf(" the addrss is = %u \n",paddr);
		/*********************************************************/
		free(tmp);
	}
	else {
		printf("List not empty\n");
	}
	
	return(node);
}
void insertNode(NODE node,int dir)
{
	static int nodeno = 1;
	findGoalvalue(&node);
	LIST *tlist = head;	
	LIST *plist = 0;
	LIST *tmp = (LIST *)malloc(sizeof(LIST));	
		
	tmp->node = node;
	tmp->node.no = nodeno++;
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
	
}


void findGoalvalue(NODE *node)
{
	int i;
	node->gvalue = 0;
	for(i = 1; i <= 16; i++ ) {
		if(node->spos == i)
			continue;
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

int lessvalue(NODE *node,int index,int xvalue)
{
	findGoalvalue(node);
	
	return((node->gvalue+xvalue+1)%2);
}



	
void solveFifteen()
{
	NODE node[4];
	NODE pnode[4];
	NODE inode;	
	int r;
	int c;
	int spos;
	int depth = 0;
	int i;
	
	int x = 0;
	char *dir[4] = {"up", "down", "left", "right"};
	int stack[4]={1000};
	int top=0;
	int prevdir = 0;
	int cdir = -10;
	TREENODE *paddr = 0;
		
	inode = getFirstNode(&paddr);	
	while(1) {
		node[0] = node[1] = node[2] = node[3] = inode;
		
		spos = inode.spos-1;
		r = spos/4;
		c = spos%4+1;
		x = (r+c+1)%2;
		depth = inode.depth + 1;	
		prevdir = cdir;
		top = 0;
			
		
		
		if( r>=1 ){		// up direction
			swap(&node[0].arr[node[0].spos], &node[0].arr[(r-1)*4+c]);
			node[0].spos 	= (r-1) * 4 +c;
			node[0].depth 	= depth; 
			node[0].paddr	= paddr;
			node[0].dir	= -4;
			insertNode(node[0], 0 );
			
		}
		
		if( r<=2 ){		// down direction
			swap(&node[1].arr[node[1].spos], &node[1].arr[(r+1)*4+c]);
			node[1].spos  	= (r+1) * 4 + c;
			node[1].depth 	= depth; 
			node[1].paddr	= paddr;
			node[1].dir	= 4;
			insertNode(node[1], 1);
		}
		
		if( c>=2 ){		//left direction
			swap(&node[2].arr[node[2].spos], &node[2].arr[r*4+(c-1)]);
			node[2].spos 	= r * 4 + (c-1);
			node[2].depth 	= depth; 
			node[2].paddr	= paddr;
			node[2].dir	= -1;
			insertNode(node[2],2);
			
		}
		
		if( c<=3 ){		// right direction
			swap(&node[3].arr[node[3].spos], &node[3].arr[r*4+(c+1)]);
			node[3].spos 	= r * 4 + (c+1);
			node[3].depth 	= depth; 
			node[3].paddr	= paddr;
			node[3].dir	= 1;
			insertNode(node[3],3);
		}
			
		inode = getFirstNode(&paddr);	
//		printf(" the node number = %d\n", inode.no);
	}
}


int main()
{	
	/*int arr[] = {
		1,   2,  3,  4,
		5,   6,  7,  8, 
		9,  10, 11,  0,
		13, 14, 15,  12
	};*/
	int i;
	NODE node;
	for(i = 1; i <=16; i++){
		scanf("%d",&node.arr[i]);
		if( node.arr[i] == 0 )
			node.spos = i;
	}
		
	//node.spos 	=  4;
	node.depth	=  0;
	node.gvalue     = -1;
	node.no		= -1;
	node.paddr 	= 0;
	node.dir	= -10;

 	int spos, r, c, x;
	spos = node.spos-1;
        r = spos/4;
        c = spos%4+1;
        x = (r+c)%2;
	
	findGoalvalue(&node);
//	if( node.valid == -1 )
//		exit(0);
	INODE = node;
	insertNode(node, 0);
	solveFifteen();
	
}		
