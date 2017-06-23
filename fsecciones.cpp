/**
* Isaias Gonzalez <siderevs@gmail.com>
*/
#include "stdafx.h"
#include "Histogram.h"
#include "Ransac.h"
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include <stdio.h>

int thresh = 195;

CvSeq* findLines(IplImage* imgor, int thresh);
IplImage* CreateROI(IplImage* original, int width, int heigh, int x, int y);
void DrawLines(IplImage* original, CvSeq* lines, CvScalar color);

int main( int argc, char** argv )
{
    CvCapture* capture = 0;

    #ifdef _DEBUG
      capture = cvCaptureFromAVI("D:\\Tesis\\Video017.avi");
    #else
    if( argc != 2 || !(capture = cvCaptureFromAVI( argv[1])))
        return -1;
    #endif

    cvNamedWindow("original",1);

    IplImage* frame;

    for(;;)
    {
        frame = cvQueryFrame( capture );
        if( !frame )
            break;

        int quarter = frame->height/4;

        IplImage* uno = CreateROI(frame, frame->width/4, quarter, 0, quarter);
        IplImage* dos = CreateROI(frame, frame->width/4, quarter, frame->width/4, quarter); 
        IplImage* tres = CreateROI(frame, frame->width/4, quarter, (frame->width/4)*2, quarter); 
        IplImage* cuatro = CreateROI(frame, frame->width/4, quarter, (frame->width/4)*3, quarter); 
        IplImage* cinco = CreateROI(frame, frame->width /4, quarter*2/3, frame->width/4, quarter*2);
        IplImage* seis = CreateROI(frame, frame->width /4, quarter*2/3, (frame->width/4)*2, quarter*2);
        IplImage* siete = CreateROI(frame, frame->width /4, quarter, (frame->width/4)/2, quarter*1.5);
        IplImage* ocho = CreateROI(frame, frame->width /4, quarter, (frame->width/4)*2.5, quarter*1.5);

        //primer cuadro
        CvSeq* lines2 = findLines(uno, thresh );
        DrawLines(uno, lines2, CV_RGB(255,0,0));
        cvReleaseMemStorage(&lines2->storage);

        /*Histogram *histogram = new Histogram();
        CvHistogram* hist1 = histogram->GetHistogram(cuatro);
        histogram->DrawHistogram(hist1);*/
        
        //segundo cuadro
        CvSeq* lines3 = findLines(dos, thresh );
        DrawLines(dos, lines3, CV_RGB(0, 255, 0));
        cvReleaseMemStorage(&lines3->storage);

        //tercer cuadro
        CvSeq* lines4 = findLines(tres, thresh );
        DrawLines(tres, lines4, CV_RGB(255, 0, 0));
        cvReleaseMemStorage(&lines4->storage);

        //cuarto cuadro
        CvSeq* lines5 = findLines(cuatro, thresh );
        //Ransac* ransac = new Ransac();
        //ransac->FindBestLine(lines5, cuatro);
        DrawLines(cuatro, lines5, CV_RGB(255, 0, 0));
        cvReleaseMemStorage(&lines5->storage);

        //quinto cuadro
        CvSeq* lines6 = findLines(cinco, thresh );
        DrawLines(cinco, lines6, CV_RGB(255, 0, 0));
        cvReleaseMemStorage(&lines6->storage);

        //sexto cuadro
        CvSeq* lines7 = findLines(seis, thresh );
        DrawLines(seis, lines7, CV_RGB(255, 0, 0));
        cvReleaseMemStorage(&lines7->storage);

        //septimo cuadro
        CvSeq* lines8 = findLines(siete, thresh );
        DrawLines(siete, lines8, CV_RGB(255, 0, 0));
        cvReleaseMemStorage(&lines8->storage);

        //septimo cuadro
        CvSeq* lines9 = findLines(ocho, thresh );
        DrawLines(ocho, lines9, CV_RGB(255, 0, 0));
        cvReleaseMemStorage(&lines9->storage);

        //cvAddS(seis, CV_RGB(175, 75, 75), seis);
        //cvAddS(cinco, CV_RGB(75, 75, 75), cinco);
        //cvAddS(cuatro, CV_RGB(100, 100, 100), cuatro);
        //cvAddS(tres, CV_RGB(75, 75, 75), tres);
        //cvAddS(dos, CV_RGB(100, 100, 100), dos);*/
        //cvAddS(uno, CV_RGB(75, 75, 75), uno);
        //cvAddS(ocho, CV_RGB(75, 75, 75), ocho);

        cvReleaseImage( &uno );
        cvReleaseImage( &dos );
        cvReleaseImage( &tres );
        cvReleaseImage( &cuatro );
        cvReleaseImage( &cinco );
        cvReleaseImage( &seis );
        cvReleaseImage( &siete );
        cvReleaseImage( &ocho );

        cvShowImage("original", frame);
        cvWaitKey(35);
    }

    cvReleaseCapture( &capture);

    return 0;
}

CvSeq* findLines(IplImage* imgor, int thresh)
{
    IplImage* gray = cvCreateImage( cvGetSize(imgor), 8, 1);
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* contours = 0;

    // Converts to gray
    
    //cvPyrMeanShiftFiltering(imgor, imgor, 1, 2, 1);
    //cvNamedWindow("Contours",1);
    //cvShowImage( "Contours", imgor );
    cvCvtColor( imgor, gray, CV_BGR2GRAY );
    //cvEqualizeHist(gray, gray);
    cvThreshold( gray, gray, thresh, 255, CV_THRESH_BINARY );
    //cvAdaptiveThreshold( gray, gray, 255, CV_THRESH_BINARY, 0, 15, thresh);
    cvFindContours( gray, storage, &contours );
    //cvZero( gray );

    if( contours )
        cvDrawContours( gray, contours, cvScalarAll(255), cvScalarAll(255), 100 );
    
    /*cvNamedWindow("Contours",1);
    cvShowImage( "Contours", gray );*/

    cvReleaseMemStorage( &storage );

    CvMemStorage* storage2 = cvCreateMemStorage(0);                      //#, angulo, longitud
    CvSeq* lines = cvHoughLines2( gray, storage2, CV_HOUGH_PROBABILISTIC, 2*CV_PI, CV_PI/3, 7, 18, 1 );
    cvReleaseImage( &gray );

    return lines;
}

IplImage* CreateROI(IplImage* original, int width, int heigh, int x, int y)
{
    IplImage* sub_img = cvCreateImageHeader(cvSize(width, heigh), original->depth, original->nChannels); 
    sub_img->origin = original->origin;
    sub_img->widthStep = original->widthStep;
    sub_img->imageData = original->imageData + y * original->widthStep + x * original->nChannels;
    return sub_img;
}


void DrawLines(IplImage* original, CvSeq* lines, CvScalar color)
{
    for( int i = 0; i < lines->total; i++ )
    {
        CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
        cvLine( original, line[0], line[1], color, 1, 1 );
    }
}