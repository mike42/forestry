#include "SimulationDriver.h"

SimulationDriver::SimulationDriver(simulation_options_t *options)
{
    // Set up default values
    this -> clearance = options -> clearance;
    this -> frameCount = 0;

    clear_count = options -> clear_count;
    num_frames = options -> num_frames;
    assert(clear_count < WORLD_COUNT); // Can't clear all the planets.
    for(size_t i = 0; i < clear_count; i++) {
        this -> clear_frame[i] = options -> clear_frame[i];
    }

    // Initialise all required worlds
    for(size_t i = 0; i <= WORLD_COUNT; i++) {
        if(i <= clear_count) {
            // Seed worlds and set them to a habitable temperature
            this -> world[i] = new World(i, options);
            this -> world[i] -> setSolarLuminosity(START_LUMINOSITY);
            this -> world[i] -> setGlobalTemp(START_TEMP);

            if(options -> simulation_type != SIM_EMPTY) {
                this -> world[i] -> seed(1);
            }   
        } else {
            this -> world[i] = NULL;
        }
    }

    cout << "A\n";
}

void SimulationDriver::run()
{
    population_t counts;
    unsigned int dead;

    do {
        dead = 0;
        /* Step up solar intensity */
        if(frameCount % LUMINOSITY_STEP_FRAMES == LUMINOSITY_STEP_FRAMES - 1) {
            for(size_t i = 0; i <= clear_count; i++) {
                this -> world[i] -> setSolarLuminosity(this -> world[i] -> getSolarLuminosity() + LUMINOSITY_STEP);
            }
        }

        for(size_t i = 0; i <= clear_count; i++) {
            /*  Update each world */
            this -> world[i] -> update();

            /* Clear world if necessary */
            if(i > 0 && clear_frame[i - 1] == frameCount) {
                this -> world[i] -> clear(this -> world[i] -> options -> clearance);
            }

            /* Perform a 'census' */
            counts = this -> world[i] -> census();
            cout << frameCount << "\t" << i << "\t" << counts.black << "\t" << counts.white << "\t" << "\t" << counts.temperature << "\t" << this -> world[i] -> getSolarLuminosity() << "\n";
            if(counts.black == 0 && counts.white == 0) {
              // Note dead planet
              dead++;
            }
        }
        frameCount++;
    } while(frameCount < num_frames || (num_frames == 0 && dead <= clear_count));

    return;
}

SimulationDriver::~SimulationDriver()
{
   // for(size_t i = 0; i <= CLEARTIMES && i <= (this -> clears); i++) {
    //    delete this -> world[i];
   // }
}
