/*
 * =====================================================================================
 *
 *       Filename:  lp.c
 *
 *    Description:  loop detection and position
 *
 *        Version:  1.0
 *        Created:  Monday 20 August 2012 02:04:06  IST
 *       Revision:  none
 *       Compiler:  gcc
 *          input:  position of loop and elements and ctrl-D
 *
 *         Author:  madan (), madanpandiri@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

typedef struct list {
    int data;
    struct list *next;
}LIST;


LIST *h;


LIST *find_loop(LIST *l)
{
    LIST *n = l;
    if (n->next) {
        n = n->next->next;
    }

    while (1) {
        if (l == n) {
            printf("Found a loop\n");
            return l;
        }

        if (n->next && n->next->next) {
            n = n->next->next;
        }
        else {
            printf("Not a loop");
            return 0;
        }
        l = l->next;
    }
}



int main()
{

    int data;
    int lp_pos;
    LIST *p;
    

    scanf("%d", &lp_pos);
    int err =  scanf("%d", &data);
    if (err == EOF)
        exit(0);
    
    h = malloc(sizeof(LIST));
    h->data = data;
    h->next = NULL;

    LIST *l = h;
    while (scanf("%d", &data) != EOF) {
        if (!--lp_pos)
            p = l;
        l->next = malloc(sizeof(LIST));
        l = l->next;

        
        l->data = data;
        l->next = NULL;
    }

    LIST *pl;
    for (l = h; l != NULL; pl = l, l=l->next)
        printf("%d\n", l->data);

    pl->next = p;
    LIST *n = find_loop(h);
    LIST *nl;
    int i;
    int done = 0;
    if (n) {
        for (i = 1, l = h; !done && l != NULL; pl =l, l = l->next, i++) {
             nl = n->next;
             while (n != nl) {
                 if (nl == l) { 
                     printf("loop started at = %d, %d\n", i, l->data);
                     done = 1;
                     break;
                }
                nl = nl->next;
            }
        }
    }
}

