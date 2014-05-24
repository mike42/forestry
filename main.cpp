#include <iostream>
#include <getopt.h>
#include "SimulationDriver.h"

using namespace std;

int main(int argc, char **argv)
{




    SimulationDriver *sim = new SimulationDriver(0.5);
    sim -> run();
    delete sim;

    return 0;
}


