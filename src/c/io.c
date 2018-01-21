#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include "../h/main.h"
#include "../h/io.h"

/* Everything that happens here is specific 
 * to POSIX-compatible system. If your system is not
 * POSIX-compatible, it is not gonna work, you 
 * have been warned. */

void render 
(
	char * model, 
	char * output
)
{
	FILE * file;
	size_t len = 0;
	ssize_t read;
	char * tmp;
	file = fopen(model, "r");
	
	/* CONFIGURATION */
	matrix m;
	int degree;
	int scaling_int;
	struct camera cam;
	
	/* HELPER VALUES */
	int canvas_size_x;
	int canvas_size_y;
	int bg; // background
	int default_col; // default color, if 
	//not specified explicitly
	int draw_edges;
	
	/* Strings for comparison */
	char * comment = "//";
	char * color = "COLOR";
	char * edges = "EDGES";
	char * camera = "CAMERA";
	char * canvas = "CANVAS";
	char * scaling = "SCALING";
	char * model_str = "MODEL";
	char * background = "BACKGROUND";
	
	struct polygon p;
	
	if (file == NULL) {
		printf("Requested file does not exist.\n");
		exit(EXIT_FAILURE);
	};
	
	const size_t line_size = 300;
	char * line = malloc(line_size * sizeof(char));
	p.vertex = malloc((line_size/3) * 3 * sizeof(int));
	while (fgets(line, line_size, file) != NULL)  {
		if (strncmp(line, camera, strlen(camera)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				parse_polygon(&degree, p, line);
				cam.lens = p.vertex[0];
			}
		}
		if (strncmp(line, canvas, strlen(canvas)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				parse_polygon(&degree, p, line);
				for(int i = 0; i < 4; i++) {
					cam.canvas[i] = p.vertex[i];
				}
			}
		}
		if (strncmp(line, background, strlen(background)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				bg = strtol(line, &tmp, 10);
			}
		}
		if (strncmp(line, color, strlen(color)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				default_col = strtol(line, &tmp, 10);
			}
		}
		if (strncmp(line, edges, strlen(edges)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				draw_edges = strtol(line, &tmp, 10);
			}
		}
		if (strncmp(line, scaling, strlen(scaling)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				scaling_int = strtol(line, &tmp, 10);
			}
		}
		// Now we have enough data to initialize matrix
		if (strncmp(line, model_str, strlen(model_str)) == 0) {
			canvas_size_x = (int)distance(cam.canvas[1], cam.canvas[2]);
			canvas_size_y = (int)distance(cam.canvas[0], cam.canvas[1]);
			m = init
			(
				canvas_size_x * scaling_int, 
				canvas_size_y * scaling_int, 
				bg
			);
			while (fgets(line, line_size, file) != NULL) {
				if (strncmp(line, comment, strlen(comment)) == 0) {
					// do nothing
				} else {
					parse_polygon(&degree, p, line);
					p.degree = degree;
					draw
					(
						m, p, cam, 
						draw_edges,
						scaling_int, 
						default_col
					);
				}
			}
		}
	}
	
	if (line) { free(line); }
	free(p.vertex);
	fclose(file);
	
	write_pgm(output, m);
	free(m.cell);
};

void parse_polygon 
(
	int * degree,
	struct polygon p,
	char * string
) 
{
	int i;
	char * piece;
	char * number;
	char * tmp;
	
	i = 0;
	*degree = 1;
	for (;;) {
		if (string[i] == ']' && string[i+1] == '[')
			{ *degree = *degree + 1; }
		if (string[i] == ']' && string[i+1] == ']')
			{ break; }
		if (i == 300) {
			printf("Provided model is broken. It's either:\n");
			printf("1. File contains single line longer than 300 characters.\n");
			printf("2. You forgot double brackets at the end.\n");
			printf("3. Your parents were related. I'm sorry.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	
	i = 0;
	while (piece = strsep(&string, "][")) {
		if (strlen(piece) > 1) {
			number = strsep(&piece, ",");
			p.vertex[i].x = strtol(number, &tmp, 10);
			number = strsep(&piece, ",");
			p.vertex[i].y = strtol(number, &tmp, 10);
			number = strsep(&piece, ",");
			p.vertex[i].z = strtol(number, &tmp, 10);
			i++;
		}
	}
};

void draw
(
	matrix m,
	struct polygon p,
	struct camera cam,
	int edges,
	int scaling,
	int color
)
{
	switch (p.degree) {
	case 1:
		render_point 
		(
			m, 
			p.vertex[0], 
			cam, scaling, color
		);
		break;
	case 2:
		render_line
		(
			m, 
			p.vertex[0], p.vertex[1], 
			cam, scaling, color
		);
		break;
	default:
		if (edges == 0) {
			render_polygon(m, p, cam, scaling, color, 1);
		} else if (edges == 1) {
			render_polygon(m, p, cam, scaling, color, 1);
			render_polygon(m, p, cam, scaling, 0, 0);
		} else {
			render_polygon(m, p, cam, scaling, 0, 0);
		}
	}
}

void write_pgm (char * filename, matrix m) {
	int i, j;
	FILE * file;
	file = fopen(filename, "w+");
	fprintf(file, "P2\n");
	fprintf(file, "%d %d\n", m.size_x, m.size_y);
	fprintf(file, "%d\n", max(m.cell, m.size_x * m.size_y));

	// Strings must be written in reverse order
	for (i = m.size_y - 1; i >= 0; i--) {
		for (j = 0; j < m.size_x; j++) {
			fprintf(file, "%d ", m.cell[offset(m, j, i)]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}
