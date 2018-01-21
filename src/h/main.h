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

struct line {
	int color;
	int amount;
	xy * dot;
};

struct shape {
	int degree;
	xy * vertex;
};

struct polygon {
	int degree;
	xyz * vertex;
};

struct camera {
	xyz lens;
	xyz canvas[4];
};

struct intersection {
	int exists;
	int in_range;
	xyz pos;
};

struct projection {
	int exists;
	xy pos;
};

/* --------- */
/* Functions */
/* --------- */

int min (int * n, int size);
int max (int * n, int size);

/* Create matrix with with equal to size_x
 * and height equal to size_y with 
 * value assigned to every cell */
matrix init
(
	int size_x,
	int size_y,
	int value
);

/* While matrix stored in memory as 1-dimentional array, 
 * get offset of cell, correspronding to its 
 * cartesian [x,y] position */
int offset
(
	matrix m,
	int pos_x,
	int pos_y
);

/* Determine normalized distance between two points in 
 * 3-dimentional space */
float distance (xyz start, xyz finish);

/* Assign value to [pos_x, pos_y] cell in matrix */
void update
(
	matrix m,
	int pos_x,
	int pos_y,
	int value
);

/* Return array of points for drawing straight line */
struct line line
(
	matrix m,
	xy start,
	xy finish,
	int color
);

/* Draw closest raster representation of straight line
 * on given matrix */
void draw_line
(
	matrix m,
	xy start,
	xy finish,
	int color
);

/* Draw polygon vith veriable amount of vertex
* (including triangle). Draw only perimeter if 
* solid = 0, draw fill all points inside polygon 
* with color if solid = 1 */
void draw_polygon
(
	matrix m,
	struct shape s,
	int color,
	int solid
);
				  
struct projection project
(
	xyz point,
	struct camera cam,
	int scaling
);

void render_point
(
	matrix m,
	xyz point,
	struct camera cam,
	int scaling,
	int color
);

void render_line
(
	matrix m,
	xyz start,
	xyz finish,
	struct camera cam,
	int scaling,
	int color
);
	
void render_polygon
(
	matrix m,
	struct polygon p,
	struct camera cam,
	int scaling,
	int color,
	int solid
);
