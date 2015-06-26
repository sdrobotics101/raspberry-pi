#include <vector>
#include <opencv2/opencv.hpp>
#include "Contour.hpp"

Contour::Contour()
{
}

Contour::Contour(std::vector < cv::Point > points)
{
	contour = points;
	area = cv::contourArea(contour);
}

std::vector < cv::Point > Contour::get_points()
{
	return contour;
}

double Contour::get_area()
{
	return area;
}
