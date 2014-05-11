#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "World.h"

class World;
enum dest_t { DEST_NONE, DEST_FILE, DEST_SCREEN };
class Display {
    public:
        Display(World* w, dest_t dest);
        virtual ~Display();
        int update();
        int frameSkip;
        int seq;
    private:
        World* target;
        dest_t dest;
        cv::Mat img;
};


#endif // DISPLAY_H
