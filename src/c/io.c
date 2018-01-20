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
	file = fopen(filename, "r");
	
	if (file == NULL) {
		printf("Requested file does not exist.\n");
		exit(EXIT_FAILURE);
	};
	
	//read line by line
	const size_t line_size = 300;
	char * line = malloc(line_size);
	while (fgets(line, line_size, file) != NULL)  {
		char * camera = "CAMERA";
		if (strncmp(line, camera, strlen(camera)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				//printf(line);
			}
		}
		char * canvas = "CANVAS";
		if (strncmp(line, canvas, strlen(canvas)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				//printf(line);
			}
		}
		char * scaling = "SCALING";
		if (strncmp(line, scaling, strlen(scaling)) == 0) {
			if (fgets(line, line_size, file) != NULL) {
				//printf(line);
			}
		}
		char * model = "MODEL";
		if (strncmp(line, model, strlen(model)) == 0) {
			while (fgets(line, line_size, file) != NULL) {
				struct polygon temp = parse_polygon(line);
				printf("%d\n", temp.degree);
			}
		}
	}
	
	if (line) { free(line); }
	fclose(file);
};

struct polygon parse_polygon (char * string) {
	int i, j;
	char * piece;
	char * number;
	char * tmp;
	struct polygon res;
	res.degree = 1;
	
	i = 0;
	for (;;) {
		//printf("%c\n", string[i]);
		if (string[i] == ']' && string[i+1] == '[')
			{ res.degree++; }
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
	
	i = 1;
	xyz * vertex = malloc(3 * res.degree * sizeof(int));
	piece = strtok(string, "][");
	
	number = strtok(piece, ",");
	vertex[0].x = strtol(number, &tmp, 10);
	number = strtok(NULL, ",");
	vertex[0].y = strtol(number, &tmp, 10);
	number = strtok(NULL, ",");
	vertex[0].z = strtol(number, &tmp, 10);
	
	while(i < res.degree) {
		piece = strtok(NULL, "][");
		if (piece) {
			number = strtok(piece, ",");
			vertex[i].x = strtol(number, &tmp, 10);
			number = strtok(NULL, ",");
			vertex[i].y = strtol(number, &tmp, 10);
			number = strtok(NULL, ",");
			vertex[i].z = strtol(number, &tmp, 10);
		}
		i++;
	}
	
	res.vertex = vertex;
	free(vertex);
	return res;
};

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
