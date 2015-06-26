#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <vector>
#include <opencv2/opencv.hpp>
#include "Contour.hpp"

class Rectangle:public Contour {
 public:
	Rectangle(std::vector < cv::Point > points);
	cv::Point2f get_center();
	double get_width();
	double get_height();
	double get_aspect_ratio();
	double get_angle();
	double get_area_ratio();
 protected:
	 cv::RotatedRect rectangle;
	double aspect_ratio;
	double angle;
	double area_ratio;
};

#endif				// Rectangle_hpp
