reset
set ylabel 'time(sec)'
set title 'compute-pi perfomance'
set datafile separator ','
set key width 2
set key left
set grid
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot 'result_clock_gettime.csv' using 1:2 with lines title 'baseline', \
'' using 1:3 with lines title 'omp_2', \
'' using 1:4 with lines title 'omp_4', \
'' using 1:5 with lines title 'avx', \
'' using 1:6 with lines title 'avxunroll'

reset
set ylabel 'error'
set title 'compute-pi error'
set datafile separator ','
set key width 2
set key left
set grid
set term png enhanced font 'Verdana,10'
set output 'error.png'

plot 'result_clock_gettime.csv' using 1:8 with lines title 'baseline', \
'' using 1:9 with lines title 'omp_2', \
'' using 1:10 with lines title 'omp_4', \
'' using 1:11 with lines title 'avx', \
'' using 1:12 with lines title 'avxunroll'
