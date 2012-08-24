#include"puzzle.h"
#define INC_COUNT 20
#define NODE NODE


void min_heap(int, int);
int remove_pq(NODE *);
void insert_pq(NODE);
void sort();
void huff_code();
void print_tree(NODE *);

int hsz = 0;
int sz  = 0;
int leftsz = 0;	
NODE *harr = 0;
NODE *pnode=0;

void min_heap(int i, int len)
{
	int min = i;
	int l, r;

	l = 2 * i;
	r = 2 * i + 1;		

	if( (l <= len) && (harr[l].gvalue < harr[i].gvalue) ) 
		min = l;
	if( (r <= len) && (harr[r].gvalue < harr[min].gvalue) )
		min = r;
	if( min != i ) {
		swap(harr[min], harr[i], NODE);
		min_heap(min, len);
	}
}

int remove_pq(NODE *node)
{
	int i;
	if( hsz >= 1 ) {
		*node = harr[1];
		swap(harr[1], harr[hsz], NODE);
		hsz--;
		min_heap(1, hsz);
		if( hsz % INC_COUNT == 0 ) {
			sz = sz - INC_COUNT;
			if( sz == 0 ){
				free(harr);
				harr = 0;
			}
			else
				harr = (NODE *)realloc(harr, sizeof(NODE) * (sz + 1) );
			
			leftsz = 0;
		}
		else
			leftsz++;

		return(1);		
	}
	else {
		printf("Heap empty\n");
		return 0;
	}
}

void insert_pq(NODE node)
{
	int i;
	if( leftsz == 0 ) {
		sz = sz + INC_COUNT;
		leftsz = INC_COUNT;
		harr = (NODE *)realloc(harr, sizeof(NODE) * (sz+1));
	}
	leftsz--;	
	harr[++hsz] = node;	
	for(i=(hsz+1)/2 ; i>=1; i--)
		min_heap(i, hsz);
}

/*void sort()
{
	NODE node;
	while( remove_pq(&node) ) {
//		printf("%d\n",	node.freq);
//		getc(stdin);
	}
}

void print_tree(NODE *tree)
{
	if( tree ) {
		print_tree(tree->left);
//		printf("%d\n", tree->freq);
		print_tree(tree->right);
	}

}

void mynode(NODE node)
{
	NODE *ptr = pnode;
	printf(" freq: = %d\t", node.freq);
	while(ptr) {
		if( node.freq < ptr->freq ){
			ptr = ptr->left;
			printf("%c",'0');
		}
		else 
		if( node.freq > ptr->freq ) {
				ptr = ptr->right;
				printf("%c",'1');
		}
		
		else
			return;
	}
}
void traverse(NODE *node)
{
	static char arr[100];
	static int i=-1;
	int j=0;
	if( node ) {
		i++;
		arr[i] = '0';
		traverse(node->left);
		if( node->ch != '\0' ) {
			printf("char = %c freq = %d\t", node->ch, node->freq);
			for( j = 0; j < i; j++)
				printf("%c", arr[j]);
		}
		printf("\n");
		arr[i] = '1';
		traverse(node->right);
		i--;
	}
}
void tree_traverse()
{
	traverse(pnode);
}	
void huffcode()
{
	int t1, t2;	
	NODE *lnode, *rnode;
//	NODE *pnode=0;
	while(hsz >=1 ) {
		t1 = 0;
		t2 = 0;
		pnode = (NODE *)malloc(sizeof(NODE));
		lnode = (NODE *)malloc(sizeof(NODE));
		rnode = (NODE *)malloc(sizeof(NODE));
		
		if( remove_pq(lnode) ) {
			t1 = lnode->freq;
			if(lnode->addr) 
				pnode->left = lnode->addr; 
			else
				pnode->left = lnode;
		}
		if( remove_pq(rnode) ) {
			t2 = rnode->freq;
			if( rnode->addr )
				pnode->right = rnode->addr;
			else
				pnode->right = rnode;
		}
		pnode->freq = t1 + t2;
		pnode->addr = pnode;
		pnode->ch   = '\0';
		if( hsz >= 1 )
			insert_pq(*pnode);
	}
	print_tree(pnode);
}*/
