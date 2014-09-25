#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *swap(char *s, int len)
{
	int st, end;
	int ch;
	st = 0;
	end = st + len - 1;
	while (st <= end) {
		ch = s[st];
		s[st] = s[end];
		s[end] = ch;
		st++;
		end--;
	}
	return s;
}

void print(char *s, int len)
{
	int i;
	for (i = len-1; i >= 0; i--)
		printf("%d", s[i]);
	printf("\n");
}

/* len of s should be greater than 1 */	 
char *strip_leading_zeros(char *s)
{
	for (; *s == '0'; s++);

	if (*s == '\0')
		s--;

	return s;

}


char *process(char *s, int len)
{
	int i;
	swap(s, len);
	for (i = 0; i < len; i++) {
		s[i] = s[i] -'0';
	}
	return s;
}
		
char *reprocess(char *s, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		s[i] = s[i] + '0';
	}
	swap(s, len);
	s[len] ='\0';
	return s;
}
	
/* Assumption: each array cell occupy one element and  (not a char)
 LSB start first in the array
 Array is sufficiently large to accomodate a carry 
 return the length of the C array 
 Assumption A greater than B*/
int add(char *A, char *B, int alen, int blen, char *C)
{
	int i, s, c;
	c = 0;
	for (i = 0; i < blen; i++) {
		s = A[i] + B[i] + c; 
		c = s/10;
		C[i] = s%10;
	}
	for (; i < alen; i++) {
		s = A[i] + c; 
		c = s/10;
		C[i] = s%10;
	}
	
	if (c)
		C[i++] = c;
	
	i--;
	while (i >= 0 && C[i] == 0)
		i--;

	if (i == -1)
		i = 0;
	return i+1;
}
/* A > B */
int sub(char *A, char *B, int alen, int blen, char *C)
{
	/* take 9's complement of B */
	int c, s;
	int i;
	
	c = 1;
	for (i = 0; i < blen; i++) {
		s = A[i] + (9 - B[i]) + c;
		c = s/10;
		C[i] = s%10;
	}
	for (; i < alen; i++) {
		s = A[i] + (9 - 0) + c;
		c = s/10;
		C[i] = s%10;
	}
#if 0 
	/*discard carry, will always get a carry */
	if (c)
		C[i++] = c;
#endif

	i--;
	while (i >= 0 && C[i] == 0)
		i--;

	if (i == -1)
		i = 0;
	
	return i+1;
}
/* Assumption A > B */
int mul(char *A, char *B, int alen, int blen, char *C)
{

	int i, j, s, c;
	memset(C, 0, alen + blen);
	for (i = 0; i < blen; i++) {
		c = 0;
		for (j = 0; j < alen; j++) {
			s = C[i+j] + A[j] * B[i] + c; 
			c = s/10;
			C[i+j] = s%10;
		}
		if (c) {
			C[i+j] = c;
		}
	}
	if (c)
		return i+j;
	else
		return i+j-1;
}

/* Assumption A > B 
 * Data to be stored from MSB onwards
 */
int divide(char *A, long long int b, int alen, char *C)
{
	long long int q; 
	int n, i, k;
	int first_time;
	n = alen;
	k = 0;

	swap(A, alen);

	first_time = 1;
	q = A[0];
	for (i = 1; i < n;) {
		if (q >= b) {
			C[k++] = q / b;
			q = q % b;			
			first_time = 0;
		}
		else {
			q = q * 10 + A[i++];
			if (q < b) 
				if (!first_time)
					C[k++] = 0;
		}
	}
	if (q >= b) 
		C[k++] = q/b;

	if (k == 0) {
		C[0] = 0;
		k = 1;
	}
	else {
		swap(C, k);
	}
	return k;
}
int compare(char *s1, char *s2, int s1_len, int s2_len)
{
	char *s1_end = s1 + s1_len;
	char *s2_end = s2 + s2_len;

	while (s1 < s1_end) {
		if (*s1 != 0)
			break;
		s1++;
	}	
	s1_len = s1_end - s1;
			
	while (s2 < s2_end) {
		if (*s2 != 0)
			break;
		s2++;
	}
	s2_len = s2_end - s2;

	if (s1_len < s2_len)
		return -1;
	
	if (s1_len > s2_len)
		return 1;

	int i;
	for (i = 0; i < s1_len; i++)
		if (s1[i] < s2[i])
			return -1;

		else if (s1[i] > s2[i])
			return 1;

	return 0;
}
/*Assumption A > B */
int long_divide(char *A, char *B, int alen, int blen, char *C)
{
	char q[300];
	char r[300];
	char s[300];
	char *Aend;
	char Brev[300];
	int qlen, rlen, slen;
	int ret;
	int first_time;


	int n, i, k, p;
	n = alen;
	k = 0;

	Aend = A + alen;

	/* division uses MSB to LSB order, so change the numbers */
	swap(A, alen);
	memcpy(Brev, B, blen);
	swap(B, blen);
	
	if (compare(A, B, alen, blen) < 0) {
		C[0] = 0;
		return 1;
	}
/*	qlen = blen-1;
	memcpy(q, A, qlen);
	A += qlen;
*/
	qlen = 0;
	first_time = 1;	
	while (1) {
		ret = -1;

		while (A < Aend) {
			q[qlen++] = *A++;
			if ((ret = compare(q, B, qlen, blen)) >= 0) 
				break;
			if (!first_time)
				C[k++] = 0;
		}

		if (A >= Aend && ret < 0)
			break;

		/* q >= B */
		char T[1];
		for (p = 9; p >= 1; p--) {
			T[0] = p;
			rlen = mul(Brev, T, blen, 1, r);   
			/* mul, sub uses reverse implementation*/
			swap(r, rlen);	
			if ((ret = compare(r, q, rlen, qlen)) <= 0) {
				slen = sub(swap(q, qlen), swap(r, rlen), qlen, rlen, s); 
				swap(s, slen);
				/* if exactly divisible reset qlen to 0 */
				if (slen == 1 && s[0] == 0) {
					qlen = 0;
				}
				else {
					memcpy(q, s, slen);
					qlen = slen;
				}
				C[k++] = p;
				first_time = 0;
				break;
			}
		}
	}

	swap(C, k);
	/*remove leading zeros*/
	return k;
}

int evaluate(char *A, char *B, char *C, char op)
{
	char asign, bsign;
	int alen, blen;

	asign = A[0];
	bsign = B[0];
	if (asign != '-')
		asign = '+';
	else
		A++;

	if (bsign != '-') 
		bsign = '+';
	else
		B++;

	A = strip_leading_zeros(A);
	B = strip_leading_zeros(B);

	alen = strlen(A);
	blen = strlen(B);
	
	char *s1, *s2;
	
	int ret, k;
	int s1_len, s2_len;
	char s1_sign, s2_sign;

	if (alen == blen)
		ret = strcmp(A, B);
	else
		ret = alen < blen? -1: 1;

	if (ret < 0) {
		s1		= B;
		s1_len	= blen;
		s1_sign = bsign;
		
		s2		= A;
		s2_len	= alen;
		s2_sign = asign;
	}
	else if (ret > 0) {
		s1		= A;
		s1_len	= alen;
		s1_sign = asign;

		s2		= B;
		s2_len	= blen;
		s2_sign = bsign;
	}
	else if (ret == 0) {
		/* optimization */
		if (op == '+' && (asign != bsign)) {
			C[0] = '0';
			C[1] = '\0';
			return;
		}
		s1 = A;
		s2 = B;
		s1_len = alen;
		s2_len = blen;
	}
	process(s1, s1_len);
	process(s2, s2_len);

	switch (op) {

		case '+':

			/*four cases*/
			/*case 1 s1 +ve, s2 +ve*/
			if (s1_sign == '+' && s2_sign == '+') {
				k = add(s1, s2, s1_len, s2_len, &C[0]); 
				reprocess(&C[0], k);
			}

			/*case 2 s1 -ve, s2 -ve*/
			if (s1_sign == '-' && s2_sign == '-') {
				k = add(s1, s2, s1_len, s2_len, &C[1]); 
				C[0] = '-';
				reprocess(&C[1], k);
			}

			/*case 3 s1 +ve, s2 -ve*/
			if (s1_sign == '+' && s2_sign == '-') {
				k = sub(s1, s2, s1_len, s2_len, &C[0]); 
				reprocess(&C[0], k);
			}

			/*case 4 s1 -ve, s2 +ve*/
			if (s1_sign == '-' && s2_sign == '+') {
				k = sub(s1, s2, s1_len, s2_len, &C[1]); 
				C[0] = '-';
				reprocess(&C[1], k);
			}
		break;
		
		case '*':
			/* one of them is zero */
			if ((s1_len == 1 && s1[0] == 0) ||
				(s2_len == 1 && s2[0] == 0)) {
				C[0] = '0';
				C[1] = '\0';
				return;
			}

			/*case 1 s1 +ve, s2 +ve*/
			/*case 2 s1 -ve, s2 -ve*/
			if (s1_sign == s2_sign) { 
				k = mul(s1, s2, s1_len, s2_len, &C[0]); 
				reprocess(&C[0], k);
			}

			/*case 3 s1 +ve, s2 -ve*/
			/*case 4 s1 -ve, s2 +ve*/
			if (s1_sign == '+' && s2_sign == '-') {
				k = mul(s1, s2, s1_len, s2_len, &C[1]); 
				C[0] = '-';
				reprocess(&C[1], k);
			}

		break;

		case '/':
			if (blen == 1 && B[0] == 0) {
				printf("Divide by Zero!!\n");
				return;
			}
			/*case 1 s1 +ve, s2 +ve*/
			/*case 2 s1 -ve, s2 -ve*/
			int off = 0;
			if (s1_sign != s2_sign)  
				off = 1;
#if 0
			reprocess(B, blen);
			long long int b = atoll(B);
			if (b <= 922337203685477580) 
				k = divide(A, b, alen, &C[off]);
			else 
#endif
				k = long_divide(A, B, alen, blen, &C[off]);

			if (off)
				C[0] = '-';
			reprocess(&C[off], k);
		break;
	}
}

int main()
{
	char A[300];
	char B[300];
	char C[300];
	char D[300];
	char t[1]={1};
	int alen, clen;
	int k;
	int even;

	int ret;
#if 0
	while (scanf("%s", A) != EOF) {
		alen = strlen(A);
		process(A, alen);
		swap(A, alen);
		memcpy(B, A, alen);
		k = alen;
		even = 1;
		if (A[0] % 2 != 0) {
			k = add(A, t, alen, 1, B); 
			even = 0;
		}
		//	  print(B, k);
		k = div(B, 2, k, C);
		//	  print(C, k);

		clen = k;
		k = mul(C, C, clen, clen, D);
		//	  print(D, k);

		if (even) {
			k = add(D, C, k, clen, A);
			print(A, k);
		}
		else {
			print(D, k);
		}
	}
//#else
	char T[3];
	while (scanf("%s", A) != EOF) {
		if (A[0] == '1' && A[1] == '\0') {
			printf("1\n");
			continue;
		}
		//(n-1)
		T[0] = '-';
		T[1] = '1';
		T[2] = '\0';
		evaluate(A, T, C, '+'); 
		printf("%s\n", C);
		
		// C = n - 1, now do 2C 
		T[0] = '2';
		T[1] = '\0';
		evaluate(C, T, A, '*'); 
		printf("%s\n", A);
	}
#endif
	scanf("%s %s", A, B);
	evaluate(A, B, C, '/');
	printf("%s\n", C);
	return 0;
}

