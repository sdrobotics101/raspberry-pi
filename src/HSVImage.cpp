/* HSVImage.cpp -- Implmentation of HSVImage class

   Copyright (C) 2012, 2013, 2014 Tushar Pankaj
   
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

#include <vector>
#include <opencv2/opencv.hpp>
#include "HSVImage.hpp"

HSVImage::HSVImage(cv::Mat & input_image)
{
	load_rgb_image(input_image);
}

void HSVImage::load_rgb_image(cv::Mat & input_image)
{
	input_image.copyTo(rgb);
	cvtColor(input_image, input_image, CV_RGB2HSV);
	std::vector < cv::Mat > slices;
	split(input_image, slices);
	input_image.copyTo(hsv);
	slices.at(0).copyTo(hue);
	slices.at(1).copyTo(saturation);
	slices.at(2).copyTo(value);
}

cv::Mat * HSVImage::get_rgb_mat()
{
	return &rgb;
}

cv::Mat * HSVImage::get_hsv_mat()
{
	return &hsv;
}

cv::Mat * HSVImage::get_hue_mat()
{
	return &hue;
}

cv::Mat * HSVImage::get_saturation_mat()
{
	return &saturation;
}

cv::Mat * HSVImage::get_value_mat()
{
	return &value;
}