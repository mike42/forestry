#ifndef SIMULATIONDRIVER_H
#define SIMULATIONDRIVER_H

#include "World.h"

#define START_LUMINOSITY 1.0F
#define LUMINOSITY_STEP 0.1F
#define LUMINOSOTY_STEP_FRAMES 50

class SimulationDriver
{
    public:
        SimulationDriver(double clearance, int size);
        virtual ~SimulationDriver();
        void run();
    protected:
    private:
        bool graphical;
        double clearance;
        int clearFrame[3];
        int frameCount;
        World* world;
};

#endif // SIMULATIONDRIVER_H
