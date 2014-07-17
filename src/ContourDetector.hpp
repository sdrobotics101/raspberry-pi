/* ContourDetector.hpp -- Header file for ContourDetector class

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

#ifndef ContourDetector_hpp
#define ContourDetector_hpp

#include <opencv2/opencv.hpp>
#include "Contour.hpp"

class ContourDetector {
 public:
	struct Params {
		Params();

		bool filterByHue;
		int minHue;
		int maxHue;

		bool filterBySaturation;
		int minSaturation;
		int maxSaturation;

		bool filterByValue;
		int minValue;
		int maxValue;

		bool filterByArea;
		int minArea;
		int maxArea;

		bool filterWithCanny;
		int minCanny;
		int maxCanny;

		bool filterWithBlur;

		/*bool filterByShape;
		   enum Shape // Move to Contour.hpp
		   {
		   CIRCLE,
		   RECTANGLE
		   };
		   Shape contourShape; */
	};
	 ContourDetector(const ContourDetector::Params & parameters =
			 ContourDetector::Params());
	Contour detect(cv::Mat image);
 private:
	 Params params;
};

#endif				// ContourDetector_hpp
