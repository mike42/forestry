#ifndef SIMULATIONDRIVER_H
#define SIMULATIONDRIVER_H

#define START_LUMINOSITY 1.0F
#define LUMINOSITY_STEP 0.1F
#define LUMINOSITY_STEP_FRAMES 50
#define CLEARTIMES 3

#include "World.h"

class SimulationDriver
{
    public:
        SimulationDriver(double clearance);
        virtual ~SimulationDriver();
        void run();
    protected:
    private:
        bool graphical;
        double clearance;
        unsigned int clearFrame[CLEARTIMES];
        unsigned int clears;
        unsigned long int frameCount;
        World* world[CLEARTIMES + 1];
};

#endif // SIMULATIONDRIVER_H
