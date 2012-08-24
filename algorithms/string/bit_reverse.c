/*
 * =====================================================================================
 *
 *       Filename:  swap.c
 *
 *    Description:  reverse bits in a number
 *
 *        Version:  1.0
 *        Created:  01/02/2004 06:12:10 AM
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
typedef unsigned int u32;
unsigned int  reverse(unsigned int n)
{
	n = ((n&0xaaaaaaaa)>>1) | (n & 0x55555555)<<1;
	n = ((n&0xcccccccc)>>2) | (n & 0x33333333)<<2;
	n = ((n&0xf0f0f0f0)>>4) | (n & 0x0f0f0f0f)<<4;
	n = ((n&0xff00ff00)>>8) | (n & 0x00ff00ff)<<8;
	n = ((n&0xffff0000)>>16) | (n & 0x0000ffff)<<16;
//	printf("rev = 0x%8x\n", n);
	return (n);

}
unsigned int bit_set(unsigned int n)
{
	unsigned int t = n & (n - 1); 
	t = t ^ n;
//	printf("set: 0x%x\n", t);
	return t;
}

u32  find_high_value(u32 n) 
{
	n = reverse(n);
	n = bit_set(n);
	if (n==1)
		return 0;
	int val =((1<<31) / (n>>1));
	printf("%d\n", val);

}

int main()
{
	u32 value;
	while(1) {
		scanf("%d", &value);
//		printf("%x\n", value);
		find_high_value(value);
	}
}
