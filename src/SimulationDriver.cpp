#include "SimulationDriver.h"

SimulationDriver::SimulationDriver(simulation_options_t *options)
{
    // Set up default values
    this -> clearance = options -> clearance;
    this -> frameCount = 0;
    this -> clears = 0;
    for(size_t i = 0; i < CLEARTIMES; i++) {
        this -> clearFrame[i] = 0;
    }

    // Initialise first world and set other worlds to be empty
    this -> world[0] = new World(0, options);
    for(size_t i = 1; i <= CLEARTIMES; i++) {
        this -> world[i] = NULL;
    }

    // Seed the first world and set it to a habitable temperature
    this -> world[0] -> setSolarLuminosity(START_LUMINOSITY);
    this -> world[0] -> setGlobalTemp(START_TEMP);

    if(options -> simulation_type != SIM_EMPTY) {
        this -> world[0] -> seed(0.5);
    }
}

void SimulationDriver::run()
{
    population_t counts;
    unsigned int dead;

    do {
        dead = 0;
        for(size_t i = 0; i <= CLEARTIMES && i <= clears; i++) {
            /* Step up solar intensity */
            if(frameCount % LUMINOSITY_STEP_FRAMES == LUMINOSITY_STEP_FRAMES - 1) {
                this -> world[i] -> setSolarLuminosity(this -> world[i] -> getSolarLuminosity() + LUMINOSITY_STEP);
            }

            /*  Update each world */
            this -> world[i] -> update();

            /* Clone and clear world if necessary */
            if(frameCount % (CLEARSTEP * (i + 1)) == 0) {
                this -> world[i] -> clear(this -> world[i] -> options -> clearance);
                cerr << this -> world[i] -> options -> clearance << endl;
            }

            /* Perform a 'census', and stop when all worlds are dead */
            counts = this -> world[i] -> census();
            cout << frameCount << "\t" << i << "\t" << counts.black << "\t" << counts.white << "\t" << "\t" << counts.temperature << "\t" << this -> world[i] -> getSolarLuminosity() << "\n";
            if(counts.black == 0 && counts.white == 0) {
                // Note dead planet
              //  dead++;
            }
        }
        frameCount++;
    } while(dead < clears + 1);

    return;
}

SimulationDriver::~SimulationDriver()
{
   // for(size_t i = 0; i <= CLEARTIMES && i <= (this -> clears); i++) {
    //    delete this -> world[i];
   // }
}
