#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void x86sdot(size_t n, double* sdot, double* C, double* A, double* B);
extern void SIMDsdot(size_t n, double* sdot, double* C, double* A, double* B);

void f_sdot(size_t n, double* sdot, double* C, double* A, double* B) {
	for (int i = 0; i < n; i++) {
		C[i] = A[i] * B[i];
		*sdot += C[i];
	}
}

int main() {
	const size_t ARRAY_SIZE = 1 << 28;
	const size_t ARRAY_BYTES = ARRAY_SIZE * sizeof(double);

	double* A, * B, * C, * sdot;
	A = (double*)malloc(ARRAY_BYTES);
	B = (double*)malloc(ARRAY_BYTES);
	C = (double*)malloc(ARRAY_BYTES);
	sdot = (double*)malloc(sizeof(double));
	*sdot = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE; i++) {
		A[i] = (double)i;
		B[i] = (double)i;
	}

	clock_t start, end;
	
	f_sdot(ARRAY_SIZE, sdot, C, A, B);

	for (int j = 0; j < 1; j++) {
		*sdot = 0;
		start = clock();
		f_sdot(ARRAY_SIZE, sdot, C, A, B);
		end = clock();
		double time_taken = ((double)(end - start)) * 1e3 / CLOCKS_PER_SEC;

		printf("sdot = %lf \n", *sdot);
		printf("C function took %lf ms for array size %ld \n", time_taken, ARRAY_SIZE);

		unsigned int err_count = 0;

		for (i = 0; i < ARRAY_SIZE; i++) {
			if (A[i] * B[i] != C[i])
				err_count++;
		}

		printf("Error count (C program): %d \n", err_count);
	}

	x86sdot(ARRAY_SIZE, sdot, C, A, B);

	for (int j = 0; j < 1; j++) {
		*sdot = 0;
		start = clock();
		x86sdot(ARRAY_SIZE, sdot, C, A, B);
		end = clock();
		double time_taken = ((double)(end - start)) * 1e3 / CLOCKS_PER_SEC;

		printf("sdot = %lf \n", *sdot);
		printf("C function took %lf ms for array size %ld \n", time_taken, ARRAY_SIZE);

		unsigned int err_count = 0;

		for (i = 0; i < ARRAY_SIZE; i++) {
			if (A[i] * B[i] != C[i])
				err_count++;
		}

		printf("Error count (C program): %d \n", err_count);
	}
	
	SIMDsdot(ARRAY_SIZE, sdot, C, A, B);

	for (int j = 0; j < 1; j++) {
		*sdot = 0;
		start = clock();
		SIMDsdot(ARRAY_SIZE, sdot, C, A, B);
		end = clock();
		double time_taken = ((double)(end - start)) * 1e3 / CLOCKS_PER_SEC;

		printf("sdot = %lf \n", *sdot);
		printf("C function took %lf ms for array size %ld \n", time_taken, ARRAY_SIZE);

		unsigned int err_count = 0;

		for (i = 0; i < ARRAY_SIZE; i++) {
			if (A[i] * B[i] != C[i])
				err_count++;
		}

		printf("Error count (C program): %d \n", err_count);
	}

	printf("%lf", C[10]);

	return 0;
}