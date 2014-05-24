#include "Cell.h"
#define DAISY_PROPAGATION_PROB 0.0125

double breedProbability(double temperature);

Cell::Cell()
{
    colour = GREY;
    temperature = 0;
    is_daisy = false;
    doDie = false;
    nextTemp = 0;
    energy = 0;
}

Cell::~Cell()
{
    //dtor
}

void Cell::calcUpdate(World* w, size_t pos_x, size_t pos_y) {
    /* Figure out new temperature. Will be averaged before applying */
    doDie = false;
    nextTemp = temperature + (w -> getSolarLuminosity() * (1.0 - getAlbedo())) - 0.32;

    if(is_daisy) {
        energy++;
        if(energy >= DAISY_DIE_STEP) {
            doDie = true;
        }
    }
}

void Cell::doUpdate(World* w, size_t pos_x, size_t pos_y) {
    /* Get neighbour cells */
    Cell* neighbour[9];
    w -> getLocalArea(pos_x, pos_y, neighbour);

    /* Adjust temperature (average of nextTemp of this block) */
    double avgTemp = 0;
    for(size_t i = 0; i < 9; i++) {
        avgTemp += neighbour[i] -> nextTemp;
    }
    avgTemp /= 9;
    temperature = avgTemp;

    if(is_daisy && doDie) {
        is_daisy = false;
        energy = 0;
        colour = GREY;
    }

    if(!is_daisy) {
        Cell* candidate[9];
        size_t candidate_count = 0;
        for(size_t i = 0; i < 9; i++) {
            if(neighbour[i] -> is_daisy) {
                candidate[candidate_count] = neighbour[i];
                candidate_count++;
           }
        }

        if(candidate_count > 0 && w -> dis(w -> gen) < breedProbability(temperature)) {
            is_daisy = true;
            energy = 0;
            colour = candidate[rand() % candidate_count] -> colour;
        }
    }
}

double breedProbability(double temperature) {
    double p = 1.0 - (DAISY_TEMP_RANGE * pow(temperature - DAISY_TEMP_OPTIMAL, 2.0));
    if(p < 0) {
        return 0;
    }
    return p;
}
