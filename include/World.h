#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <random>
#include "Cell.h"
#include "Display.h"
#include "SimulationDriver.h"

#define WORLD_WIDTH 100
#define WORLD_HEIGHT 100
#define WORLD_SURFACE_CLEAR 0.8

#define DAISY_DIE_PROBABILITY 0.07
#define DAISY_TEMP_OPTIMAL 295.5
#define DAISY_TEMP_RANGE pow(17.5, -2.0)

using namespace std;

struct population_t {
    double temperature;
    unsigned long int white;
    unsigned long int black;
    unsigned long int none;
};

class Cell;
class Display;
class World
{
    public:
        World(int id, simulation_options_t *options);
        virtual ~World();
        population_t census();
        void setSolarLuminosity(double l) { this -> solarLuminosity = l; }
        double getSolarLuminosity() { return this -> solarLuminosity; }
        void update();

        // Options to help the simulation tick along
        int clear(double clearance);
        int seed(double density);
        void getLocalArea(size_t x, size_t y, Cell* (&ptr)[9]);
        void setGlobalTemp(double temp);

        uniform_real_distribution<> dis;
        mt19937 gen;

        Cell** cell;

        simulation_options_t *options;
    protected:
    private:
        double solarLuminosity;
        Display* d;
};

#endif // WORLD_H
