/* RPIVideoDevice.hpp -- Header file for RPIVideoDevice class

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

#ifndef RPIVideoDevice_hpp
#define RPIVideoDevice_hpp

#include <thread>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include "BaseVideoDevice.hpp"

class RPIVideoDevice:public BaseVideoDevice {
 public:
	RPIVideoDevice();
	virtual void start();
	 virtual ~ RPIVideoDevice();
 protected:
	 virtual void init_camera();
	virtual void capture_from_camera();
	 raspicam::RaspiCam_Cv camera;
};

#endif				// RPIVideoDevice_hpp
