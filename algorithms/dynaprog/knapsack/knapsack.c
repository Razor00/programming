#include<stdio.h>
struct resource {
	float wt;
	float profit;
	float ratio;
};

typedef struct resource rsrc;

void knapsack(rsrc *rptr, int n, float kwt)
{
	float kprofit = 0.0;
	float kfilledwt = kwt;
	while(n){
		kwt = kwt - rptr->wt;
		if( kwt < 0 ){
			kwt = kwt + rptr->wt;
			kprofit += kwt * rptr->ratio;		
			printf("%f\n", kwt/rptr->wt);
			kwt = 0;
			break;
		}
		else{
			kprofit += rptr->profit;	
		}	
		n--;
		rptr++;	
		printf("%f ", 1.0);	
	}
	if( kwt > 0 )
		kfilledwt = kfilledwt - kwt;	
	printf("The weight = %f \t profit is =%f \n", kfilledwt, kprofit);	
}		




int comp(rsrc *v1, rsrc *v2)
{
	if( v1->ratio < v2->ratio )
		return 1;
	else
	if( v1->ratio > v2->ratio )
		return -1;
	return 0;
}
int main()
{
	int i=0;
	float wt, profit;
	float kwt;
	int n;
	int arr;
	rsrc *rptr;
	scanf("%d%f", &n, &kwt);
	
	rptr = (rsrc *)calloc((n), sizeof(rsrc));
		
	
	for( i = 0; i < n; i++) {
//		printf(" value of i = %d\n", i);
		scanf("%f%f", &wt, &profit);
//		printf("wt = %f \t profit= %f \n", wt, profit);
//		printf(" value of i = %d\n", i);
		(rptr+i)->wt = wt;
		rptr[i].profit = profit;
		rptr[i].ratio = profit/wt;
	}
	
	
//	printf("before sort\n");
//	for( i = 0; i < n; i++) 
//		printf(" wt = %lf\t profit = %lf\t ratio = %lf\n", rptr[i].wt, rptr[i].profit, rptr[i].ratio);

	qsort(rptr, n, sizeof(rsrc), (int (*)(void *, void *))(comp));

//	printf("sorted elements\n");

	for( i = 0; i < n; i++) 
		printf(" wt = %lf\t profit = %lf\t ratio = %lf\n", rptr[i].wt, rptr[i].profit, rptr[i].ratio);
	knapsack(rptr, n, kwt);	
	free(rptr);
}
	
