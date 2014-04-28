#ifndef WORLD_H
#define WORLD_H
#include <cstdlib>
#include "Cell.h"

using namespace std;

class World
{
    public:
        World(unsigned int worldSize);
        virtual ~World();

	void setSolarLuminosity(double l) { this -> solarLuminosity = l; }
        double getSolarLuminosity() { return this -> solarLuminosity; };
    protected:
    private:
        double solarLuminosity;
        size_t size;
        Cell* cell;
};

#endif // WORLD_H
