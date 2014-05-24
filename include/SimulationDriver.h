#ifndef SIMULATIONDRIVER_H
#define SIMULATIONDRIVER_H

#define START_LUMINOSITY 0.65F
#define START_TEMP DAISY_TEMP_OPTIMAL - 17.3
#define LUMINOSITY_STEP 0.00001F
#define LUMINOSITY_STEP_FRAMES 1

#define CLEARTIMES 3
#define CLEARSTEP 1000

/* Structs to store simultion options */
enum simulation_type_t {SIM_DAISYWORLD, SIM_EMPTY, SIM_FORESTRY};
enum display_type_t { DEST_NONE, DEST_FILE, DEST_WINDOW };

struct simulation_options_t {
    simulation_type_t simulation_type;
    display_type_t display_type;
    char *outpFilePrefix;
    int seed;
    int frame_skip;
    double clearance;
    int num_frames;
    int temp_only;
};

#include "World.h"
class World;
class SimulationDriver
{
    public:
        SimulationDriver(simulation_options_t *options);
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
