#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

struct User
{
    VideoCapture cap;
    Mat m;
};

void mouse(int k, int x, int y, int s, void *p)
{
    User * u  = (User*)p;
    if ( k == EVENT_MOUSEMOVE ) {
		
		int radius = 75;
		Mat m;
		cv::cvtColor(u->m, m, CV_BGR2GRAY);
		Mat mask = Mat::zeros(m.size(), CV_8UC1), maskBlur, mc;

		circle(mask, Point(x, y), radius, Scalar(255), -1);

		Mat negMask;

		bitwise_not(mask, negMask);
		circle(mask, Point(x, y), radius, Scalar(255), -1);

		Mat md, mdBlur, mdint;

		m.copyTo(md);
		md.setTo(0, negMask);
		imshow("mask image", md);
		md.convertTo(mdint, CV_32S);
		Size fxy(10, 10);
		blur(mdint, mdBlur, fxy);
		mdBlur = mdBlur;
		mask.convertTo(maskBlur, CV_32S);

		blur(maskBlur, maskBlur, fxy);
		Mat mskB;
		mskB.setTo(1, negMask);
		divide(mdBlur, maskBlur/255, mdBlur);

		mdBlur.convertTo(mc, CV_8U);
		resize(mc, mc, Size(), 0.5, 0.5);
		
		cv::Mat imageROI;

		imageROI = u->m(cv::Rect(0,0,mc.cols, mc.rows));
		cvtColor(imageROI, imageROI, CV_BGR2GRAY);
		cv::addWeighted(imageROI, 1.0, mc, 0.3, 0., imageROI);

		imshow("Blur with mask", mc);
		imshow("asd", imageROI);
		// mc.copyTo(u->m(cv::Rect(x, y, mc.cols, mc.rows)));
		// if (0 <= region.x
		// 	&& 0 <= region.width
		// 	&& region.x + region.width <= u->m.cols
		// 	&& 0 <= region.y
		// 	&& 0 <= region.height
		// 	&& region.y + region.height <= u->m.rows) {
		// 	if ( u->cap.isOpened() ) {
			
        //     	imshow("i", u->m);
		// 		waitKey(10);
		// 	}

		// }
	}
}
int main(int,char**)
{
    User u;
    namedWindow("i", CV_WINDOW_AUTOSIZE);
    setMouseCallback("i",mouse,&u);
    u.cap.open("test_video4.mp4");
    while( u.cap.isOpened() )
    {
        u.cap.read(u.m);
        if (! u.m.empty())
            imshow("i", u.m);
        int k = waitKey(40);
        if ( k==27 ) break;
    }
    return 0;
}
