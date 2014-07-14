#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "../HSVImage.hpp"

std::string window = "Color Follower";
int hue_upper_threshold;
std::string hue_upper_trackbar = "Hue Upper Threshold:";
int hue_lower_threshold;
std::string hue_lower_trackbar = "Hue Lower Threshold";
int canny_threshold;
std::string canny_trackbar = "Canny Threshold:";
HSVImage img;

void trackbar_callback(int param, void *obj)
{
	cv::Mat input;
	img.rgb.copyTo(input);
	cv::Mat hsv_thresh_hue_upper;
	cv::Mat hsv_thresh_hue_lower;
	cv::Mat thresholded;
	cv::threshold(img.hsv, hsv_thresh_hue_lower, hue_lower_threshold, 255,
		      CV_THRESH_BINARY);
	cv::threshold(img.hsv, hsv_thresh_hue_upper, hue_upper_threshold, 255,
		      CV_THRESH_BINARY_INV);
	thresholded = hsv_thresh_hue_lower & hsv_thresh_hue_upper;
	cv::Mat gray0;
	thresholded.copyTo(gray0);
	cv::Mat gray;
	cv::Canny(gray0, gray, 0, canny_threshold, 5);
	cv::dilate(gray, gray, cv::Mat(), cv::Point(-1, -1));
	std::vector < std::vector < cv::Point > >contours;
	cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	for (uint i = 0; i < contours.size(); i++) {
		cv::Scalar color(0, 0, 0);
		cv::drawContours(input, contours, i, color, 5, 8);
	}
	cv::imshow(window, input);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] <<
		    " [INPUT FILE]" << std::endl;
		return EXIT_FAILURE;
	}
	cv::Mat raw_image = cv::imread(argv[1]);
	img = HSVImage(raw_image);
	cv::namedWindow(window, 0);
	cv::createTrackbar(hue_lower_trackbar, window, &hue_lower_threshold,
			   255, trackbar_callback);
	cv::createTrackbar(hue_upper_trackbar, window, &hue_upper_threshold,
			   255, trackbar_callback);
	cv::createTrackbar(canny_trackbar, window, &canny_threshold, 255,
			   trackbar_callback);
	cv::imshow(window, raw_image);
	cv::waitKey(0);

	return EXIT_SUCCESS;
}
