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
