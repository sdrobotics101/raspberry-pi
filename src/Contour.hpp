/* Contour.hpp -- Header file for Contour class

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

#ifndef Contour_hpp
#define Contour_hpp

#include <vector>
#include <opencv2/opencv.hpp>

class Contour {
 public:
	Contour(std::vector < cv::Point2d > points);
	std::vector < cv::Point2d > get_points();
	double get_area();
 protected:
	 std::vector < cv::Point2d > contour;
	double area;
};

#endif				// Contour_hpp