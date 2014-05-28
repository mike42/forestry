#!/bin/bash
mkdir -p data

len=38000

echo " * Running empty planet for $len frames.."
cmd="bin/Release/forestry -i --empty -n $len -r0"
echo $cmd;
$cmd > data/empty.dat&

echo " * Running basic daisyworld x 10.."
for i in {1..10}; do
    cmd="bin/Release/forestry -i --daisyworld -n $len -r$i"
    echo $cmd;
    $cmd > data/daisyworld-$i.dat&
done
wait

echo " * Verifying that all daisyworlds were cooked .."
tail data/daisyworld-*.dat -n 1 | grep $len

echo " * Compare above temperatures to empty planet .."
tail data/empty.dat -n 1 | grep $len

echo " * Logging world x 10 at 1.0 density.."
for i in {1..10}; do
    cmd="bin/Release/forestry -i --clear 1.0 -n $len -r$((i + 10)) 31500 32000 32500"
    echo $cmd;
    $cmd > data/forestry-100-$i.dat&
done
wait

echo " * Logging world x 10 at 0.95 density.."
for i in {1..10}; do
    cmd="bin/Release/forestry -i --clear 0.95 -n $len -r$((i + 20)) 31500 32000 32500"
    echo $cmd;
    $cmd > data/forestry-095-$i.dat&
done
wait

echo " * Logging world x 10 at 0.90 density.."
for i in {1..10}; do
    cmd="bin/Release/forestry -i --clear 0.90 -n $len -r$((i + 30)) 31500 32000 32500"
    echo $cmd;
    $cmd > data/forestry-090-$i.dat&
done
wait
