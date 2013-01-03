

char input[200000];
char sequence[12][50];

void get_next(char *str, int l)
{
    int i;

    for (i = l - 1; i >= 0; i--) {
            if (str[i] == '0') {
                str[i] = '1';
                break;
            }
            str[i] = '0';
    }
}

int get_count(char *inp, char *seq, int len, int n)
{
	int cnt = 0;
	char *end_inp = inp + n;
	while (inp < end_inp) {
		if (strncmp(inp, seq, len) == 0)
			cnt++;
			inp += len;
			continue;
		}
		inp++;
	}
}
void cal_occurence(int A, int B, int N, char *input, int n)
{
	char seq[13] = {};
	int i = 1;
	for (seq_order = A; seq_order <= B, seq_order++) {
		memset(seq, 0, sizeof(seq));
		sequence[seq_order][i] = get_count(input, seq, seq_order, n);
		for (i = 2; i < (1 << seq_order); i++) {
			get_next(seqi, seq_order);
			sequence[seq_order][i] = get_count(input, seq, seq_order, n);
		}
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

