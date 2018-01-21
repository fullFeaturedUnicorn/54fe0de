#include <stdlib.h>
#include "../h/main.h"

struct line line
(	
	matrix m,
	xy start,
	xy finish,
	int color
)
{
	struct line res;
	int delta_x, delta_y, eps, x, y, counter;

	counter = 0;
	res.color = color;
	delta_x = abs(finish.x - start.x);
	delta_y = abs(finish.y - start.y);
	res.dot = malloc(2 * (delta_x + delta_y) * sizeof(int));

	// Make sure target will not ever exceed actual canvas size
	x = start.x >= m.size_x ? m.size_x : start.x;
	y = start.y >= m.size_y ? m.size_y : start.y;
	x = start.x < 0 ? 0 : start.x;
	y = start.y < 0 ? 0 : start.y;

	if (finish.x >= m.size_x) { finish.x = m.size_x; }
	if (finish.y >= m.size_y) { finish.y = m.size_y; }
	if (finish.x < 0) { finish.x = 0; }
	if (finish.y < 0) { finish.y = 0; }

	int eps_x = 0;
	int eps_y = 0;
	int mod_x = 0;
	int mod_y = 0;
	res.dot[0].x = x;
	res.dot[0].y = y;
	for(;;) {
		if (delta_y != 0 && delta_x != 0) {
			eps_x += abs(delta_x / delta_y);
			eps_y += abs(delta_y / delta_x);
			mod_y += abs(delta_y) % abs(delta_x);
			mod_x += abs(delta_x) % abs(delta_y);
		} else if (delta_y == 0) {
			eps_x += 1;
		} else if (delta_x == 0) {
			eps_y += 1;
		}
				
		if (eps_x >= 1 || mod_x >= delta_y) {
			if (start.x > finish.x) {
				x--;
			} else {
				x++;
			}
			eps_x -= 1;
			mod_x -= delta_y;
		}
		if (eps_y >= 1 || mod_y >= delta_x) {
			if (start.y > finish.y) {
				y--;
			} else {
				y++;
			}
			eps_y -= 1;
			mod_y -= delta_x;
		}

		counter++;
		res.dot[counter].x = x;
		res.dot[counter].y = y;
		if (x == finish.x && y == finish.y) { break; }
		if (x == m.size_x || y == m.size_y) { break; }
		if (x < 0 || y < 0) { break; }
	}
	
	res.amount = counter;
	return res;
};

void draw_line
(
	matrix m,
	xy start,
	xy finish,
	int color
)
{
	int i = 0;
	xy a = start;
	xy b = finish;
	
	if (start.x > finish.x || start.y > finish.y) { 
		a.x = finish.x;
		b.x = start.x;
		a.y = finish.y;
		b.y = start.y;
	}
	
	struct line l =
		line(m, a, b, color);
	while (i <= l.amount) {
		update(m, l.dot[i].x, l.dot[i].y, color);
		i++;
	}
	free(l.dot);
}

void draw_polygon
(
	matrix m,
	struct shape s,
	int color,
	int solid
)
{
	int i;
	xy floating;
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
			ab = line(m, s.vertex[0], s.vertex[1], color);
			bc = line(m, s.vertex[1], s.vertex[2], color);
			ac = line(m, s.vertex[0], s.vertex[2], color);
			
			for (int i = 0; i < ab.amount; i++) {
				floating = ab.dot[i];
				draw_line(m, floating, s.vertex[2], color);
			}
			free(ab.dot);
			
			for (int i = 0; i < bc.amount; i++) {
				floating = bc.dot[i];
				draw_line(m, floating, s.vertex[0], color);
			}
			free(bc.dot);
			
			for (int i = 0; i < ac.amount; i++) {
				floating = ac.dot[i];
				draw_line(m, floating, s.vertex[1], color);
			}
			
			free(ac.dot);
			break;
		default:
			i = 0;
			struct shape tmp;
			tmp.degree = 3;
			
			tmp.vertex = malloc(2 * tmp.degree * sizeof(int));
			tmp.vertex[0] = s.vertex[0];
			tmp.vertex[1] = s.vertex[1];
			tmp.vertex[2] = s.vertex[s.degree - 1];
			draw_polygon(m, tmp, color, 1);
			
			while (i < s.degree - 2) {
				tmp.vertex[0] = s.vertex[i];
				tmp.vertex[1] = s.vertex[i+1];
				tmp.vertex[2] = s.vertex[i+2];
				draw_polygon(m, tmp, color, 1);
				i++;
			}
			
			free(tmp.vertex);
		}
		break;
	}
};

void render_point(
	matrix m,
	xyz point,
	struct camera cam,
	int scaling,
	int color)
{
	struct projection res = project(point, cam, scaling);
	printf("%d: %d %d\n", res.exists, res.pos.x, res.pos.y);
	if (res.exists == 1) {
		update(m, res.pos.x, res.pos.y, color);
	}
}

void render_line
(
	matrix m,
	xyz start,
	xyz finish,
	struct camera cam,
	int scaling,
	int color
)
{
	struct projection res_a = project(start, cam, scaling);
	struct projection res_b = project(finish, cam, scaling);
	if (res_a.exists == 1 && res_b.exists == 1) {
		draw_line(m, res_a.pos, res_b.pos, color);	
	}
};

void render_polygon
(
	matrix m,
	struct polygon p,
	struct camera cam,
	int scaling,
	int color,
	int solid
)
{
	int i = 0;
	int ex = 0;
	struct shape s;
	s.degree = p.degree;
	s.vertex = malloc(p.degree * 3 * sizeof(int));
	struct projection tmp;
	for (;;) {
		if (i == p.degree) { break; }
		tmp = project(p.vertex[i], cam, scaling);
		if (tmp.exists) {
			s.vertex[i] = tmp.pos;
			ex++;
		}
		i++;
	}
	if (ex == p.degree - 1) {
		draw_polygon(m, s, color, solid);
	}
	free(s.vertex);
}
