# Read specific sensor from sensors -u 5 times per second for plotting
while true; do
	sleep 0.2
	echo `date --rfc-3339=ns` `sensors k10temp-pci-00c3 -u | grep temp1_input | cut -d':' -f2 | cut -d' ' -f2`
done
