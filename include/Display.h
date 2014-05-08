#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "World.h"

class Display {
    public:
        Display(World* w);
        virtual ~Display();
        int update();
        
    private:
        World* target;
        cv::Mat img;
};
