//
// Created by 耿欣 on 2018/1/24.
//

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char* argv[]) {
    IplImage* src;
    if (argc == 7 && ((src = cvLoadImage(argv[1], 1)) != 0)) {
        int x = atoi(argv[2]);
        int y = atoi(argv[3]);
        int width = atoi(argv[4]);
        int height = atoi(argv[5]);
        int add = atoi(argv[6]);

        IplImage *sub_img = cvCreateImageHeader(cvSize(width, height), src->depth, src->nChannels);
        sub_img->origin = src->origin;
        sub_img->widthStep = src->widthStep;
        sub_img->imageData = src->imageData + y * src->widthStep + x * src->nChannels;
        cvAddS(sub_img, cvScalar(add), sub_img);
        cvReleaseImageHeader(&sub_img);
        cvNamedWindow("ROI_Add", 1);
        cvShowImage("ROI_Add", src);
        cvWaitKey();
    }
    return 0;
}