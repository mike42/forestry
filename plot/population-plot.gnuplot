#!/usr/bin/gnuplot
set key left
set terminal pdf
set output 'population.pdf'
set xlabel 'Frame'
set ylabel 'Population'

plot "data.dat" using 1:3 w lines title "Black daisies", \
"data.dat" using 1:4 w lines title "White daisies"
