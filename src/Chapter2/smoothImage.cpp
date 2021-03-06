//
// Created by 耿欣 on 2018/1/23.
//

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char* argv[]) {
    IplImage *img = cvLoadImage(argv[1]);

    cvNamedWindow("Example4-in");
    cvNamedWindow("Example4-out");

    cvShowImage("Example4-in", img);

    IplImage *out = cvCreateImage(
            cvGetSize(img), //图像结构大小
            IPL_DEPTH_8U, //各通道每个像素点的类型
            3); //通道数

    cvSmooth(img, out, 3, 3);

    cvShowImage("Example4-out", out);

    cvReleaseImage(&out);
    cvWaitKey(0);
    cvDestroyWindow("Example4-in");
    cvDestroyWindow("Example4-out");
}
