/* Robot.hpp -- Header file for Robot class

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

#ifndef Robot_hpp
#define Robot_hpp

#include <string>
#include "Serial.hpp"
#include "Logger.hpp"
#include "BaseVideoDevice.hpp"

class Robot {
 public:
	Robot();
	~Robot();
	void set_period(int new_period);
	void autonomous_mode();
	void teleop_mode();
	BaseVideoDevice *get_forward_camera();
	BaseVideoDevice *get_downward_camera();
	Logger *get_logger();
	Serial *get_serial();
 private:
	void autonomous_init();
	void teleop_init();
	void autonomous_periodic();
	void teleop_periodic();
	Serial serial;
	int period;
	 std::string int_base;
	uint8_t bat_v_threshold;
	BaseVideoDevice *forward_camera;
	BaseVideoDevice *downward_camera;
	Logger logger;
};

#endif				// Robot_hpp
