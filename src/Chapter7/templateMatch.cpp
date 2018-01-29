//
// Created by 耿欣 on 2018/1/29.
//

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    IplImage *src, *templ, *ftmp[6];
    int i;

    if (argc == 3 && ((src = cvLoadImage(argv[1], 1)) != 0) && ((templ = cvLoadImage(argv[2], 1)) != 0)) {
        int i_width = src->width - templ->width + 1;
        int i_height = src->height - templ->height + 1;
        for (int i = 0; i < 6; i++) {
            ftmp[i] = cvCreateImage(cvSize(i_width, i_height), 32, 1);
        }
        for (int i = 0; i < 6; i++) {
            cvMatchTemplate(src, templ, ftmp[i], i);
            cvNormalize(ftmp[i], ftmp[i], 1, 0, CV_MINMAX);
        }

        cvNamedWindow( "Template", 0 );
        cvShowImage(   "Template", templ );
        cvNamedWindow( "Image", 0 );
        cvShowImage(   "Image", src );

        cvNamedWindow( "SQDIFF", 0 );
        cvShowImage(   "SQDIFF", ftmp[0] );

        cvNamedWindow( "SQDIFF_NORMED", 0 );
        cvShowImage(   "SQDIFF_NORMED", ftmp[1] );

        cvNamedWindow( "CCORR", 0 );
        cvShowImage(   "CCORR", ftmp[2] );

        cvNamedWindow( "CCORR_NORMED", 0 );
        cvShowImage(   "CCORR_NORMED", ftmp[3] );

        cvNamedWindow( "CCOEFF", 0 );
        cvShowImage(   "CCOEFF", ftmp[4] );

        cvNamedWindow( "CCOEFF_NORMED", 0 );
        cvShowImage(   "CCOEFF_NORMED", ftmp[5] );

        cvWaitKey();

    }
    return 0;
}