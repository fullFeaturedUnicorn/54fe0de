#include <string.h>
#include "../h/main.h"

int main(int argc, char * argv[]) {
	/*
	int scaling = 1;
	matrix m = init(150,100,15);
	struct camera cam;
	cam.canvas[0] = (xyz) {0,0,0};
	cam.canvas[1] = (xyz) {0,100,0};
	cam.canvas[2] = (xyz) {0,100,150};
	cam.canvas[3] = (xyz) {0,150,100};
	cam.lens = (xyz) {100,50,75};
	
	write_pgm("./tmp/out.pgm", m);
	free(m.cell);
	*/
	int scaling;
	struct camera cam;
	
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-f") == 0) {
			char * filename = argv[i + 1];
			read_model(filename);
		}
		if (strcmp(argv[i], "-o") == 0) {
			char * output = argv[i + 1];
			//printf("%s", output);
		}
	}
	return 0;
}
