/* ----- */
/* Types */
/* ----- */

typedef struct xy_ {
	int x;
	int y;
} xy;

typedef struct xyz_ {
	int x;
	int y;
	int z;
} xyz;

typedef struct matrix_ {
	int size_x;
	int size_y;
	int * cell;
} matrix;

/* ---------- */
/* Structures */
/* ---------- */

struct dot {
	xy pos;
	int color;
};

struct polygon {
	xyz * vertex;
};

/* --------- */
/* Functions */
/* --------- */

int min(int * n);
int max(int * n);
int hypotenuse(int ab, int ac);

matrix init(int size_x,
			int size_y,
			int value);

int offset(matrix m,
		   int pos_x,
		   int pos_y);

void update(matrix m,
			int pos_x,
			int pos_y,
			int value);
