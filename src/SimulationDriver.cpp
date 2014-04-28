#include "SimulationDriver.h"

SimulationDriver::SimulationDriver(double clearance)
{
    // Set up default values
    this -> clearance = clearance;
    this -> frameCount = 0;
    this -> clears = 0;
    for(size_t i = 0; i < CLEARTIMES; i++) {
        this -> clearFrame[i] = 0;
    }

    // Initialise first world and set other worlds to be empty
    this -> world[0] = new World();
    for(size_t i = 1; i <= CLEARTIMES; i++) {
        this -> world[i] = NULL;
    }
}

void SimulationDriver::run()
{
    population_t counts;
    unsigned int dead;

    do {
        dead = 0;
        for(size_t i = 0; i <= CLEARTIMES && i <= clears; i++) {
            // Clone and clear world if necessary
            // TODO

            // Update each world
            this -> world[i] -> update();

            // Perform a 'census', and stop when all worlds are dead
            counts = this -> world[i] -> census();
            cout << frameCount << "\t" << i << "\t" << counts.black << "\t" << counts.white << "\t" << counts.none << "\n";
            if(counts.black == 0 && counts.white == 0) {
                // Note dead planet
                dead++;
            }
        }
        frameCount++;
    } while(dead < clears + 1);

    return;
}

SimulationDriver::~SimulationDriver()
{
    for(size_t i = 0; i <= CLEARTIMES && i <= clears; i++) {
        delete this -> world[i];
    }
}
