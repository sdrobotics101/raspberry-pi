#include <algorithm>
#include <math.h>
#include <opencv2/opencv.hpp>
#include "Rectangle.hpp"

Rectangle::Rectangle(std::vector < cv::Point > points)
{
	rectangle = cv::minAreaRect(points);
	angle = (double)rectangle.angle;
	if (cos(angle * 180.0 / M_PI) < 0.2) {
		std::swap(rectangle.size.width, rectangle.size.height);
		angle -= 90.0;
		rectangle.angle -= 90.0;
	}
	if (angle < -90.0) {
		angle += 180.0;
		rectangle.angle += 180.0;
	}
	aspect_ratio = (double)get_width() / (double)get_height();
	area = (double)get_width() * (double)get_height();
	area_ratio = area / cv::contourArea(points);
	cv::Point2f pts[4];
	rectangle.points(pts);
	for (int i = 0; i < 4; i++)
		contour.push_back(pts[i]);
}

cv::Point2f Rectangle::get_center()
{
	return rectangle.center;
}

double Rectangle::get_width()
{
	return rectangle.size.width;
}

double Rectangle::get_height()
{
	return rectangle.size.height;
}

double Rectangle::get_aspect_ratio()
{
	return aspect_ratio;
}

double Rectangle::get_angle()
{
	return angle;
}

double Rectangle::get_area_ratio()
{
	return area_ratio;
}
