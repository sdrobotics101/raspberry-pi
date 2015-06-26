#ifndef Contour_hpp
#define Contour_hpp

#include <vector>
#include <opencv2/opencv.hpp>

class Contour {
 public:
	Contour();
	Contour(std::vector < cv::Point > points);
	std::vector < cv::Point > get_points();
	double get_area();
 protected:
	 std::vector < cv::Point > contour;
	double area;
};

#endif				// Contour_hpp
