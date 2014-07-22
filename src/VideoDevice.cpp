/* VideoDevice.cpp -- Implementation of VideoDevice class

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

#include <cstdlib>
#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "VideoDevice.hpp"

VideoDevice::VideoDevice()
{
	is_finished = false;
	is_ready = false;
}

void VideoDevice::start_capture(int device_id)
{
	init_camera(device_id);
	capture_thread =
	    new std::thread(&VideoDevice::capture_from_camera, this);
}

cv::Mat VideoDevice::get_image()
{
	while (!is_ready) ;
	return image;
}

void VideoDevice::init_camera(int device_id)
{
	camera.open(device_id);
	if (!camera.isOpened()) {
		std::cerr << "Unable to open capture device /dev/video" <<
		    device_id << std::endl;
		exit(EXIT_FAILURE);
	}
}

void VideoDevice::capture_from_camera()
{
	while (!is_finished) {
		camera >> image;
		is_ready = true;
	}
}

VideoDevice::~VideoDevice()
{
	is_finished = true;
	capture_thread->join();
	delete capture_thread;
}
