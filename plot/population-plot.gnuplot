#!/usr/bin/gnuplot
set terminal pdf
set output 'outp.pdf'
set xlabel 'Frame'
set ylabel 'Population'

plot "data.dat" using 1:3 w lines title "White daisies", \
"data.dat" using 1:4 w lines title "Black daisies", \
"data.dat" using 1:5 w lines title "Empty", \
"data.dat" using 1:6 w lines title "Temperature"
