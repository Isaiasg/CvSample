/**
* Isaias Gonzalez <siderevs@gmail.com>
*/

#ifndef RANSAC_H
#define RANSAC_H
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>

class Ransac 
{
public:
    Ransac();
    void FindBestLine(CvSeq* lines, IplImage* frame);
    CvPoint* GetRandomPoint();
    ~Ransac();
private:
    CvSeq* ConvertLinesToPoints();
};
#endif