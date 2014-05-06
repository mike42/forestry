#!/usr/bin/gnuplot
set terminal png
set output 'outp.png'
set xlabel 'Frame'
set ylabel 'Population'

plot "data.dat" using 1:3 w lines title "White daisies", \
"data.dat" using 1:4 w lines title "Black daisies"

