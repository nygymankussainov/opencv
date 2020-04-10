#include "data.hpp"

void mouseCallBack(int event, int x, int y, int, void *p)
{
    if ( event == CV_EVENT_MOUSEMOVE ) {

		t_data *data = (t_data *)p;
    	IplImage* src, * res, * roi;
		src = cvCreateImage(cvSize(data->matFrame.cols, data->matFrame.rows), 8, 3);
		IplImage tmp = data->matFrame;
		cvCopy(&tmp, src);
    	res = cvCreateImage(cvGetSize(src), 8, 3);
    	roi = cvCreateImage(cvGetSize(src), 8, 1);

	    /* prepare the 'ROI' image */
	    cvZero(roi);

		cvCircle( roi, cvPoint(x, y), data->radius, CV_RGB(255, 255, 255), -1, 8, 0 );

		/* extract subimage */
		cvAnd(src, src, res, roi);

		/*
		* do the main processing with subimage here.
		* in this example, we simply invert the subimage
		*/
		cvSmooth(res, res, CV_GAUSSIAN, data->ap_width, data->ap_height, data->sigma1, data->sigma2);

		/* 'restore' subimage */
		IplImage* roi_C3 = cvCreateImage(cvGetSize(src), 8, 3);
		cvMerge(roi, roi, roi, NULL, roi_C3);
		cvAnd(res, roi_C3, res, NULL);

		/* merge subimage with original image */
		cvNot(roi, roi);
		cvAdd(src, res, res, roi);

		/* show result */
		cvShowImage("window", res);
		cvWaitKey(10);

	    /* be tidy */
		cvReleaseImage(&src);
		cvReleaseImage(&res);
		cvReleaseImage(&roi);
	}
}

void	showVideo(t_data *data) {

	cv::namedWindow("window", CV_WINDOW_AUTOSIZE);
    cv::setMouseCallback("window", mouseCallBack, data);
	while ( data->capture.isOpened() ) {


		data->capture.read(data->matFrame);
		if ( data->matFrame.empty() ) {
			break ;
		}
		cv::imshow("window", data->matFrame);
		int c = cv::waitKey(33);
		if (c == 27) { // если нажата ESC - выходим
			break ;
		}
		data->matFrame.release();
	}
	cv::destroyWindow("window");
	data->capture.release();
	data->matFrame.release();
}

int		main(void) {

	t_data *data = ini_parser();
	if ( !data )
		return 0;
	try {

		data->capture.open(data->video);
		if ( !data->capture.isOpened() )
			throw "Couldn't open video file";
	}
	catch(const char *err) {

		std::cout << err << std::endl;
		delete data;
		return 0;
	}
	showVideo(data);
	delete data;
	return 0;
}
