#include <stdio.h>
#include "../h/main.h"

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
