#include "World.h"

World::World()
{
    this -> solarLuminosity = 0;

    size_t y;
    this -> cell = new Cell*[WORLD_HEIGHT];
    for(y = 0; y < WORLD_HEIGHT; ++y) {
       this -> cell[y] = new Cell[WORLD_WIDTH];
    }
}

World::~World()
{
    size_t y;
    for(y = 0; y < WORLD_HEIGHT; y++) {
        this -> cell[y][0].colour = GREY;
        this -> cell[y][19].colour = GREY;
        delete [] (this -> cell[y]);
    }
    delete[] this -> cell;

}

void World::update() {
    size_t y, x;
    for(y = 0; y < WORLD_HEIGHT; y++) {
        for(x = 0; x < WORLD_WIDTH; x++) {
            // TODO update each agent here
        }
    }
}

population_t World::census() {
    population_t result;
    result.black = 0;
    result.white = 0;
    result.none = 0;
    size_t y, x;
    for(y = 0; y < WORLD_HEIGHT; y++) {
        for(x = 0; x < WORLD_WIDTH; x++) {
            switch(this -> cell[y][x].colour) {
            case BLACK:
                result.black++;
                break;
            case WHITE:
                result.white++;
                break;
            case GREY:
                result.none++;
                break;
           }
        }
    }
    return result;
}
