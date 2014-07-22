/* blob_detect.cpp -- Experiment using SimpleBlobDetector

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

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] <<
		    " [INPUT FILE] [OUTPUT FILE]" << std::endl;
		return EXIT_FAILURE;
	}
	cv::Mat input = cv::imread(argv[1]);
	cv::SimpleBlobDetector::Params params;
	params.minDistBetweenBlobs = 50.0f;
	params.filterByInertia = false;
	params.filterByConvexity = false;
	params.filterByColor = false;
	params.filterByCircularity = false;
	params.filterByArea = true;
	params.minArea = 20.0f;
	params.maxArea = 500.0f;
	cv::SimpleBlobDetector blob_detector = cv::SimpleBlobDetector(params);
	blob_detector.create("SimpleBlob");
	std::vector < cv::KeyPoint > keypoints;
	blob_detector.detect(input, keypoints);
	for (unsigned int i = 0; i < keypoints.size(); i++) {
		cv::circle(input, keypoints.at(i).pt, 10,
			   cv::Scalar(255, 255, 255));
	}
	//cv::imwrite(argv[2], input);
	cv::imshow("Blob detector", input);

	return EXIT_SUCCESS;
}
