/* threshold.cpp -- Experiment which thresholds on hue

   Copyright (C) 2014 Tushar Pankaj
   
   This file is part of San Diego Robotics 101 Robosub.
   
   San Diego Robotics 101 Robosub is free software: you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.
   
   San Diego Robotics 101 Robosub is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
   Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with San Diego Robotics 101 Robosub.  If not, see
   <http://www.gnu.org/licenses/>. */

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
	cv::threshold(input_hsv.hue, hsv_thresh_hue_lower, 40, 255,
		      CV_THRESH_BINARY);
	cv::threshold(input_hsv.hue, hsv_thresh_hue_upper, 50, 255,
		      CV_THRESH_BINARY);
	output = hsv_thresh_hue_lower & hsv_thresh_hue_upper;
	cv::imwrite(argv[2], output);

	return EXIT_SUCCESS;
}
