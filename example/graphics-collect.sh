#!/bin/bash
mkdir -p img
bin/Release/forestry --clear 1.0 --display-invisible=31450 --display-file=img/daisies -n 32000 31500 -r11 > img/data.txt &
bin/Release/forestry --clear 1.0 --display-invisible=31450 --display-file=img/heat --display-temp-only -n 32000 31500 -r11 > /dev/null
