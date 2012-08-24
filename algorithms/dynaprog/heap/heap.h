#define swap(a, b, type)  { type c; c = a; a = b; b = c; }
struct huffnode {
	int freq;
	char ch;
	struct huffnode* left;
	struct huffnode* right;
	struct huffnode* addr;
};
typedef struct huffnode hnode;

