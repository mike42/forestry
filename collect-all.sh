#!/bin/bash
mkdir -p data
./temp-collect.sh > data/temp.dat&
a=%%
time ./data-collect.sh
sleep 10 # catch CPU cool-down
kill $a
