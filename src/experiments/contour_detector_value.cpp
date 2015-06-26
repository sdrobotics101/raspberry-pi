#include <stdlib.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "../HSVImage.hpp"

int main(int argc, char *argv[])
{
	if (argc != 6) {
		std::cerr << "Usage: " << argv[0] <<
		    " [INPUT FILE] [VALUE LOWER THRESHOLD] [VALUE UPPER THRESHOLD] [CANNY THRESHOLD] [OUTPUT FILE]"
		    << std::endl;
		return EXIT_FAILURE;
	}
	cv::Mat raw_image = cv::imread(argv[1]);
	HSVImage img = HSVImage(raw_image);
	cv::Mat hsv_thresh_value_upper;
	cv::Mat hsv_thresh_value_lower;
	cv::Mat thresholded;
	cv::threshold(img.value, hsv_thresh_value_lower, atoi(argv[2]), 255,
		      cv::THRESH_BINARY);
	cv::threshold(img.value, hsv_thresh_value_upper, atoi(argv[3]), 255,
		      cv::THRESH_BINARY_INV);
	thresholded = hsv_thresh_value_lower & hsv_thresh_value_upper;
	cv::Mat gray0;
	thresholded.copyTo(gray0);
	cv::Mat gray;
	cv::Canny(gray0, gray, 0, atoi(argv[4]), 5);
	cv::dilate(gray, gray, cv::Mat(), cv::Point(-1, -1));
	std::vector < std::vector < cv::Point > >contours;
	std::vector < cv::RotatedRect > boundingRects;
	cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	/*for (uint i = 0; i < contours.size(); i++)    // Remove contours with area < 1000
	   {
	   if (cv::contourArea(contours.at(i)) < 1000) {
	   contours.erase(contours.begin() + i);
	   i--;
	   }
	   } */
	for (uint i = 0; i < contours.size(); i++)	// Compute minimum area bounding rectangles
		boundingRects.push_back(cv::minAreaRect(contours.at(i)));
	cv::Mat output;
	img.rgb.copyTo(output);
	for (uint i = 0; i < contours.size(); i++) {	// Show everything
		//cv::drawContours(output, contours, i, cv::Scalar(0, 0, 0), 5, 8);
		cv::Point2f boundingPoints[4];
		boundingRects.at(i).points(boundingPoints);
		//std::cout << "Contour " << i << ": [";
		cv::Scalar color(0, 0, 0);
		for (int i = 0; i < 4; i++)
			cv::line(output, boundingPoints[i],
				 boundingPoints[(i + 1) % 4], color);
		//cv::imshow("Contour Detector", output);
		//for (uint j = 0; j < contours.at(i).size(); j++) {
		//std::cout << contours.at(i).at(j);
		//if (j != contours.at(i).size() - 1)
		//std::cout << ", ";
		//}
		//std::cout << "], Bounding: ";
		//for (int j = 0; j < 4; j++) {
		//      std::cout << boundingPoints[j];
		//      if (j != 3)
		//                      std::cout << ", ";
		//}
		//std::cout << std::endl;
	}
	cv::imwrite(argv[5], output);
	/*cv::namedWindow("CV", 0);
	   cv::imshow("CV", thresholded);
	   cv::waitKey(0); */

	return EXIT_SUCCESS;
}
