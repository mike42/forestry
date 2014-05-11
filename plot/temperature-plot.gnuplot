#!/usr/bin/gnuplot
set key left
set terminal pdf
set output 'temp.pdf'
set xlabel 'Frame'
set ylabel 'Temperature K'
set y2label 'Solar Intensity'
set y2tics auto

plot "data.dat" using 1:5 w lines title "Temperature", \
"data.dat" using 1:6 w lines title "Solar Intensity" axes x1y2
