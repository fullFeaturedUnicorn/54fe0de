#include <stdlib.h>
#include "../h/main.h"

struct dot * line(xy start,
				  xy finish,
				  int value)
{
	int mem,
		delta_x, delta_y, delta,
		eps_x, eps_y, modulo_x, modulo_y,
		x, y;

	struct dot * dot_;
	
	eps_x = eps_y = 0;
	modulo_x = modulo_y = 0;

	int tmp_x[2] = {start.x, finish.x};
	int tmp_y[2] = {start.y, finish.y};
	delta_x = max(tmp_x, 2) - min(tmp_x, 2);
	delta_y = max(tmp_y, 2) - min(tmp_y, 2);
	int deltas[2] = {delta_x, delta_y};
	delta = max(deltas, 2);

	if (delta_x == 0 && delta_y == 0) {
		dot_ = malloc(5 * sizeof(int));
		dot_[0].pos.x = start.x;
		dot_[0].pos.y = start.y;
		dot_[0].color = value;
	} else if (delta_x == 0) {
		dot_ = malloc(5 * delta_y * sizeof(int));
		for (int i = 0; i <= delta_y; i++) {
			dot_[i].pos.x = start.x;
			dot_[i].pos.y = start.y + i;
			if (start.y > finish.y) {
				dot_[i].pos.y = start.x - i;
			}
			dot_[i].color = value;
		}
	} else if (delta_y == 0) {
		dot_ = malloc(5 * delta_x * sizeof(int));
		for (int i = 0; i <= delta_x; i++) {
			dot_[i].pos.y = start.y;
			dot_[i].pos.x = start.x + i;
			if (start.x > finish.x) {
				dot_[i].pos.x = start.x - i;
			}
			dot_[i].color = value;
		}
	} else {
		x = start.x;
		y = start.y;
		mem = hypotenuse(delta_x, delta_y); 
		dot_ = malloc(5 * mem * sizeof(int));
		for (int i = 0; i <= delta; i++) {
			dot_[i].pos.x = x;
			dot_[i].pos.y = y;
			dot_[i].color = value;
			eps_x += delta_x / delta_y;
			eps_y += delta_y / delta_x;
			modulo_x += delta_x % delta_y;
			modulo_y += delta_y % delta_x;
			if (eps_x >= 1 || modulo_x >= delta_y) {
				if (start.x < finish.x) {
					x++;
				} else {
					x--;
				}
				eps_x -= 1;
				modulo_x -= delta_y;
			}
			if (eps_y >= 1 || modulo_y >= delta_x) {
				if (start.y < finish.y) {
					y++;
				} else {
					y--;
				}
				eps_y -= 1;
				modulo_y -= delta_x;
			}
		}
	}
	return dot_;
}

void draw_line(matrix m,
			   xy start,
			   xy finish,
			   int color) {};

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
