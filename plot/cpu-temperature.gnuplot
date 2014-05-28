#!/usr/bin/gnuplot
set key left
set terminal pdf
set output outfile
set xlabel 'Sample'
set ylabel 'Temperature (C)'

plot infile using 3 w lines title 'CPU temp'

