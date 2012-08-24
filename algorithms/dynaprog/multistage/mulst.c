#include<stdio.h>
/****************************************/
struct node {
	int vertex;
	int edgecost;
	struct node *next;
};
typedef struct node NODE;
NODE *gnode;
/*----------------------------------------*/
struct cost {
	int nvertex;
	int cost;
};
typedef struct cost COST;
COST *gcost;

/****************************************/

int fsr(int vertex)
{
	if( gcost[vertex].cost != -1)
		return(gcost[vertex].cost);

	int min = 1000000;
	int tcost;
	int pos=-1;
	NODE *temp;
	temp = &gnode[vertex];
	while(temp->next) {
		temp = temp->next;
		tcost = temp->edgecost	+ fsr(temp->vertex);
		if( tcost < min) {
			min = tcost;
			pos = temp->vertex;
		}
	}
	gcost[vertex].nvertex	= pos;
	gcost[vertex].cost 	= (pos == -1)? 0 : min;
	return(gcost[vertex].cost);
}
		

void findpath(int st, int end)
{
	int i = st;
	printf("vertex[%d] ",st+1);
	while(i != end) {
		printf(" --> %d vertex[%d] ", gcost[i].cost, gcost[i].nvertex+1);
		i = gcost[i].nvertex;
	}
	printf("\n");
}
int main()
{
	int n;
	int i;
	int vsrc, vdest, edgelen;
	NODE *temp1, *temp2, *temp;
	scanf("%d", &n);
	gcost = (COST *)calloc(n, sizeof(COST) );
	gnode = (NODE *)calloc(n, sizeof(NODE) );
	for(i=0; i< n; i++) {
		gcost[i].cost = -1;
		gnode[i].vertex = i;
	}
	gcost[n-1].cost = 0;

	while(1) {
		if (scanf("%d %d %d",&vsrc, &vdest, &edgelen) == EOF )
			break;
		temp1 = temp2 = &gnode[vsrc-1]; 
		while(temp1){
			temp2 = temp1;
			temp1 = temp1->next;
		}
		temp2->next = (NODE *)calloc(1, sizeof(NODE));
		(temp2->next)->vertex     = vdest-1;  
		(temp2->next)->edgecost   = edgelen;
	}
	/*for( i = 0; i < n; i++ ){
		temp = &gnode[i];
		printf(" i = %d\n", temp);
		while(temp) {
			printf("src = %d  dest = %d cost = %d\n", i, temp->vertex, temp->edgecost);
			temp = temp->next;
		}
	}*/
	printf("cost = %d\n",fsr(0));
	findpath(0, n-1);	
			
}
