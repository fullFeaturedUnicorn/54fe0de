#include <stdio.h>
#include "../tests/tests.h"
#include "../src/h/main.h"

int main() {
	test_all();
}

void test_min() {	
	int test1[11] = {1,2,3,4,5,6,7,8,9,10,11};
	int test2[5] = {9,172635,1,12,-52};
	int test3[4] = {50,10,0,12};

	int exp1 = 1;
	int exp2 = -52;
	int exp3 = 0;

	int i = 0; int c = 3;
	if (min(test1, 11) == exp1) { i++; }
	if (min(test2, 5) == exp2) { i++; }
	if (min(test3, 4) == exp3) { i++; }
	if (i == c) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL at test #%d\n", c);
	}
};

void test_max() {
	int test1[7] = {1,2,3,4,5,6,7};
	int test2[3] = {-8,-3,0};
	int test3[5] = {5,-2,16,234,-4};

	int exp1 = 7;
	int exp2 = 0;
	int exp3 = 234;

	int i = 0; int c = 3;
	if (max(test1, 7) == exp1) { i++; }
	if (max(test2, 3) == exp2) { i++; }
	if (max(test3, 5) == exp3) { i++; }
	if (i == c) {
		printf("SUCCESS\n");
	} else {
		printf("FAIL at test #%d\n", c);
	}
};
void test_hypotenuse() {};
void test_init() {};
void test_offset() {};
void test_update() {};

void test_all() {
	printf("Testing min()... ");
	test_min();
	printf("Testing max()... ");
	test_max();
};
