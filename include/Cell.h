#ifndef CELL_H
#define CELL_H

enum CellColour { BLACK, WHITE, GREY };

class Cell
{
    public:
        Cell();
        virtual ~Cell();
        bool is_daisy;
        int energy;
        CellColour colour;
        double temperature;
};

#endif // CELL_H
