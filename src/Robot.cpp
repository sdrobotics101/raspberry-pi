/* Robot.cpp -- Implementation of Robot class

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
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
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

void Robot::autonomous_mode()
{
	autonomous_init();
	while (true) {
		autonomous_periodic();
		std::this_thread::sleep_for(std::chrono::milliseconds(period));
	}
}

void Robot::autonomous_init()
{
}

void Robot::autonomous_periodic()
{
}

void Robot::teleop_mode()
{
	teleop_init();
	while (true) {
		teleop_periodic();
		std::this_thread::sleep_for(std::chrono::milliseconds(period));
	}
}

void Robot::teleop_init()
{
	int_base = "dec";
	std::cout << "Cubeception Helm" << std::endl;
	std::cout << "Type \"help\" for help with commands" << std::endl << std::endl;;
}

void Robot::teleop_periodic()
{
	std::cout << "cubeception> ";
	std::string input;
	std::getline(std::cin, input);
	if (input.find(" ") == std::string::npos)
	{
		if (input == "dec") {
			std::cin >> std::dec;
			std::cout << std::dec;
			int_base = "dec";
			std::cout << "Set base to decimal" << std::endl;
		} else if (input == "hex") {
			std::cin >> std::hex;
			std::cout << std::hex;
			int_base = "hex";
			std::cout << "Set base to hex" << std::endl;
		} else if (input == "oct") {
			std::cin >> std::oct;
			std::cout << std::oct;
			int_base = "oct";
			std::cout << "Set base to octal" << std::endl;
		} else if (input == "help") {
			std::cout << "Available commands:" << std::endl;
			std::cout << "Format: COMMAND [DATA TYPE] -- description" << std::endl << std::endl;
			std::cout << " vel_x INT8_T -- set linear velocity along x-axis" << std::endl;
			std::cout << " vel_y INT8_T -- set linear velocity along y-axis" << std::endl;
			std::cout << " vel_z INT8_T -- set linear velocity along z-axis" << std::endl;
			std::cout << "sleep INT32_T -- sleep for given number of milliseconds" << std::endl;
			std::cout << "          dec -- set integer base to decimal" << std::endl;
			std::cout << "          hex -- set integer base to hex" << std::endl;
			std::cout << "          oct -- set integer base to octal" << std::endl;
			std::cout << "         help -- show this help" << std::endl;
		} else
			std::cout << input << ": command not found" << std::endl;
	}
	else
	{
		std::string key;
		int value;
		if (int_base == "dec")
			std::istringstream(input) >> key >> value;
		else if (int_base == "hex")
			std::istringstream(input) >> std::hex >> key >> value;
		else if (int_base == "oct")
			std::istringstream(input) >> std::oct >> key >> value;			
		int8_t value8 = (int8_t) value;
		if (key == "vel_x") {
			serial.get_tx_packet()->set_vel_x(value8);
			std::cout << "Set vel_x = " << value << std::endl;
		} else if (key == "vel_y") {
			serial.get_tx_packet()->set_vel_y(value8);
			std::cout << "Set vel_y = " << value << std::endl;
		} else if (key == "vel_z") {
			serial.get_tx_packet()->set_vel_z(value8);
			std::cout << "Set vel_z = " << value << std::endl;
		} else if (key == "sleep") {
			std::cout << "Sleeping for " << value << " ms" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(value));
		} else
			std::cout << key << ": command not found" << std::endl;
	}
}
