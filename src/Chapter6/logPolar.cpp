//
// Created by 耿欣 on 2018/1/29.
//

#include <cv.h>
#include <highgui.h>

int main(int argc, char *argv[]) {
    IplImage *src;
    double M;
    if (argc == 3 && ((src = cvLoadImage(argv[1], 1)) != 0)) {
        M = atof(argv[2]);
        IplImage *dst = cvCreateImage(cvGetSize(src), 8, 3);
        IplImage *src2 = cvCreateImage(cvGetSize(src), 8, 3);
        cvLogPolar(src, dst, cvPoint2D32f(src->width / 4, src->height / 2), M, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);
        cvLogPolar(dst, src2, cvPoint2D32f(src->width / 4, src->height / 2), M, CV_INTER_LINEAR + CV_WARP_INVERSE_MAP);
        cvNamedWindow("log-polar", 1);
        cvShowImage("log-polar", dst);
        cvNamedWindow("inverse log-polar", 1);
        cvShowImage("inverse log-polar", src2);
        cvWaitKey();
    }
    return 0;
}