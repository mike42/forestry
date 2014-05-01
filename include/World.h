#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include "Cell.h"

#define WORLD_WIDTH 20
#define WORLD_HEIGHT 30

using namespace std;

struct population_t {
    unsigned long int white;
    unsigned long int black;
    unsigned long int none;
};

class World
{
    public:
        World();
        virtual ~World();
        population_t census();
        void setSolarLuminosity(double l) { this -> solarLuminosity = l; }
        double getSolarLuminosity() { return this -> solarLuminosity; }
        void update();
    protected:
    private:
        double solarLuminosity;
        Cell** cell;
};

#endif // WORLD_H
