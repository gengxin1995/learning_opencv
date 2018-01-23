//
// Created by 耿欣 on 2018/1/23.
//

#include <opencv/cv.h>
#include <opencv/highgui.h>

int g_slider_size = 2;

IplImage* doPyrDown(IplImage* in, int filter = CV_GAUSSIAN_5x5) {
    assert(in->width % 2 == 0 && in->height % 2 == 0);
    IplImage *out = cvCreateImage(cvSize(in->width / 2, in->height / 2), in->depth, in->nChannels);
    cvPyrDown(in, out);
    return (out);
}

int main(int argc, char* argv[]) {
    CvCapture* capture = cvCreateFileCapture(argv[1]);
    cvNamedWindow("practice", CV_WINDOW_AUTOSIZE);
    cvCreateTrackbar("position", "practice", &g_slider_size, 6);
    IplImage* frame;
    while (1) {
        frame = cvQueryFrame(capture);
        if (!frame) break;
        for (int i = 0; i < g_slider_size; i++) {
            frame = doPyrDown(frame);
        }
        cvShowImage("practice", frame);
        char c = cvWaitKey(33);
        if (c == 27) break;
    }
    cvReleaseCapture(&capture);
    cvDestroyWindow("practice");
}