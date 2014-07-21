/* Robot.cpp -- Implementation of Robot class

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

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "Robot.hpp"
#include "Serial.hpp"
#include "TXPacket.hpp"

Robot::Robot()
{
	period = 10;
	serial.open_serial();
	serial.start();
}

void Robot::set_period(int new_period)
{
	period = new_period;
}

void Robot::autonomous_init()
{
	while (true) {
		autonomous_periodic();
		std::this_thread::sleep_for(std::chrono::milliseconds(period));
	}
}

void Robot::autonomous_periodic()
{
}

void Robot::teleop_init()
{
	while (true) {
		teleop_periodic();
		std::this_thread::sleep_for(std::chrono::milliseconds(period));
	}
}

void Robot::teleop_periodic()
{
	std::cout << "cubeception> ";
	std::string key;
	int value;
	std::cin >> key >> value;
	int8_t value8 = (int8_t) value;
	if (key == "vel_x") {
		serial.get_tx_packet()->set_vel_x(value8);
		std::cout << "Setting vel_x =" << value << std::endl;
	} else if (key == "vel_y") {
		serial.get_tx_packet()->set_vel_y(value8);
		std::cout << "Setting vel_y = " << value << std::endl;
	} else if (key == "vel_z") {
		serial.get_tx_packet()->set_vel_z(value8);
		std::cout << "Setting vel_z = " << value << std::endl;
	} else if (key == "sleep") {
		std::cout << "Sleeping for " << value << " ms" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(value));
	} else
		std::cout << key << ": command not found" << std::endl;
}
