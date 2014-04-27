#ifndef CELL_H
#define CELL_H

enum CellColour { BLACK, WHITE, GREY };

class Cell
{
    public:
        Cell();
        virtual ~Cell();
    protected:
        CellColour colour;
        double temperature;
    private:
        bool is_daisy;
        int energy;
};

#endif // CELL_H
