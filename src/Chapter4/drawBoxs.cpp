//
// Created by 耿欣 on 2018/1/24.
//

#include <opencv/cv.h>
#include <opencv/highgui.h>

void my_mouse_call_back(int event, int x, int y, int flag, void *param);

CvRect box;
bool drawing_box = false;

void draw_box(IplImage *img, CvRect rect) {
    cvRectangle(img, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), cvScalar(255, 0, 0));
}

int main(int argc, char* argv[]) {
    box = cvRect(-1, -1, 0, 0);
    IplImage *image = cvCreateImage(cvSize(200, 200), IPL_DEPTH_8U, 3);
    cvZero(image);
    IplImage *temp = cvCloneImage(image);

    cvNamedWindow("Box Example");

    cvSetMouseCallback("Box Example", my_mouse_call_back, (void *) image);

    while (1) {
        cvCopy(image, temp);
        if (drawing_box) draw_box(temp, box);
        cvShowImage("Box Example", temp);
        if ( cvWaitKey(15) == 27) break;
    }
    cvReleaseImage( &image );
    cvReleaseImage( &temp );
    cvDestroyWindow( "Box Example" );

    return 0;
}

void my_mouse_call_back(int event, int x, int y, int flag, void *param) {
    IplImage *image = (IplImage *) param;
    switch (event) {
        case CV_EVENT_MOUSEMOVE:
            if ( drawing_box ) {
                box.width = x-box.x;
                box.height = y-box.y;
            }
            break;
        case CV_EVENT_LBUTTONDOWN:
            drawing_box = true;
            box = cvRect(x, y, 0, 0);
            break;
        case CV_EVENT_LBUTTONUP:
            drawing_box = false;
            if (box.width<0) {
                box.x += box.width;
                box.width *= -1;
            }
            if (box.height<0) {
                box.y += box.height;
                box.height *= -1;
            }
            draw_box(image, box);
            break;
        default:
            break;
    }
}