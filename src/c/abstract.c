#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../h/main.h"

#define PI 3.14159265

int min (int * n, int size) {
	int i = 0;
	int min = n[0];
	while(i < size) {
		if(n[i] < min) {
			min = n[i];
		}
		i++;
	}
	return min;
}

int max (int * n, int size) {
	int i = 0;
	int max = n[0];
	while(i < size) {
		if(n[i] > max) {
			max = n[i];
		}
		i++;
	}
	return max;
}

matrix init
(
	int size_x,
	int size_y,
	int value
)
{
	matrix m;
	m.size_x = size_x;
	m.size_y = size_y;
	m.cell = (int *)malloc(size_x * size_y * sizeof(int));
	for (int i = 0; i < size_x * size_y; i++) {
		m.cell[i] = value;
	}
	return m;
}

/* It is possible to get confused by coordinate system
 * I use. The bottom left corner of the matrix is [0;0],
 * and axis  generally follow common cartesian approach,
 * not a "flipped over" one. Better to incapsulate
 * getting actual position of imaginary "cell". */
int offset
(
	matrix m,
	int pos_x,
	int pos_y
)
{
	int offset_x, offset_y, offset;
	offset_x = m.size_x * abs(m.size_y - pos_y);
	offset_y = m.size_x - pos_x;
	if (offset_x == 0) {
		offset_x = m.size_x;
	}
	offset = offset_x - offset_y;
	if (m.size_x == pos_x) { 
		offset--; 
	}
	return offset;
}

void update
(
	matrix m,
	int pos_x,
	int pos_y,
	int value
)
{
	m.cell[offset(m, pos_x, pos_y)] = value;
}

float distance
(
	xyz start,
	xyz finish
)
{
	int x, y, z;
	x = finish.x - start.x;
	y = finish.y - start.y;
	z = finish.z - start.z;
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
};

xyz center (xyz a, xyz b, xyz c) {
	xyz center;
	float per; // perimeter
	per = distance(a, b) + distance(a, c) + distance(b, c);
	center.x = (a.x + b.x + c.x) / per;
	center.y = (a.y + b.y + c.y) / per;
	center.z = (a.z + b.z + c.z) / per;
	return center;
}

xyz angles (xyz a, xyz b, xyz c) {
	float ab, bc, ac;
	float cos_a, cos_b, cos_c;
	xyz angles_;
	ab = distance(a, b);
	bc = distance(b, c);
	ac = distance(a, c);
	cos_a = (pow(ac, 2) + pow(ab, 2) - pow(bc, 2)) / (2 * ac * ab);
	cos_b = (pow(ab, 2) + pow(bc, 2) - pow(ac, 2)) / (2 * bc * ab);
	cos_c = (pow(bc, 2) + pow(ac, 2) - pow(ab, 2)) / (2 * bc * ac);
	angles_.x = acos(cos_a) * 180 / PI;
	angles_.y = acos(cos_b) * 180 / PI;
	angles_.z = acos(cos_c) * 180 / PI;
	return angles_;
}

struct intersection intersect_triangle
(
	xyz line_start,
	xyz line_finish,
	struct polygon t
)
{
	if (t.degree == 3) {
		xyz plane;
		struct intersection res;
		double d, angle, mu;
		double eps = 0.003;

		xyz * v;
		int i = 0;
		v = malloc(3 * 3 * sizeof(int));
		for(;;) {
			if (i == 3) { break; };
			v[i] = t.vertex[i];
			i++;
		}
		
		plane.x =
			(v[2].y - v[1].y) * (v[3].z - v[1].z) -
			(v[2].z - v[1].z) * (v[3].y - v[1].y);
		plane.y =
			(v[2].z - v[1].z) * (v[3].x - v[1].x) -
			(v[2].x - v[1].x) * (v[3].z - v[1].z);
		plane.z =
			(v[2].x - v[1].x) * (v[3].y - v[1].y) -
			(v[2].y - v[1].y) * (v[3].z - v[1].x);
		d = (plane.x * v[1].x) -
			(plane.y * v[1].y) -
			(plane.z * v[1].z);
		d = -d;
		angle =
			plane.x * (line_finish.x - line_start.x) +
			plane.y * (line_finish.y - line_start.y) +
			plane.z * (line_finish.z - line_start.z);
		res.exists = 0; res.in_range = 0;
		res.pos = (xyz) {-1,-1,-1};
		if (fabs(angle) > eps) {
			res.exists = 1;
			mu = (d +
				  (plane.x * line_start.x) +
				  (plane.y * line_start.y) +
				  (plane.z * line_start.z)) / angle;
			mu = -mu;
			res.pos.x = line_start.x + mu * (line_finish.x - line_start.x);
			res.pos.y = line_start.y + mu * (line_finish.y - line_start.y);
			res.pos.z = line_start.z + mu * (line_finish.z - line_start.z);
			if (mu > 0 && mu < 1) {
				res.in_range = 1;
			}
		}
		free(v);
		return res;
	} else {
		printf("Asked for intersection between line\n");
		printf("and something that isn't a triangle.\n");
		exit(EXIT_FAILURE);
	}
}

struct projection project
(
	xyz point,
	struct camera cam,
	int scaling
)
{
	/*                  D
	y z            . .  |
	|/     B  . .     K-| // Something like this
	-->x   -------------- // It supposed to be triangles
	       |     ..    O  // but I am not very good at drawing
	       A */
	       
	struct projection res;
	struct polygon canvas;
	float ao, bo, ab, cos_bao;
	canvas.degree = 3; // Triangle is enough to define entire plane
	canvas.vertex = malloc(3 * 3 * sizeof(int));
	int i = 0;
	
	for (;;) {
		if (i == 3) { break; }
		canvas.vertex[i] = cam.canvas[i];
		i++;
	}

	res.exists = 0;
	res.pos = (xy) {-1,-1};
	struct intersection p =
		intersect_triangle(point, cam.lens, canvas);
	if (p.exists == 1) {
		ao = distance(cam.canvas[0], p.pos);
		bo = distance(cam.canvas[1], p.pos);
		ab = distance(cam.canvas[0], cam.canvas[1]);
		cos_bao = (pow(ab,2) + pow(ao,2) + pow(bo,2)) / (2 * ao * ab);
		if (cos_bao > 0 && cos_bao < 1) {
			res.exists = 1;
			res.pos.x = (int) (ao * scaling * sin(acos(cos_bao)));
			res.pos.y = (int) (ao * scaling * cos_bao);
		}
	}
	free(canvas.vertex);
	return res;
}
