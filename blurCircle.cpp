#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <iostream>

cv::Mat matFrame;

void mouse(int k, int x, int y, int, void *p)
{
    if ( k == CV_EVENT_MOUSEMOVE ) {

    	IplImage* src, * res, * roi;
		src = cvCreateImage(cvSize(matFrame.cols, matFrame.rows), 8, 3);
		IplImage tmp = matFrame;
		cvCopy(&tmp, src);
    	res = cvCreateImage(cvGetSize(src), 8, 3);
    	roi = cvCreateImage(cvGetSize(src), 8, 1);


	    /* prepare the 'ROI' image */
	    cvZero(roi);

		cvCircle(
			roi,
			cvPoint(x, y),
			50,
			CV_RGB(255, 255, 255),
			-1, 8, 0
    	);

		/* extract subimage */
		cvAnd(src, src, res, roi);

		/*
		* do the main processing with subimage here.
		* in this example, we simply invert the subimage
		*/
		// cvNot(res, res);
		cvSmooth(res, res, CV_GAUSSIAN, 55);


		/* 'restore' subimage */
		IplImage* roi_C3 = cvCreateImage(cvGetSize(src), 8, 3);
		cvMerge(roi, roi, roi, NULL, roi_C3);
		cvAnd(res, roi_C3, res, NULL);

		/* merge subimage with original image */
		cvNot(roi, roi);
		cvAdd(src, res, res, roi);

		/* show result */
		cvShowImage("original", res);
		cvWaitKey(10);

	    /* be tidy */
		cvReleaseImage(&src);
		cvReleaseImage(&res);
		cvReleaseImage(&roi);
	}
}

int		main(int argc, char **argv) {

	cvNamedWindow("original",CV_WINDOW_AUTOSIZE);

	cv::VideoCapture capture;
    cv::setMouseCallback("original",mouse, NULL);
	cv::namedWindow("original", CV_WINDOW_AUTOSIZE);
	capture.open(argv[1]);
	while ( capture.isOpened() ) {


		capture.read(matFrame);
		if ( matFrame.empty() ) {
			break ;
		}
		cv::imshow("original", matFrame);
		char c = cvWaitKey(33);
		if (c == 27) { // если нажата ESC - выходим
				break;
		}

	}

	return 0;
}
