#!/usr/bin/gnuplot
set key left
set terminal pdf
set output outfile
set xlabel 'Frame'
set ylabel 'Temperature K'
set y2label 'Solar Intensity'
set y2tics auto

plot infile using 1:5 w lines title "Temperature", \
    infile using 1:2 w lines title "Solar Intensity" axes x1y2
