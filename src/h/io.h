/* Entry point to the program, function that calls everything
 * else in required order so the program works as expected. 
 * /derp\ */
void render (char * model, char * output);

/* Function that accepts matrix of values and translates it 
 * into an commonly accepted image format */
void write_pgm (char * filename, matrix m);

/* Helper function to translate my homebrew config file's
 * way of storing polygon's properties into actual c objects */
void parse_polygon 
(
	int * degree, 
	struct polygon p, 
	char * string
);

/* Draw whatever is written in string as a polygon, 
 * update matrix of values with resulting numbers */
void draw (
	matrix m,
	struct polygon p,
	struct camera cam,
	int edges,
	int scaling,
	int color
);
