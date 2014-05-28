#include <stdio.h>

#ifndef SIMULATIONDRIVER_H
#define SIMULATIONDRIVER_H

#define START_LUMINOSITY 0.65F
#define START_TEMP DAISY_TEMP_OPTIMAL - 17.3
#define LUMINOSITY_STEP 0.00003F
#define LUMINOSITY_STEP_FRAMES 1

#define WORLD_COUNT 4

/* Structs to store simultion options */
enum simulation_type_t {SIM_DAISYWORLD, SIM_EMPTY, SIM_FORESTRY};
enum display_type_t { DEST_NONE, DEST_FILE, DEST_WINDOW };

struct simulation_options_t {
    simulation_type_t simulation_type;
    display_type_t display_type;
    char *outpFilePrefix;
    int seed;
    unsigned long frame_skip;
    double clearance;
    unsigned long num_frames;
    unsigned long until;
    unsigned long clear_frame[WORLD_COUNT - 1];
    size_t clear_count;
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
        unsigned long int frameCount;

        unsigned long num_frames;
        size_t clear_count;
        unsigned long clear_frame[WORLD_COUNT - 1];

        World* world[WORLD_COUNT];
};

#endif // SIMULATIONDRIVER_H
