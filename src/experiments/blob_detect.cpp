#include <stdlib.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::
		    cerr << "Usage: " << argv[0] <<
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
