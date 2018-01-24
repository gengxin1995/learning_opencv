//
// Created by 耿欣 on 2018/1/24.
//

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char* argv[]) {
    IplImage *src1, *src2;
    if (argc == 9 && ((src1 = cvLoadImage(argv[1], 1)) != 0) && ((src2 = cvLoadImage(argv[2], 1)) != 0)) {
        int x = atoi(argv[3]);
        int y = atoi(argv[4]);
        int width = atoi(argv[5]);
        int height = atoi(argv[6]);
        int alpha = (double)atof(argv[7]);
        int beta = (double)atof(argv[8]);
        cvSetImageROI(src1, cvRect(x, y, width, height));
        cvSetImageROI(src2, cvRect(0, 0, width, height));
        cvAddWeighted(src1, alpha, src2, beta, 0.0, src1);
        cvResetImageROI(src1);
        cvNamedWindow("Alpha_Blend", 1);
        cvShowImage("Alpha_Blend", src1);
        cvWaitKey();
    }
    return 0;
}