CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall -fopenmp -mavx -g -lm
EXECUTABLE = \
	time_test_baseline time_test_openmp_2 time_test_openmp_4 \
	time_test_avx time_test_avxunroll \
	benchmark_clock_gettime polygon

default: computepi.o
	$(CC) $(CFLAGS) computepi.o time_test.c -DBASELINE -o time_test_baseline -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_2 -o time_test_openmp_2 -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_4 -o time_test_openmp_4 -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVX -o time_test_avx -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVXUNROLL -o time_test_avxunroll -lm
	$(CC) $(CFLAGS) computepi.o benchmark_clock_gettime.c -o benchmark_clock_gettime -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DPOLYGON -o time_test_polygon -lm

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

check: default
	time ./time_test_baseline
	time ./time_test_openmp_2
	time ./time_test_openmp_4
	time ./time_test_avx
	time ./time_test_avxunroll
	time ./time_test_polygon

gencsv: default
	for i in `seq 100 2000 800000`; do \
		printf "%d," $$i;\
		./benchmark_clock_gettime $$i; \
	done > result_clock_gettime.csv	

plot: gencsv
	gnuplot ./scripts/runtime.gp

clean:
	rm -f $(EXECUTABLE) *.o *.s result_clock_gettime.csv runtime.png error.png time_test_polygon
