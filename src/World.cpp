#include "World.h"

World::World()
{
    this -> solarLuminosity = 0;

    size_t y;
    this -> cell = new Cell*[WORLD_HEIGHT];
    for(y = 0; y < WORLD_HEIGHT; ++y) {
       this -> cell[y] = new Cell[WORLD_WIDTH];
    }

    random_device rd;
    gen = mt19937(rd());
    dis = uniform_real_distribution<>(0, 1);
}

World::~World()
{
    size_t y;
    for(y = 0; y < WORLD_HEIGHT; y++) {
        this -> cell[y][0].colour = GREY;
        this -> cell[y][19].colour = GREY;
        delete[] (this -> cell[y]);
    }
    delete[] this -> cell;
}

void World::update() {
    size_t y, x;
    for(y = 0; y < WORLD_HEIGHT; y++) {
        for(x = 0; x < WORLD_WIDTH; x++) {
            this -> cell[y][x].calcUpdate(this, x, y);
        }
    }
    
    for(y = 0; y < WORLD_HEIGHT; y++) {
        for(x = 0; x < WORLD_WIDTH; x++) {
            this -> cell[y][x].doUpdate(this, x, y);
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

int World::clear(double clearance) {
    return true;
}

int World::seed(double density) {
    size_t y, x;
    int ret = 0;
        
    for(y = 0; y < WORLD_HEIGHT; y++) {
        for(x = 0; x < WORLD_WIDTH; x++) {
            if(!this -> cell[y][x].is_daisy && dis(gen) < density) {
                this -> cell[y][x].is_daisy = true;
                if(dis(gen) < 0.5) {
                    cell[y][x].colour = BLACK;
                } else {
                    cell[y][x].colour = WHITE;
                }
                cell[y][x].energy = (int)(dis(gen) * (double)DAISY_BREED_STEP); // Random energy
                ret++;
            }
        }
    }

    return ret;
}

void World::setGlobalTemp(double temp) {
    size_t y, x;
    for(y = 0; y < WORLD_HEIGHT; y++) {
        for(x = 0; x < WORLD_WIDTH; x++) {
            this -> cell[y][x].temperature = temp;
        }
    }
}

void World::getLocalArea(size_t x, size_t y, Cell* ptr[9]) {
    int src_x = 0;
    int src_y = 0;
    
    for(size_t i = 0; i < 9; i++) {
        src_x = (x - 1) + (i % 3);
        src_y = (y - 1) + (i / 3);
        while(src_x < 0) {
            src_x += WORLD_WIDTH;
        }
        while(src_x >= WORLD_WIDTH) {
            src_x -= WORLD_WIDTH;
        }
        while(src_y < 0) {
            src_y += WORLD_HEIGHT;
        }
        while(src_y >= WORLD_HEIGHT) {
            src_y -= WORLD_HEIGHT;
        }
        ptr[i] = &cell[src_y][src_x];
    }
    return;
}
