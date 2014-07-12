#include <stdlib.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../HSVImage.hpp"

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] <<
		    " [INPUT FILE] [OUTPUT FILE]" << std::endl;
		return EXIT_FAILURE;
	}
	cv::Mat input = cv::imread(argv[1]);
	HSVImage input_hsv = HSVImage(input);
	cv::Mat hsv_thresh_hue_upper;
	cv::Mat hsv_thresh_hue_lower;
	cv::Mat thresholded;
	//cv::threshold(*(input_hsv.get_hue_mat()), hsv_thresh_hue_lower, 115, 255, CV_THRESH_BINARY);
	//cv::threshold(*(input_hsv.get_hue_mat()), hsv_thresh_hue_upper, 127, 255, CV_THRESH_BINARY_INV);
	cv::threshold(*(input_hsv.get_hue_mat()), hsv_thresh_hue_lower, 40, 255,
		      CV_THRESH_BINARY);
	cv::threshold(*(input_hsv.get_hue_mat()), hsv_thresh_hue_upper, 50, 255,
		      CV_THRESH_BINARY_INV);
	thresholded = hsv_thresh_hue_lower & hsv_thresh_hue_upper;
	std::vector < std::vector < cv::Point > >contours;
	std::vector < cv::Vec4i > hierarchy;
	cv::findContours(thresholded, contours, hierarchy, CV_RETR_CCOMP,
			 CV_CHAIN_APPROX_SIMPLE);
	for (int i = 0; i >= 0; i = hierarchy[i][0]) {
		cv::Scalar color(255, 0, 0);
		cv::drawContours(input, contours, i, color, 1, 8, hierarchy);
	}
	cv::namedWindow("CV", 0);
	cv::imshow("CV", input);
	cv::waitKey();
	cv::imwrite(argv[2], input);

	return EXIT_SUCCESS;
}
