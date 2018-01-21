#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/main.h"
#include "../h/io.h"

static char * model;
static char * output;
static char * usage = "main -f /path/to/model -o output.pgm";

int main(int argc, char * argv[]) {
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-f") == 0) {
			model = argv[i + 1];
		}
		if (strcmp(argv[i], "-o") == 0) {
			output = argv[i + 1];
		}
	}
	if (model && output) {
		render(model, output);
		return 0;
	} else {
		printf("%s", usage);
		exit(EXIT_FAILURE);
	}
}
