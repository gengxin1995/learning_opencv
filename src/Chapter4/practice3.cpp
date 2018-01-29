//
// Created by 耿欣 on 2018/1/24.
//

#include <cv.h>
#include <highgui.h>

#define cvCvtPixToPlane cvSplit
#define cvQueryHistValue_2D( hist, idx0, idx1 )   cvGetReal2D( (hist)->bins, (idx0), (idx1) )

CvRect g_rect;
bool g_isDown;

void my_callback(int event, int x, int y, int flag, void *param);

void high_light(IplImage *image, CvRect rect);

void draw_hist(IplImage *image, CvRect rect);

int main(int argc, char *argv[]) {
    IplImage *original_image = cvLoadImage(argv[1]);
    assert(original_image != NULL);
    IplImage *temp_image = cvCreateImage(cvGetSize(original_image), original_image->depth, original_image->nChannels);
    assert(temp_image != NULL);
    cvNamedWindow("show");
    cvSetMouseCallback("show", my_callback, (void *) temp_image);
    while (1) {
        IplImage *temp_image = cvCloneImage(original_image);
        if (g_isDown == true) {
            high_light(temp_image, g_rect);
            draw_hist(temp_image, g_rect);
        } else {
            high_light(temp_image, g_rect);
            draw_hist(temp_image, g_rect);
        }
        cvShowImage("show", temp_image);
        if (cvWaitKey(30) == 27) {
            break;
        }
    }
    cvDestroyAllWindows();
    return 0;
}

void my_callback(int event, int x, int y, int flag, void *param) {
    IplImage *image = (IplImage *) param;
    switch (event) {
        case CV_EVENT_MOUSEMOVE:
            if (g_isDown == true) {
                g_rect.width = x - g_rect.x;
                g_rect.height = y - g_rect.y;
            }
            break;
        case CV_EVENT_LBUTTONDOWN:
            g_isDown = true;
            g_rect = cvRect(x, y, 0, 0);
            break;
        case CV_EVENT_LBUTTONUP:
            g_isDown = false;
            if (g_rect.width<0) {
                g_rect.x += g_rect.width;
                g_rect.width *= -1;
            }
            if (g_rect.height<0) {
                g_rect.y += g_rect.height;
                g_rect.height *= -1;
            }
            high_light(image, g_rect);
            draw_hist(image, g_rect);
            break;
        default:
            break;
    }
}

void high_light(IplImage *image, CvRect rect) {
    assert(image != NULL);

    int col, row;
    for (row = rect.y; row <= rect.y + rect.height; row++) {
        uchar *ptr = (uchar *) (image->imageData + row * image->widthStep);
        for (col = rect.x; col <= rect.x + rect.width; col++) {
            ptr[(col * 3 + 1)] = 150;
            ptr[(col * 3 + 2)] = 110;
        }
        if (row >= image->height - 1) {
            row = image->height;
        }
    }
}

void draw_hist(IplImage *img, CvRect Rect) {
    if (Rect.x <= 0 || Rect.y <= 0 || Rect.height <= 0 || Rect.width <= 0) {
        return;
    }
    IplImage* hsv = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3 );
    IplImage *h_plane = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1 );
    IplImage *s_plane = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
    IplImage *v_plane=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
    IplImage *planes[] = {h_plane, s_plane};
    int h_bins = 16, s_bins = 8;
    int hist_size[] = {h_bins, s_bins};
    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 255};
    float *ranges[] = {h_ranges, s_ranges};
    cvCvtColor(img, hsv, CV_BGR2HSV);
    cvResetImageROI(img);
    cvCvtPixToPlane(hsv, h_plane, s_plane, v_plane, 0);
    CvHistogram *hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, ranges, 1);
    cvCalcHist(planes, hist, 0, 0);
    float max_value;
    cvGetMinMaxHistValue(hist, 0, &max_value, 0, 0);
    int height = 480;
    int width = (h_bins * s_bins * 6);
    IplImage *hist_img=cvCreateImage(cvSize(width,height),8,3);cvZero(hist_img);
    IplImage *hsv_color=cvCreateImage(cvSize(1,1),8,3);
    IplImage *rgb_color = cvCreateImage(cvSize(1, 1), 8, 3);
    int bin_w = width / (h_bins * s_bins);
    for(int h = 0; h < h_bins; h++) {
        for(int s = 0; s < s_bins; s++) {
            int i = h * s_bins + s;
            float bin_val = cvQueryHistValue_2D(hist, h, s);
            int intensity = cvRound(bin_val * height / max_value);
            cvSet2D(hsv_color, 0, 0, cvScalar(h * 180.f / h_bins, s * 255.f / s_bins, 255, 0));
            cvCvtColor(hsv_color, rgb_color, CV_HSV2BGR);
            CvScalar color = cvGet2D(rgb_color, 0, 0);
            cvRectangle(hist_img, cvPoint(i * bin_w, height), cvPoint((i + 1) * bin_w, height - intensity), color, -1,
                        8, 0);
        }
    }
    cvNamedWindow("H-S Histogram", 1);
    cvShowImage("H-S Histogram", hist_img);
}

