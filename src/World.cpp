#include "World.h"

World::World(int id, simulation_options_t *options)
{
    this -> solarLuminosity = 0;
    this -> options = options;

    size_t y;
    this -> cell = new Cell*[WORLD_HEIGHT];
    for(y = 0; y < WORLD_HEIGHT; y++) {
       this -> cell[y] = new Cell[WORLD_WIDTH];
    }

    if(options -> seed == -1) {
        random_device rd;
        gen = mt19937(rd());
    } else {
        gen = mt19937(options -> seed);
    }
    dis = uniform_real_distribution<>(0, 1);

    d = new Display(this, id);
}

World::~World()
{
    size_t y;
    for(y = 0; y < WORLD_HEIGHT; y++) {
        delete[] (this -> cell[y]);
    }
    delete[] this -> cell;
    delete d;
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

    d -> update();
}

population_t World::census() {
    population_t result;
    result.black = 0;
    result.white = 0;
    result.none = 0;
    result.temperature = 0;
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
            result.temperature += this -> cell[y][x].temperature;
        }
    }
    result.temperature /= (WORLD_HEIGHT * WORLD_WIDTH);
    return result;
}

int World::clear(double clearance) {
    // Assumes square world
    size_t clear_size = round(pow((double)(WORLD_WIDTH * WORLD_HEIGHT) * WORLD_SURFACE_CLEAR, 0.5));
    size_t clear_start = (WORLD_WIDTH - clear_size) / 2;

    size_t y, x;
    int n = 0;
    for(y = 0; y < WORLD_HEIGHT; y++) {
        for(x = 0; x < WORLD_WIDTH; x++) {
            if(x > clear_start && x < clear_start + clear_size &&
                y > clear_start && y < clear_start + clear_size &&
                dis(gen) < clearance) {
                this -> cell[y][x].is_daisy = false;
                this -> cell[y][x].colour = GREY;
                n++;
            }
        }
    }
    return n;
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

void World::getLocalArea(size_t x, size_t y, Cell* (&ptr)[9]) {
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
