#include <stdlib.h>
#include "../h/main.h"

int main() {
	matrix m = init(150,100,15);
	xy start = (xy) {52,78};
	xy finish = (xy) {112,4};
	//draw_line(m, start, finish, 0);

	struct shape triangle;
	triangle.degree = 3;
	triangle.vertex = malloc(2 * 3 * sizeof(int));
	triangle.vertex[0] = (xy) {52,78};
	triangle.vertex[1] = (xy) {78, 92};
	triangle.vertex[2] = (xy) {112, 4};
	draw_polygon(m, triangle, 9, 1);
	draw_polygon(m, triangle, 3, 0);
	
	write_pgm("./tmp/out.pgm", m);
	free(m.cell);
}
