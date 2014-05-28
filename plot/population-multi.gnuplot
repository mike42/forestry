#!/usr/bin/gnuplot
set key left
set terminal pdf
set output outfile
set xlabel 'Frame'
set ylabel 'Population'

plot infile using 1:3 w lines title "Black Control", \
    infile using 1:4 w lines title "White Control", \
    infile using 1:6 w lines title "Black A", \
    infile using 1:7 w lines title "White A", \
    infile using 1:9 w lines title "Black B", \
    infile using 1:10 w lines title "White B", \
    infile using 1:12 w lines title "Black C", \
    infile using 1:13 w lines title "White C"
