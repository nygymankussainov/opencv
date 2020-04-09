#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
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
		cv::Rect region(x-radius, y-radius, radius * 2, radius * 2);

		if (0 <= region.x
			&& 0 <= region.width
			&& region.x + region.width <= u->m.cols
			&& 0 <= region.y
			&& 0 <= region.height
			&& region.y + region.height <= u->m.rows) {
			if ( u->cap.isOpened() ) {
			
				cv::GaussianBlur(u->m(region), u->m(region), Size(radius, radius), 4);
            	imshow("i", u->m);
				waitKey(10);
			}

		}
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
