/* RPIVideoDevice.cpp -- Implementation of RPIVideoDevice class

   Copyright (C) 2012, 2013, 2014 Tushar Pankaj
   
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

#include <stdlib.h>
#include <iostream>
#include <thread>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include "BaseVideoDevice.hpp"
#include "RPIVideoDevice.hpp"

 RPIVideoDevice::RPIVideoDevice():BaseVideoDevice()
{
	focal_length = (3.6e-3) / (1.4e-6);
}

void RPIVideoDevice::start()
{
	init_camera();
	capture_thread =
	    new std::thread(&RPIVideoDevice::capture_from_camera, this);
}

void RPIVideoDevice::init_camera()
{
	camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	if (!camera.open()) {
		std::cerr << "Unable to open Raspberry Pi camera device." <<
		    std::endl;
		exit(EXIT_FAILURE);
	}
}

void RPIVideoDevice::capture_from_camera()
{
	cv::Mat unflipped;
	while (!is_finished) {
		camera.grab();
		camera.retrieve(unflipped);
		cv::flip(unflipped, image, -1);
		is_ready = true;
	}
}

RPIVideoDevice::~RPIVideoDevice()
{
	is_finished = true;
	capture_thread->join();
	delete capture_thread;
}
