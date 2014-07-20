/* Circle.cpp -- Implementation of Circle class

   Copyright (C) 2014 Tushar Pankaj
   
   This file is part of San Diego Robotics 101 Robosub.
   
   San Diego Robotics 101 Robosub is free software: you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by he Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.
   
   San Diego Robotics 101 Robosub is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
   Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with San Diego Robotics 101 Robosub.  If not, see
   <http://www.gnu.org/licenses/>. */

#include <math.h>
#include <opencv2/opencv.hpp>
#include "Circle.hpp"

 Circle::Circle(std::vector < cv::Point2d > points):Contour(points)
{
	cv::Point2f center_tmp;
	float radius_tmp;
	cv::minEnclosingCircle(contour, center_tmp, radius_tmp);
	center = center_tmp;
	radius = radius_tmp;
	area = M_PI * pow(radius, 2);
	log_area_ratio = log(area / cv::contourArea(contour));
}

cv::Point2d Circle::get_center()
{
	return center;
}

double Circle::get_radius()
{
	return radius;
}
