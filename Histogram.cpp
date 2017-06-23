/**
* Isaias Gonzalez <siderevs@gmail.com>
*/
#include "stdafx.h"
#include "Histogram.h"

Histogram::Histogram(){}

CvHistogram* Histogram::GetHistogram(IplImage* img)
{
    IplImage* image= 0;
    CvHistogram* histo;

    //size of the histogram -1D histogram
    int bins = 256;
    int hsize[] = {bins};

    //ranges - grayscale 0 to 256
    float xranges[] = { 0, 256 };
    float* ranges[] = { xranges };  

    //create an 8 bit single channel image to hold a
    //grayscale version of the original picture
    image = cvCreateImage( cvGetSize(img), 8, 1 );

    cvCvtColor( img, image, CV_BGR2GRAY );

    //planes to obtain the histogram, in this case just one
    IplImage* planes[] = { image };

    //get the histogram and some info about it
    histo = cvCreateHist( 1, hsize, CV_HIST_ARRAY, ranges,1);
    cvCalcHist( planes, histo, 0, NULL);

    return histo;
}


void Histogram::DrawHistogram(CvHistogram* histogram)
{
    cvNamedWindow("histogram",1);

    //max and min value of the histogram
    float max_value = 0, min_value = 0;

    cvGetMinMaxHistValue( histogram, &min_value, &max_value);
    //create an 8 bits single channel image to hold the histogram paint it white
    IplImage* imgHistogram = cvCreateImage(cvSize(256, 50),8,1);
    cvRectangle(imgHistogram, cvPoint(0,0), cvPoint(256,50), CV_RGB(255,255,255),-1);

    //draw the histogram :P
    for(int i=0; i < 256; i++)
    {
        float value = cvQueryHistValue_1D( histogram, i);
        int normalized = cvRound(value*50/max_value);
        cvLine(imgHistogram,cvPoint(i,50), cvPoint(i,50-normalized), CV_RGB(0,0,0));
    }

    cvShowImage( "histogram", imgHistogram );
}

Histogram::~Histogram(){}