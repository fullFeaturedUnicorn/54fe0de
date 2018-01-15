#include <stdlib.h>
#include "../h/main.h"

struct line line(matrix m,
				 xy start,
				 xy finish,
				 int color)
{
	struct line res;
	int delta_x, delta_y, eps, x, y, counter;

	counter = 0;
	res.color = color;
	delta_x = abs(finish.x - start.x);
	delta_y = abs(finish.y - start.y);
	res.dot = malloc(2 * (delta_x + delta_y) * sizeof(int));

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
		res.dot[counter].x = x;
		res.dot[counter].y = y;
		if (x == finish.x || y == finish.y) { break; }
		if (eps > -delta_x) {
			if (start.x > finish.x) {
				x--;
			} else {
				x++;
			}
			eps -= delta_y;
		}
		if (eps < delta_y) {
			if (start.y > finish.y) {
				y--;
			} else {
				y++;
			}
			eps += delta_x;
		}
		counter++;
	}

	res.amount = counter;
	return res;
};

void draw_line(matrix m,
			   xy start,
			   xy finish,
			   int color)
{
	int i = 0;
	struct line l =
		line(m, start, finish, color);
	while (i < l.amount) {
		update (m, l.dot[i].x, l.dot[i].y, color);
		i++;
	}
	free(l.dot);
}

void draw_polygon(matrix m,
				  struct shape s,
				  int color,
				  int solid)
{
	int i;
	xy floating;
	printf("%d\n", solid);
	struct line ab, bc, ac;
	switch (solid) {
	case 0:
		i = 0;
		draw_line(m,
				  s.vertex[0],
				  s.vertex[s.degree - 1],
				  color);
		while (i < s.degree - 1) {
			draw_line(m,
					  s.vertex[i],
					  s.vertex[i+1],
					  color);
			i++;
		}
		break;
	case 1:
		switch (s.degree) {
		case 3:
			draw_polygon(m, s, color, 0);
			ab = line(m, s.vertex[0], s.vertex[1], color);
			bc = line(m, s.vertex[1], s.vertex[2], color);
			ac = line(m, s.vertex[0], s.vertex[2], color);
			for (int i = 0; i < ab.amount; i++) {
				floating = ab.dot[i];
				draw_line(m, s.vertex[2], floating, color);
			}
			free(ab.dot);
			/*
			for (int i = 0; i < bc.amount; i++) {
				floating = bc.dot[i];
				draw_line(m, s.vertex[0], floating, color);
			}
			free(bc.dot);
			for (int i = 0; i < ac.amount; i++) {
				floating = ac.dot[i];
				draw_line(m, s.vertex[1], floating, color);
			}
			free(ac.dot);
			*/
			break;
		}
		break;
	}
};

void render_line(matrix m,
				 xyz start,
				 xyz finish,
				 struct camera cam,
				 int scaling,
				 int color) {};

void render_polygon(matrix m,
					struct polygon p,
					struct camera cam,
					int scaling,
					int color,
					int solid) {}
