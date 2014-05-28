#!/usr/bin/gnuplot
set key off
set terminal pdf
set output outfile

set style fill solid
set boxwidth 0.5

set xlabel 'Luminosity'
set ylabel 'No. of Homeostatic Simulations'
set yrange[0:10]

plot infile using 2:xtic(1) w boxes

