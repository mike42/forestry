#include "Display.h"
#define WINDOW_NAME "Simulation View"
#define SCALE_FACTOR 10

using namespace cv;

Display::Display(World* w) {
    img = Mat::zeros(WORLD_WIDTH * SCALE_FACTOR, WORLD_HEIGHT * SCALE_FACTOR, CV_8UC3);
    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
}

Display::~Display() {
    cvWaitKey(0);
    cvDestroyWindow(WINDOW_NAME);
}

int Display::update() {
    int x, y;
    Point center;
    for(y = 0; y < WORLD_HEIGHT; y++) {
        for(x = 0; x <  WORLD_WIDTH; x++) {
            if(target -> cell[y][x].colour != GREY) {
                center.x = x * SCALE_FACTOR + SCALE_FACTOR/2;
                center.y = y * SCALE_FACTOR + SCALE_FACTOR/2;
                circle(img,
                    center,
                    SCALE_FACTOR/2,
                    Scalar( 255, 255, 255 ),
                    -1);
            }
        }
    }

    imshow(WINDOW_NAME, img);
    return 0;
}
