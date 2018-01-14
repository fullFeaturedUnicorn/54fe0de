#include <math.h>
#include <stdlib.h>
#include "../h/abstract.h"

#define PI = 3.14159265

// Obligatory pair of dumb functions, because C99 is awesome;

int min (int * n) {
	int i = 1;
	int min = n[0];
	while(n[i]) {
		if(n[i] < min) {
			min = n[i];
		}
		i++;
	}
	return min;
}

int max(int * n) {
	int i = 1;
	int max = n[0];
	while(n[i]) {
		if(n[i] > max) {
			max = n[i];
		}
		i++;
	}
	return max;
}

matrix init(int size_x,
			int size_y,
			int value)
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

int offset(matrix m,
		   int pos_x,
		   int pos_y)
{
	int offset_x, offset_y, offset;
	offset_x = m.size_x * abs(m.size_y - pos_y);
	offset_y = m.size_x - pos_x;
	if (offset_x == 0) {
		offset_x = m.size_x;
	}
	offset = offset_x - offset_y;
	return offset;
}

void update(matrix m,
			int pos_x,
			int pos_y,
			int value)
{
	m.cell[offset(m, pos_x, pos_y)] = value;
}
