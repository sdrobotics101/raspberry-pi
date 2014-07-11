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
	cv::Mat output;
	cv::threshold(*(input_hsv.get_hue_mat()), hsv_thresh_hue_lower, 40, 255,
		      CV_THRESH_BINARY);
	cv::threshold(*(input_hsv.get_hue_mat()), hsv_thresh_hue_upper, 50, 255,
		      CV_THRESH_BINARY);
	output = hsv_thresh_hue_lower & hsv_thresh_hue_upper;
	cv::imwrite(argv[2], output);

	return EXIT_SUCCESS;
}
