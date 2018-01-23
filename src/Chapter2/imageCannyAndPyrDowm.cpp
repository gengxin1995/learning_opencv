//
// Created by 耿欣 on 2018/1/23.
//

#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* doPyrDown(IplImage* in, int filter = CV_GAUSSIAN_5x5) {
    assert(in -> width % 2 == 0 && in -> height % 2 == 0);
    IplImage* out = cvCreateImage(cvSize(in -> width / 2, in -> height / 2), in -> depth, in -> nChannels);
    cvPyrDown(in, out);
    return (out);
}

IplImage *doCanny(IplImage *in, double lowThresh, double highThresh, double aperture) {
    IplImage *out = cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 1);
    cvCanny(in, out, lowThresh, highThresh, aperture);
    return (out);
}

int main(int argc, char* argv[]) {
    IplImage *img = cvLoadImage(argv[1]);

    cvNamedWindow("Example4-in");
    cvNamedWindow("Example4-out");

    cvShowImage("Example4-in", img);

    IplImage *out = doPyrDown(img);
    out = doCanny(out, 10, 100, 3);

    cvShowImage("Example4-out", out);

    cvReleaseImage(&out);
    cvWaitKey(0);
    cvDestroyWindow("Example4-in");
    cvDestroyWindow("Example4-out");
}