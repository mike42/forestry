#include "World.h"

World::World(unsigned int worldSize)
{
    size_t size = (size_t)worldSize;
    this -> size = size;
    this -> solarLuminosity = 0;
    // Initialise cells
    this -> cell = new Cell[size * size];
}

World::~World()
{
    // Destroy the cells
    delete [] this -> cell;
}
