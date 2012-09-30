/*
 * =====================================================================================
 *
 *       Filename:  suffix.c
 *
 *    Description:  suffix tree 
 *
 *        Version:  1.0
 *        Created:  Sunday 26 August 2012 12:10:55  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  madan (), madanpandiri@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char ch;
    struct node *n;
}node;

node h;
void build_link(char *s)
{
    node *n = &h;
    while (*s) {
        if (n) {
            if (*s == n->ch) {
                s++;
                n = n->next;
                continue;
            }
            break;
        }else{
            
            

        }
    }

}



void build_suffix_tree(char *s, int l)
{
    s[l]    = '$' ;
    s[l+1]  = '\0';
    l++;

    int i;
    node *n = &h;

    n->ch   = *s;
    n->next = 0;

    build_link(s);
    for (i = 1; i < l; i++) {
        build_link(s+i);
    }
    
}


int main()
{
    char buf[1024];
    gets(buf);
    construct_suffix_tree(buf, strlen(buf));
}

