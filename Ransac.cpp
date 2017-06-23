/**
* Isaias Gonzalez <siderevs@gmail.com>
*/
#include "stdafx.h"
#include "Ransac.h"
#include <time.h>

CvSeq* inputLines;
CvMemStorage* storage;

Ransac::Ransac(){}

void Ransac::FindBestLine(CvSeq* lines, IplImage* frame)
{
    inputLines = lines;
    //printf("%d total lineas\n", lines->total);
    CvSeq* points = ConvertLinesToPoints();
    //printf("%d total puntos\n", points->total);
    srand(time(NULL));
    int total = points->total;
    if(total != 0)
    {
        for(int i = 0; i < points->total / 3; i++)
        {
            int indexPoint1 = rand() % total;
            int indexPoint2 = rand() % total;
            CvPoint* startPoint = (CvPoint*)cvGetSeqElem(points, indexPoint1);
            CvPoint* endPoint = (CvPoint*)cvGetSeqElem(points, indexPoint2);
            cvLine( frame, *startPoint, *endPoint, CV_RGB(255, 0, 0), 1, 1 );
            //printf("Points  %d %d\n", indexPoint1, indexPoint2);
        }
    }
}

CvSeq* Ransac::ConvertLinesToPoints()
{
    storage = cvCreateMemStorage();
    CvSeq* seq = cvCreateSeq(CV_32SC2, sizeof(CvSeq), sizeof(CvPoint), storage);
    CvSeqWriter writer;
    cvStartAppendToSeq( seq, &writer );


    for(int i = 0; i < inputLines->total; i++)
    {
        CvPoint* temp = (CvPoint*)cvGetSeqElem(inputLines,i);
        CV_WRITE_SEQ_ELEM( temp[0], writer );
        CV_WRITE_SEQ_ELEM( temp[1], writer );
    }
    cvEndWriteSeq( &writer );

    return seq;
}

Ransac::~Ransac()
{
    cvReleaseMemStorage( &storage );
}