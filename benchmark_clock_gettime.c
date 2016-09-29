#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "computepi.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

#define PI acos(-1)

int main(int argc, char const *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, loop = 100;

    // Baseline
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        compute_pi_baseline(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);


    // OpenMP with 2 threads
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        compute_pi_openmp(N, 2);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);


    // OpenMP with 4 threads
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        compute_pi_openmp(N, 4);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);


    // AVX SIMD
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        compute_pi_avx(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);


    // AVX SIMD + Loop unrolling
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        compute_pi_avx_unroll(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

	// error
	printf("error,");

	// baseline
	double pi, diff_pi, error;
	pi = compute_pi_baseline(N);
	diff_pi = pi - PI > 0 ? pi - PI : PI - pi;
	error = diff_pi / PI;
	printf("%0.9lf,", (double) error);

	//openmp_2
	pi = compute_pi_openmp(N, 2);
	diff_pi = pi - PI > 0 ? pi - PI : PI - pi;
	error = diff_pi / PI;
	printf("%0.9lf,", (double) error);

	//openmp_4
	pi = compute_pi_openmp(N, 4);
	diff_pi = pi - PI > 0 ? pi - PI : PI - pi;
	error = diff_pi / PI;
	printf("%0.9lf,", (double) error);

	//avx
	pi = compute_pi_avx(N);
	diff_pi = pi - PI > 0 ? pi - PI : PI - pi;
	error = diff_pi / PI;
	printf("%0.9lf,", (double) error);
	
	//avxunroll
	pi = compute_pi_avx_unroll(N);
	diff_pi = pi - PI > 0 ? pi - PI : PI - pi;
	error = diff_pi / PI;
	printf("%0.9lf\n", (double) error);

    return 0;
}
