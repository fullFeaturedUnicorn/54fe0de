void render (char * model, char * output);
void write_pgm (char * filename, matrix m);
void parse_polygon 
(
	int * degree, 
	struct polygon p, 
	char * string
);
void draw (
	matrix m,
	struct polygon p,
	struct camera cam,
	int edges,
	int scaling,
	int color
);
