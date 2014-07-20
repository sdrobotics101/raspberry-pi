/* ContourDetector.cpp -- Implementation of ContourDetector class

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

#include <opencv2/opencv.hpp>
#include "Contour.hpp"
#include "ContourDetector.hpp"

ContourDetector::Params::Params()
{
	filterByHue = false;
	minHue = 0;
	maxHue = 255;

	filterBySaturation = false;
	minSaturation = 0;
	maxSaturation = 255;

	filterByValue = false;
	minValue = 0;
	maxValue = 255;

	filterByArea = false;
	minArea = 0;
	maxArea = 1e6;

	filterByAspectRatio = false;
	aspectRatio = 1.0;

	filterWithCanny = true;
	minCanny = 0;
	maxCanny = 50;

	filterWithBlur = true;
}

ContourDetector::
ContourDetector(const ContourDetector::Params & parameters):params(parameters)
{
}

std::vector < Contour > ContourDetector::detect(cv::Mat image)
{
	// TODO: Implement detection algorithm
	return std::vector < Contour > ();
}
