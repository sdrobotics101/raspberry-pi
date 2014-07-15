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
#include "Robot.hpp"
#include "Serial.hpp"
#include "TXPacket.hpp"

void Robot::start()
{
	serial.open_serial();
	serial.start();
	std::cout << "Moving forward at full speed...";
	serial.get_tx_packet()->set_vel_x(127);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "done" << std::endl;
	std::cout << "Moving backward at full speed...";
	serial.get_tx_packet()->set_vel_x(-127);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	serial.get_tx_packet()->set_vel_x(0);
	std::cout << "done" << std::endl;
	std::cout << "Moving left at full speed...";
	serial.get_tx_packet()->set_vel_y(127);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "done" << std::endl;
	std::cout << "Moving right at full speed...";
	serial.get_tx_packet()->set_vel_y(-127);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	serial.get_tx_packet()->set_vel_y(0);
	std::cout << "done" << std::endl;
	std::cout << "Moving up at full speed...";
	serial.get_tx_packet()->set_vel_z(127);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "done" << std::endl;
	std::cout << "Moving down at full speed...";
	serial.get_tx_packet()->set_vel_z(-127);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	serial.get_tx_packet()->set_vel_z(0);
	std::cout << "done" << std::endl;
}
