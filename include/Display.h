#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "World.h"
#include "SimulationDriver.h"

class World;

class Display {
    public:
        Display(World* w, int id);
        virtual ~Display();
        int update();
        unsigned long seq;
        int id;

        std::string windowName;
    private:
        World* target;
        cv::Mat img;
        display_type_t dest;
        int frame_skip;
};


#endif // DISPLAY_H
