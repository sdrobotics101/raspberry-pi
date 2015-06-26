#include <math.h>
#include <opencv2/opencv.hpp>
#include "Circle.hpp"

 Circle::Circle(std::vector < cv::Point > points):Contour(points)
{
	cv::Point2f center_tmp;
	float radius_tmp;
	cv::minEnclosingCircle(contour, center_tmp, radius_tmp);
	center = center_tmp;
	radius = radius_tmp;
	area = M_PI * pow(radius, 2);
	area_ratio = area / cv::contourArea(contour);
}

cv::Point2d Circle::get_center()
{
	return center;
}

double Circle::get_radius()
{
	return radius;
}

double Circle::get_area_ratio()
{
	return area_ratio;
}
