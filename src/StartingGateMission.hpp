/* StartingGateMission.hpp -- Header file for StartingGateMission class

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

#ifndef StartingGateMission_hpp
#define StartingGateMission_hpp

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Robot.hpp"
#include "Contour.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Mission.hpp"

class StartingGateMission:public Mission {
 public:
	StartingGateMission(Robot * robot_ptr);
	virtual void run();
 protected:
	std::vector<Circle> contours_to_circles(std::vector<Contour> contours);
	std::vector<Rectangle> contours_to_rectangles(std::vector<Contour> contours);
	std::vector<Rectangle> filter_rectangles(std::vector<Contour> detected_contours);
	std::vector<cv::Point2f> find_centroids(std::vector<Rectangle> rectangles);
	double find_angular_displacement(std::vector<cv::Point2f> centroids);
	std::string mission_name;
	Robot *robot;
};

#endif				// StartingGateMission_hpp
