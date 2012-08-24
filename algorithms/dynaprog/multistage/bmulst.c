#include<stdio.h>
/****************************************/
struct node {
	int vertex;
	int edgecost;
	struct node *next;
};
typedef struct node NODE;
NODE *gnode;

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
	NODE *temp;
	*temp = gnode[vertex];
	int min = 1000000;
	int tcost;
	int pos;
	temp = temp->next;
	while(temp) {
		tcost = temp->edgecost	+ fsr(temp->vertex);
		if( tcost < min) {
			min = tcost;
			pos = temp->vertex;
		}
	}
	gcost[vertex].nvertex	= pos;
	gcost[vertex].cost 	= min;
	return(min);
}
		


int main()
{
	int n;
	int i;
	int vsrc, vdest, edgelen;
	NODE *temp1, *temp2;
	scanf("%d", &n);
	gcost = (COST *)calloc(n, sizeof(COST) );
	gnode = (NODE *)calloc(n, sizeof(NODE) );
	for(i=0; i< n; i++) {
		gcost[i].cost = -1;
		gnode[i].vertex = i;
	}
	while(1) {
		if (scanf("%d %d %d",&vsrc, &vdest, &edgelen) == -1 )
			break;
		temp1 = temp2 = &gnode[vsrc]; 
		while(temp1){
			temp2 = temp1;
			temp1 = temp1->next;
		}
		temp2->next = (NODE *)calloc(1, sizeof(NODE));
		(temp2->next)->vertex     = vdest;  
		(temp2->next)->edgecost   = edgelen;
	}
	printf("cost = %d\n",fsr(0));
			
			
}
