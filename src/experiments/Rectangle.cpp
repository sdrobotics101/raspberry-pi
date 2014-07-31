/* Rectangle.cpp -- Implementation of Rectangle class

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
