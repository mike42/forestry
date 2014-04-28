#include "SimulationDriver.h"

SimulationDriver::SimulationDriver(double clearance, unsigned int worldSize)
{
    this -> clearance = clearance;
    this -> frameCount = 0;
    this -> clears = 0;
    for(size_t i = 0; i < CLEARTIMES; i++) {
        this -> clearFrame[i] = 0;
    }

    // Initialise worlds
    this -> world[0] = new World(worldSize);
    for(size_t i = 0; i <= CLEARTIMES; i++) {
        this -> world[i] = NULL;
    }
}

void SimulationDriver::run()
{
    return;
}


SimulationDriver::~SimulationDriver()
{
    for(size_t i = 0; i <= CLEARTIMES && i <= clears; i++) {
        delete this -> world[i];
    }
}
