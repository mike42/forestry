#include "Cell.h"
#define DAISY_PROPAGATION_PROB 0.0125

/* Stefan-Boltzmann constant is 5.670373 × 10-8 kg s-3 K-4 */
#define SB_CONST 5.670373E8

double breedProbability(double temperature);

Cell::Cell()
{
    colour = GREY;
    temperature = 0;
    is_daisy = false;
    doDie = false;
    doBreed = false;
    nextTemp = 0;
}

Cell::~Cell()
{
    //dtor
}

void Cell::calcUpdate(World* w, size_t pos_x, size_t pos_y) {
    /* Figure out new temperature. Will be averaged before applying */
    doDie = false;
    doBreed = false;

    // TODO Radiation lost to space: $\sigma_b T^4_0 = S(1-A_0)$
    // See http://en.wikipedia.org/wiki/Stefan%E2%80%93Boltzmann_law
    double lostToSpace = 0.00095 * STEFAN_BOLTZMANN_CONST * pow(temperature < 0 ? 0: temperature, 4.0);
    nextTemp = temperature + (w -> getSolarLuminosity() * (1.0 - getAlbedo())) - lostToSpace;

    if(is_daisy && w -> dis(w -> gen) < DAISY_DIE_PROBABILITY) {
            doDie = true;
    }

    if(!is_daisy) {
        /* Get neighbour cells */
        Cell* neighbour[9];
        w -> getLocalArea(pos_x, pos_y, neighbour);

        Cell* candidate[9];
        size_t candidate_count = 0;
        for(size_t i = 0; i < 9; i++) {
            if(neighbour[i] -> is_daisy) {
                candidate[candidate_count] = neighbour[i];
                candidate_count++;
           }
        }

        if(candidate_count > 0 && w -> dis(w -> gen) < breedProbability(temperature)) {
            doBreed = true;
            unsigned int j = (int)(w -> dis(w -> gen) * candidate_count);
            assert(j >= 0 && j < candidate_count);
            colour = candidate[j] -> colour;
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
        colour = GREY;
    }

    if(!is_daisy && doBreed) {
        doBreed = false;
        is_daisy = true;
        assert(colour != GREY);
    }
}

double breedProbability(double temperature) {
    // From Watson 1983, p285
    double p = 1.0 - (DAISY_TEMP_RANGE * pow(temperature - DAISY_TEMP_OPTIMAL, 2.0));
    if(p < 0) {
        return 0;
    }
    return p;
}
