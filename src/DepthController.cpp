/* DepthController.cpp -- Implementation of DepthController class

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

#include <iostream>
#include "DepthController.hpp"

DepthController::DepthController(Robot *robot_ptr, double p, double i, double d)
{
	robot = robot_ptr;
	k_p = p;
	k_i = i;
	k_d = d;
	setpoint = 0;
	previous_error = 0;
	integral = 0.0;
	is_running = true;
	controller_thread = new std::thread(&DepthController::run, this);
}

DepthController::~DepthController()
{
	is_running = false;
	controller_thread->join();
	delete controller_thread;
}

void DepthController::iterate()
{
	double error = setpoint - robot->get_serial()->get_rx_packet()->get_pos_z();
	integral += error;
	double derivative = error - previous_error;
	previous_error = error;
	int output = (int)(k_p * error + k_i * integral + k_d * derivative);
	int8_t output8;
	if (output > 127)
		output8 = 127;
	else if (output < -127)
		output8 = -127;
	else
		output8 = (int8_t)output;
	robot->get_serial()->get_rx_packet()->set_pos_z(output8);
}

void DepthController::run()
{
	while (is_running)
		iterate();
}

void DepthController::set_depth(double input_setpoint)
{
	setpoint = input_setpoint;
}
