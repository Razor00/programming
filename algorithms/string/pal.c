/*
 * =====================================================================================
 *
 *       Filename:  pal.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/15/2010 05:42:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  madan (mad), madanpandiri@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<string.h>

int palindrome(char *s, char *e)
{
	if ((e - s) < 2) return 0;
	while (s <= e && (*s == *e)){
		s++; e--;
	}
	return s - e;
}


void find_palindrome(char *s, int e)
{
		int st = 0, end = 0, len = 0;
		int i, j;
		for (i = 0; i <= e; i++) {
				for (j = 0; j < i; j++){
						if (palindrome(s+j, s+i-1) > 0){
								if ((i - j) > len){
									st = j; end = i;
									len = end - st;
								}
						//		write(1, s+j, i-j);
						//		printf("\n");
						}
				}
		
		}
	//	printf("len = %d, st = %d, end = %d \n", end - st, st, end-1);
	//	write(1, s+st,  end - st);
	//	printf("\n");
}

char buf[1024*1024];
#include <sys/time.h>
int main(int argc, char **argv)
{
//	find_palindrome("1234321", 7);
	int rd = read(0, buf, atoi(argv[1]));
//	printf("read = %d \n", rd);
//	puts(buf);
	struct timeval t1, t2;
	gettimeofday(&t1, 0);
	find_palindrome(buf, strlen(buf));
	gettimeofday(&t2, 0);
	printf("%d, %f\n", rd, (t2.tv_sec - t1.tv_sec)*1000.0 + ((t2.tv_usec - t1.tv_usec) * 1.0)/1000);
}

