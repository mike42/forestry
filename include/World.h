#ifndef WORLD_H
#define WORLD_H
#include "Cell.h"

class World
{
    public:
        World(int size);
        virtual ~World();
    protected:
    private:
        double solarLuminosity;
        int size;
        Cell **cell;
};

#endif // WORLD_H
