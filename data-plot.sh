#!/bin/bash

echo " * Plotting CPU temp.."
gnuplot -e "infile='data/temp.dat'; outfile='data/temp.pdf'; set title 'CPU temperature over time';" plot/cpu-temperature.gnuplot

echo " * Plotting empty world.."
gnuplot -e "infile='data/empty.dat'; outfile='data/empty.pdf'; set title 'Daisyworld temperature, empty world';" plot/temperature-plot.gnuplot

echo " * Plotting daisyworld runs.."
for i in {1..10}; do
    gnuplot -e "infile='data/daisyworld-$i.dat'; outfile='data/daisyworld-$i-population.pdf'; set title 'Daisyworld population, seed $i';" plot/population-plot.gnuplot
    gnuplot -e "infile='data/daisyworld-$i.dat'; outfile='data/daisyworld-$i-temperature.pdf'; set title 'Daisyworld temperature, seed $i';" plot/temperature-plot.gnuplot
done

echo " * Plotting logged world.."
for j in 100 095 090; do
    for i in {1..10}; do
        gnuplot -e "infile='data/forestry-$j-$i.dat'; outfile='data/forestry-$j-$i-population.pdf'; set title 'Daisyworld population, $j percent clearance';" plot/population-multi.gnuplot
        gnuplot -e "infile='data/forestry-$j-$i.dat'; outfile='data/forestry-$j-$i-temperature.pdf'" plot/temperature-multi.gnuplot
    done
done

cd data && find . -name '*.pdf' -size 0 -print0 | xargs -0 rm
cd ..
pdftk data/*.pdf cat output raw-graphs.pdf

php process.php
for j in 100 095 090; do
    k=$((10#$j));
    gnuplot -e "infile='data.final/summary-$j.dat'; outfile='data.final/summary-$j.pdf'; set title 'Survivability of logging, $k% clearance';" plot/summary.gnuplot
done
