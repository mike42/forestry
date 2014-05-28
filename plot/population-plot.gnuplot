#!/usr/bin/gnuplot
set key left
set terminal pdf
set output outfile
set xlabel 'Frame'
set ylabel 'Population'

plot infile using 1:3 w lines title "Black daisies", \
    infile using 1:4 w lines title "White daisies"
