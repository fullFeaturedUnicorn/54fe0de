/* ----- */
/* Types */
/* ----- */

/* Coordinates in 2-dimantional space */
typedef struct xy_ {
	int x;
	int y;
} xy;

/* Coordinates in 3-dimantional space */
typedef struct xyz_ {
	int x;
	int y;
	int z;
} xyz;

/* Rectangle with width equal to size_x and 
 * height equal to size_y, filled with numbers */
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
	int degree;
	xyz * vertex;
};

struct camera {
	xyz lens;
	xyz canvas[4];
};

/* --------- */
/* Functions */
/* --------- */

/* Create matrix with with equal to size_x
 * and height equal to size_y with 
 * value assigned to every cell */
matrix init(int size_x,
			int size_y,
			int value);

/* While matrix stored in memory as 1-dimentional array, 
 * get offset of cell, correspronding to its 
 * cartesian [x,y] position */
int offset(matrix m,
		   int pos_x,
		   int pos_y);

/* Assign value to [pos_x, pos_y] cell in matrix */
void update(matrix m,
			int pos_x,
			int pos_y,
			int value);
