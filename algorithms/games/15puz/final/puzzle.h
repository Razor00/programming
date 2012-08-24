struct TREENODE {
	char dir;
	struct TREENODE* paddr;
};

typedef struct TREENODE TREENODE;

struct NODE {
	char arr[17];
	char dir;
	char spos; 
	char gvalue; 
	int depth;
	TREENODE *paddr;
};

typedef struct NODE NODE;

struct LIST {
	NODE node;
	struct LIST *next;
};
typedef struct LIST LIST;
#define swap(a, b, type)  { type c; c = a; a = b; b = c; }
