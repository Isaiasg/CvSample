/**
* Isaias Gonzalez <siderevs@gmail.com>
*/

#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include <stdio.h>

class Histogram 
{
public:
    Histogram();
    CvHistogram* GetHistogram(IplImage* img);
    void DrawHistogram(CvHistogram* histogram);
    ~Histogram();
private:
};
#endif