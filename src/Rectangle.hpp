/* Rectangle.hpp -- Header file for Rectangle class

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

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <vector>
#include <opencv2/opencv.hpp>
#include "Contour.hpp"

class Rectangle:public Contour {
 public:
	Rectangle(std::vector < cv::Point2d > points);
	cv::Point2f get_center();
	double get_width();
	double get_height();
	double get_aspect_ratio();
	double get_angle();
	double get_log_area_ratio();
 protected:
	 cv::RotatedRect rectangle;
	double aspect_ratio;
	double angle;
	double log_area_ratio;
};

#endif				// Rectangle_hpp
