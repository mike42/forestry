#include "Display.h"
#include <unistd.h>
#define WINDOW_NAME "Simulation View "
#define SCALE_FACTOR 5

using namespace cv;

double hue2rgb(double p, double q, double t){
    if(t < 0.0) t += 1.0;
    if(t > 1.0) t -= 1.0;
    if(t < 1.0/6.0) return p + (q - p) * 6.0 * t;
    if(t < 1.0/2.0) return q;
    if(t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6.0;
    return p;
}

Scalar fromHSL(double h, double s, double l) {
    // Adapted from http://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
    // In turn adapted from en.wikipedia
    double r, g, b;
    if(s == 0) {
        r = g = b = l;
    } else {
        double q = l < 0.5 ? l * (1.0 + s) : l + s - l * s;
        double p = 2 * l - q;
        r = hue2rgb(p, q, h + 1.0/3.0);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1.0/3.0);
    }

   // return Scalar((int)round(h * 255.0), (int)round(h * 255.0), (int)round(h * 255.0));
    return Scalar(round(r * 255.0), round(g * 255.0), round(b * 255.0));
}

Display::Display(World* w, dest_t dest, int id) {
    char buffer[128];
   sprintf(buffer, "%s %d", WINDOW_NAME, id);
    this -> windowName = std::string(buffer);
    this -> dest = dest;

    target = w;
    frameSkip = 1;
    img = Mat::zeros(WORLD_HEIGHT * SCALE_FACTOR, WORLD_WIDTH * SCALE_FACTOR, CV_8UC3);
    namedWindow(this -> windowName, WINDOW_AUTOSIZE);
    seq = 0;
    update();
}

Display::~Display() {
    cvWaitKey(0);
    cvDestroyWindow(WINDOW_NAME);
}

int Display::update() {
    if(dest == DEST_NONE) {
        return 0;
    }

    int x, y;
    Point center;
    img.setTo(cv::Scalar(120, 120, 120)); // Clear
    Scalar white = Scalar( 255, 255, 255 );
    Scalar black = Scalar( 0, 0, 0 );
    for(y = 0; y < WORLD_HEIGHT; y++) {
        for(x = 0; x <  WORLD_WIDTH; x++) {
            double intensity = ((DAISY_TEMP_OPTIMAL - target -> cell[y][x].temperature) / 200.0);
            while(intensity < 0) {
                intensity += 1;
            }
            while(intensity > 1) {
                intensity -= 1;
            }

            rectangle(img,
                Point(x * SCALE_FACTOR, y * SCALE_FACTOR),
                Point((x + 1) * SCALE_FACTOR - 1, (y + 1) * SCALE_FACTOR - 1),
                fromHSL(intensity, 1, 0.5),
                CV_FILLED);
            if(target -> cell[y][x].colour != GREY) {
                center.x = x * SCALE_FACTOR + SCALE_FACTOR/2;
                center.y = y * SCALE_FACTOR + SCALE_FACTOR/2;
                circle(img,
                    Point(x * SCALE_FACTOR + SCALE_FACTOR/2, y * SCALE_FACTOR + SCALE_FACTOR/2),
                    SCALE_FACTOR/3,
                    target -> cell[y][x].colour == WHITE ? white : black,
                    CV_FILLED);
            }
        }
    }

    if(dest == DEST_SCREEN) {
        imshow(this -> windowName, img);
        cvWaitKey(1);
    } else if(dest == DEST_FILE) {
        char f[16];
        seq++;
        if(seq % frameSkip == 0) {
            sprintf(f, "frame-%05d.png", seq);
            imwrite(f, img);
        }
    }
    return 0;
}

