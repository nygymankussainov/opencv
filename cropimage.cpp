#include "opencv2/opencv.hpp"
using namespace cv;

int main()
{
    cv::Mat original = imread("cat.jpg");
	cv::Rect roi(150, 150, 120, 130); // I let you do the math ;)
	cv::Mat cropped = original(roi);
	cv::imwrite("cropped.png", cropped);

    return 0;
}
