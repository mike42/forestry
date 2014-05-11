forestry
--------

Daisyworld-style artificial life simulation for evaluating sustainable forestry management practices.

Currently best way to run is:

        make && bin/Release/forestry > data.dat && gnuplot plot.gnuplot


Tips
----

To generate a capture video from PNG output:

    avconv -f image2 -r 200 -i frame-%5d.png daisyworld.mp4

To reduce it to an acceptable filesize (as the above is 200FPS and will be a few hundred MB):

    avconv -i daisyworld.mp4 -r:v 18 -b:v 2000k daisyworld-small.mp4
    
To re-plot data as it is printed:

    bin/Release/forestry | tee data.dat

And in another terminal:

    while true; do (gnuplot plot/population-plot.gnuplot && gnuplot plot/temperature-plot.gnuplot ); sleep 3; done

Evince (the GNOME PDF viewer) will re-render the plot as it changes.


