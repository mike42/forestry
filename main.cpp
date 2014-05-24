#include <iostream>
#include <getopt.h>
#include <cmath>
#include "SimulationDriver.h"

using namespace std;

void usage() {
    cerr << "forestry [--help | --usage | --clear amount | --daisyworld | --empty ]\n\t[ --display-window | --display-invisible | --display-file prefix ]\n\t[--random-seed r] [--num-frames n ]\n\t[--display-skip s] [--display-temp-only]" << endl;
}

int main(int argc, char **argv)
{

    /* Set up defaults */
    simulation_options_t options;
    options.simulation_type = SIM_DAISYWORLD;
    options.clearance = 0.5;
    options.display_type = DEST_WINDOW;
    options.frame_skip = 0;
    options.outpFilePrefix = "frame-";
    options.seed = -1;
    options.num_frames = 0;
    options.temp_only = 0;

    extern char *optarg;
    extern int optind, optopt;

    if(argc == 0) {
        usage();
        return 1;
    }

    static struct option long_options[] = {
        {"clear", required_argument, NULL, 'c'},
        {"daisyworld", no_argument, NULL, 'd'},
        {"empty", no_argument, NULL, 'e'},
        {"help", no_argument, NULL, 'h'},
        {"display-skip", required_argument, NULL, 's'},
        {"display-invisible", no_argument, NULL, 'i'},
        {"display-window", no_argument, NULL, 'w'},
        {"display-file", required_argument, NULL, 'f'},
        {"random-seed", required_argument, NULL, 'r'},
        {"usage", no_argument, NULL, 'u'},
        {"num-frames", required_argument, NULL, 'n'},
        {"display-temp-only", required_argument, NULL, 't'},
        {0, 0, 0, 0}
    };

    int ch;
    while ((ch = getopt_long(argc, argv, "c:dehs:iwf:r:un:t", long_options, NULL)) != -1)
        switch (ch) {
            case 'c':
                options.simulation_type = SIM_FORESTRY;
                options.clearance = atof(optarg);
                if(!(options.clearance >= 0  && options.clearance <= 1)) {
                    cerr << "Error: Clearance must be a number between 0 and 1 inclusive." << endl;
                    return 1;
                }
                break;
            case 'd':
                options.simulation_type = SIM_DAISYWORLD;
                break;
            case 'e':
                options.simulation_type = SIM_EMPTY;
                break;
            case 's':
                options.frame_skip = atoi(optarg);
                if(options.frame_skip < 0) {
                    cerr << "Error: Frame skip must be a positive integer." << endl;
                    return 1;
                }
                break;
            case 'i':
                options.display_type = DEST_NONE;
                break;
            case 'w':
                options.display_type = DEST_WINDOW;
                break;
            case 'f':
                options.display_type = DEST_FILE;
                options.outpFilePrefix = optarg;
                break;
            case 'r':
                options.seed = atoi(optarg);
                if(options.seed < 0) {
                    cerr << "Error: Seed must be a positive integer. Remove the option to generate one at random." << endl;
                    return 1;
                }
                break;
            case 'n':
                options.num_frames = atoi(optarg);
                if(options.num_frames < 0) {
                    cerr << "Error: Number of frames must be a positive integer." << endl;
                    return 1;
                }
                break;
            case 't':
                options.temp_only = 1;
                break;
        default:
                usage();
                return 1;
    }

    /* Run a simulation with the selected parameters */
    SimulationDriver *sim = new SimulationDriver(&options);
    sim -> run();
    delete sim;

    return 0;
}


