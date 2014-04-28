#ifndef SIMULATIONDRIVER_H
#define SIMULATIONDRIVER_H

#define START_LUMINOSITY 1.0F
#define LUMINOSITY_STEP 0.1F
#define LUMINOSOTY_STEP_FRAMES 50
#define CLEARTIMES 3

#include "World.h"

class SimulationDriver
{
    public:
        SimulationDriver(double clearance, unsigned int worldSize);
        virtual ~SimulationDriver();
        void run();
    protected:
    private:
        bool graphical;
        double clearance;
        int clearFrame[CLEARTIMES];
        int clears;
        int frameCount;
        World* world[CLEARTIMES + 1];
};

#endif // SIMULATIONDRIVER_H
