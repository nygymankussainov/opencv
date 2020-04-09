#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
    Mat m = imread("cat.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    Mat mask=Mat::zeros(m.size(), CV_8UC1),maskBlur,mc;
    // mask is a disk
    circle(mask, Point(200, 200), 100, Scalar(255),-1);

    Mat negMask;
    // neg mask
    bitwise_not(mask, negMask);
    circle(mask, Point(200, 200), 100, Scalar(255), -1);
    Mat md,mdBlur,mdint;

    m.copyTo(md);

    // All pixels outside mask set to 0
    md.setTo(0, negMask);
    imshow("mask image", md);
    // Convert image to int
    md.convertTo(mdint, CV_32S);
    Size fxy(5, 5);
    blur(mdint, mdBlur, fxy);
    mdBlur = mdBlur;
    mask.convertTo(maskBlur, CV_32S);

    blur(maskBlur, maskBlur, fxy);
    Mat mskB;
    mskB.setTo(1, negMask);
    divide(mdBlur,maskBlur/255,mdBlur);

    mdBlur.convertTo(mc, CV_8U);
    resize(mc,mc,Size(),0.5,0.5);
    imshow("Blur with mask", mc);
    imwrite("testBlur.png", mc);
    waitKey();

}
