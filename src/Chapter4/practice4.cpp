//
// Created by 耿欣 on 2018/1/24.
//

#include <cv.h>
#include <highgui.h>

int g_slider_position = 0;
CvCapture* g_capture = NULL;
int i = 0;
int g_slider_position1 = 0;
bool t = true;

void onTrackerbarSlide(int pos) {
    cvSetCaptureProperty(
            g_capture,
            CV_CAP_PROP_POS_FRAMES,
            pos
    );
    i = pos;
}

void switch_callback(int position) {
    if (position == 0) {
        t = true;
    } else {
        t = false;
    }
}

int main(int argc, char** argv) {
    cvNamedWindow("Example3", CV_WINDOW_AUTOSIZE);
    g_capture = cvCreateFileCapture(argv[1]);
    int frames = (int) cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);
    if (frames != 0) {
        cvCreateTrackbar("Position", "Example3", &g_slider_position, frames, onTrackerbarSlide);
        cvCreateTrackbar("Position1", "Example3", &g_slider_position1, 1, switch_callback);
    }
    cvSetTrackbarPos("Position", "Example3", 1);
    cvSetTrackbarPos("Position1", "Example3", 0);

    IplImage* frame;
    while (1) {
        frame = cvQueryFrame(g_capture);
        if (!frame) break;
        cvShowImage("Example3", frame);
        cvSetTrackbarPos("Position", "Example3", i);
        if (t) {
            i += 10;
            cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, i);
        } else {
            cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, i);
        }
        char c = cvWaitKey(33);
        if (c == 27) break;
    }
    cvReleaseCapture(&g_capture);
    cvDestroyWindow("Example3");
}