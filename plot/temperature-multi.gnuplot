#!/usr/bin/gnuplot
set key left
set terminal pdf
set output outfile
set xlabel 'Frame'
set ylabel 'Temperature K'
set y2label 'Solar Intensity'
set y2tics auto

plot infile using 1:5 w lines title "Temperature Control", \
    infile using 1:8 w lines title "Temperature A", \
    infile using 1:11 w lines title "Temperature B", \
    infile using 1:14 w lines title "Temperature C", \
    infile using 1:2 w lines title "Solar Intensity" axes x1y2
