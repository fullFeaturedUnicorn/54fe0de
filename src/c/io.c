#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include "../h/main.h"

/* Everything that happens here is specific 
 * to POSIX-compatible system. If your system is not
 * POSIX-compatible, it is not gonna work, you 
 * have been warned. */

void read_model (char * filename) {
	FILE * file;
    size_t len = 0;
    ssize_t read;
    char * tmp;
	file = fopen(filename, "r");
	
	/* CONFIGURATION */
	matrix m;
	int scaling_int;
	struct camera cam;
	int degree;
	
	/* HELPER VALUES */
	int canvas_size_x;
	int canvas_size_y;
	
	struct polygon p;
	
	if (file == NULL) {
		printf("Requested file does not exist.\n");
		exit(EXIT_FAILURE);
	};
	
	//read line by line
	const size_t line_size = 300;
	char * line = malloc(line_size * sizeof(char));
	p.vertex = malloc((line_size/3) * 3 * sizeof(int));
	while (fgets(line, line_size, file) != NULL)  {
		char * camera = "CAMERA";
		if (strncmp(line, camera, strlen(camera)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				parse_polygon(&degree, p, line);
				cam.lens = p.vertex[0];
			}
		}
		char * canvas = "CANVAS";
		if (strncmp(line, canvas, strlen(canvas)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				parse_polygon(&degree, p, line);
				for(int i = 0; i < 4; i++) {
					cam.canvas[i] = p.vertex[i];
				}
			}
		}
		char * scaling = "SCALING";
		if (strncmp(line, scaling, strlen(scaling)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				scaling_int = strtol(line, &tmp, 10);
			}
		}
		// Now we have enough data to initialize matrix
		char * model = "MODEL";
		if (strncmp(line, model, strlen(model)) == 0) {
			canvas_size_x = (int)distance
				(cam.canvas[1], cam.canvas[2]);
			canvas_size_y = (int)distance
				(cam.canvas[0], cam.canvas[1]);
			printf("%d %d\n", canvas_size_x, canvas_size_y);	
			while (fgets(line, line_size, file) != NULL) {
				parse_polygon(&degree, p, line);
				p.degree = degree;
			}
		}
	}
	
	if (line) { free(line); }
	free(p.vertex);
	fclose(file);
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
		//printf("%c\n", string[i]);
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

void render 
(
	matrix m
)
{
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
