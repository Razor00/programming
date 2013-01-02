

char input[200000];
char sequence[12][50];

void cal_occurence(int A, int B, int N, char *input, int n)
{
	char seq[13];
	int seq_tot = 0;
	for (seq_order = A; seq_order <= B, seq_order++) {
		for (seq_tot = 1; seq_tot <= 	get_sequence(seq, 	
	}


}
int main()
{
	FILE *fin, *fout;
	int A, B, N;
	fin = fopen("contact.in", "r");
	fout = fopen("contact.out", "w");

	fscanf(fin, "%d %d %d", &A, &B, &N);
	int n = 0;
	while (1) {
		n = fscanf(fin, "%s", &input[n]);
		if (n != 80)
			break;
	}	
	cal_occurence(A, B, N, input, n);
}

