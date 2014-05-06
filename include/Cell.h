#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <cmath>
#include "World.h"

enum CellColour { BLACK, WHITE, GREY };

class World;
class Cell
{
    public:
        Cell();
        virtual ~Cell();
        void calcUpdate(World* w, size_t pos_x, size_t pos_y);
        void doUpdate(World* w, size_t pos_x, size_t pos_y);
        bool is_daisy;
        int energy;
        CellColour colour;
        double temperature;
    private:
    	bool doDie;
    	bool doBreed;
    	int nextTemp;
};

#endif // CELL_H
