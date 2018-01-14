#include <stdlib.h>
#include "../h/main.h"

void draw_line(matrix m,
			   xy start,
			   xy finish,
			   int color)
{
	int delta_x, delta_y, eps, x, y;
	
	delta_x = abs(finish.x - start.x);
	delta_y = abs(finish.y - start.y);

	// Make sure target will not ever exceed actual canvas size
	x = start.x >= m.size_x ? m.size_x - 1 : start.x;
	y = start.y >= m.size_y ? m.size_y - 1 : start.y;
	x = start.x < 0 ? 0 : start.x;
	y = start.y < 0 ? 0 : start.y;

	if (finish.x >= m.size_x) { finish.x = m.size_x - 1; }
	if (finish.y >= m.size_y) { finish.y = m.size_y - 1; }
	if (finish.x < 0) { finish.x = 0; }
	if (finish.y < 0) { finish.y = 0; }

	eps = delta_x > delta_y ? delta_x : -delta_y;
	
	for (;;) {
		update(m, x, y, color);
		if (x == finish.x && y == finish.y) { break; }
		if (eps > -delta_x) {
			if (start.x < finish.x) {
				x--;
			} else {
				x++;
			}
			eps -= delta_y;
		}
		if (eps < delta_y) {
			if (start.y < finish.y) {
				y--;
			} else {
				y++;
			}
			eps += delta_x;
		}
	}
};

void draw_polygon(matrix m,
				  xy * verticles,
				  int color,
				  int solid) {};

void render_line(matrix m,
				 xyz start,
				 xyz finish,
				 struct camera cam,
				 int scaling,
				 int color) {};

void render_polygon(matrix m,
					xyz * verticles,
					struct camera cam,
					int scaling,
					int color,
					int solid) {}
