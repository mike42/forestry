#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <random>
#include "Cell.h"

#define WORLD_WIDTH 20
#define WORLD_HEIGHT 30

#define DAISY_BREED_STEP 50

using namespace std;

struct population_t {
    unsigned long int white;
    unsigned long int black;
    unsigned long int none;
};

class Cell;
class World
{
    public:
        World();
        virtual ~World();
        population_t census();
        void setSolarLuminosity(double l) { this -> solarLuminosity = l; }
        double getSolarLuminosity() { return this -> solarLuminosity; }
        void update();
        
        // Options to help the simulation tick along
        int clear(double clearance);
        int seed(double density);
        void getLocalArea(size_t x, size_t y, Cell* ptr[9]);
        void setGlobalTemp(double temp);
        
        uniform_real_distribution<> dis;
        mt19937 gen;
    protected:
    private:
        double solarLuminosity;
        Cell** cell;
};

#endif // WORLD_H
