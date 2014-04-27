#include <iostream>
#include "SimulationDriver.h"

using namespace std;

int main(int argc, char **argv)
{
    SimulationDriver sim = SimulationDriver(0.5, 100);
    sim.run();
    return 0;
}
