#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <cmath>
#include "World.h"

#define STEFAN_BOLTZMANN_CONST 5.6704E-8

enum CellColour { BLACK, WHITE, GREY };

class World;
class Cell
{
    public:
        Cell();
        virtual ~Cell();
        void calcUpdate(World* w, size_t pos_x, size_t pos_y);
        void doUpdate(World* w, size_t pos_x, size_t pos_y);
        double getAlbedo() {
            if(colour == WHITE) {
                return 0.75;
            } else if(colour == BLACK) {
                return 0.25;
            }
            return 0.5;
        };
        bool is_daisy;
        int energy;
        CellColour colour;
        double temperature;
    private:
    	bool doDie;
    	bool doBreed;
    	double nextTemp;
};

#endif // CELL_H
