#ifndef Circle_hpp
#define Circle_hpp

#include <vector>
#include <opencv2/opencv.hpp>
#include "Contour.hpp"

class Circle:public Contour {
 public:
	Circle(std::vector < cv::Point > points);
	cv::Point2d get_center();
	double get_radius();
	double get_area_ratio();
 protected:
	 cv::Point2d center;
	double radius;
	double area_ratio;
};

#endif				// Circle_hpp
