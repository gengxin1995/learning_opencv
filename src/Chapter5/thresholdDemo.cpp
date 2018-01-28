//
// Created by 耿欣 on 2018/1/26.
//

#include <stdio.h>
#include <cv.h>
#include <highgui.h>

void sum_rgb (IplImage *src, IplImage *dst) {
    IplImage *r = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    IplImage *g = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    IplImage *b = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);

    cvSplit(src, r, g, b, NULL);

    IplImage *s = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);

    //使用加权加法算法对三个通道求和
    cvAddWeighted(r, 1. / 3, g, 1. / 3, 0.0, s);
    cvAddWeighted(s, 2. / 3, b, 1. / 3, 0.0, s);

    cvThreshold(s, dst, 100, 100, CV_THRESH_TRUNC);

    cvReleaseImage(&r);
    cvReleaseImage(&g);
    cvReleaseImage(&b);
    cvReleaseImage(&s);
}

int main(int argc, char *argv[]){
    cvNamedWindow("Threshold", 1);

    IplImage *src = cvLoadImage(argv[1]);
    IplImage *dst = cvCreateImage(cvGetSize(src), src->depth, 1);
    sum_rgb(src, dst);

    cvShowImage("Threshold", dst);

    cvWaitKey(0);
    cvDestroyWindow("Threshold");
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
}