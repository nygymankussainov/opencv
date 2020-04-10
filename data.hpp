#ifndef DATA_HPP
# define DATA_HPP

# include <iostream>
# include <fstream>
# include <exception>
# include <opencv2/highgui.hpp>
# include <opencv2/opencv.hpp>
# include <opencv2/imgproc.hpp>
# include <opencv2/core.hpp>

typedef struct s_data {

	cv::Mat matFrame;
	cv::VideoCapture capture;
	std::string video;
	int radius = 50;
	int ap_width = 55;
	int ap_height = 0;
	double sigma2 = 0.0;
	double sigma1 = 0.0;
}				t_data;

t_data*	ini_parser(void);

#endif
