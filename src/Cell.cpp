#include "Cell.h"

double deathProbability(double temperature);

Cell::Cell()
{
    colour = GREY;
    temperature = 0;
    is_daisy = false;
    doDie = doBreed = false;
    nextTemp = 0;
}

Cell::~Cell()
{
    //dtor
}

void Cell::calcUpdate(World* w, size_t pos_x, size_t pos_y) {
    // Figure out new temperature
    nextTemp = temperature;
// Cell*[9] neighbours = w -> getLocalArea(pos_x, pos_y);

    // Figure out if daisy will survive
    if(is_daisy && (w -> dis(w -> gen) < deathProbability(temperature))) {
        doDie = true;
    }

    // Breed
    if(is_daisy) {
        energy++;
        
        if(energy > DAISY_BREED_STEP) {
            doBreed = true;
        }
    }
}

void Cell::doUpdate(World* w, size_t pos_x, size_t pos_y) {
    temperature = nextTemp;
    if(is_daisy && doDie) {
        energy = 0;
        is_daisy = false;
        colour = GREY;
    }

    if(is_daisy && doBreed) {
        Cell* neighbour[9];
        w -> getLocalArea(pos_x, pos_y, neighbour);
        for(size_t i = 0; i < 9; i++) {
            if(!neighbour[i] -> is_daisy) {
                neighbour[i] -> is_daisy = true;
                neighbour[i] -> energy = 0;
                neighbour[i] -> colour = colour;
            }
            break;
        }
        energy = 0;
    }

    doDie = doBreed = false;
    nextTemp = 0;
}

double deathProbability(double temperature) {
    // Tweak ideal temperature range here
    double p = -(1.9 / 1000.0) * pow(temperature - 30.0, 2.0) + 1.0;
    if(p < 0) {
        p = 0;
    }
    
    // Tweak daisy mortality rate here
    return (1.0 - p) / 50.0;
}
