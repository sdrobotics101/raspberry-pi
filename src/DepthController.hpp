/* DepthController.hpp -- Header file for DepthController class

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

#ifndef DepthController_hpp
#define DepthController_hpp

#include <stdint.h>
#include <thread>
#include "Robot.hpp"

class DepthController {
 public:
	DepthController(Robot * robot_ptr, double p, double i, double d);
	~DepthController();
	void set_depth(double setpoint);
 private:
	void iterate();
	void run();
	Robot *robot;
	std::thread * controller_thread;
	double k_p;
	double k_i;
	double k_d;
	double setpoint;
	double previous_error;
	double integral;
	bool is_running;
};

#endif				// DepthController_hpp
