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
	std::chrono::milliseconds ramp_itr_time = std::chrono::milliseconds(30);
	std::chrono::milliseconds run_time = std::chrono::milliseconds(5000);

	std::cout << "Moving in +x direction..." << std::flush;
	for (int i = 0; i <= 127; i++) {
		serial.get_tx_packet()->set_vel_x(i);
		std::this_thread::sleep_for(ramp_itr_time);
	}
	std::this_thread::sleep_for(run_time);
	serial.get_tx_packet()->set_vel_x(0);
	std::cout << "done" << std::endl;
	std::cout << "Moving in -x direction..." << std::flush;
	for (int i = 0; i >= -128; i--) {
		serial.get_tx_packet()->set_vel_x(i);
		std::this_thread::sleep_for(ramp_itr_time);
	}
	std::this_thread::sleep_for(run_time);
	serial.get_tx_packet()->set_vel_x(0);
	std::cout << "done" << std::endl;
	std::cout << "Moving in +y direction..." << std::flush;
	for (int i = 0; i <= 127; i++) {
		serial.get_tx_packet()->set_vel_y(i);
		std::this_thread::sleep_for(ramp_itr_time);
	}
	std::this_thread::sleep_for(run_time);
	serial.get_tx_packet()->set_vel_y(0);
	std::cout << "done" << std::endl;
	std::cout << "Moving in -y direction..." << std::flush;
	for (int i = 0; i >= -128; i--) {
		serial.get_tx_packet()->set_vel_y(i);
		std::this_thread::sleep_for(ramp_itr_time);
	}
	std::this_thread::sleep_for(run_time);
	serial.get_tx_packet()->set_vel_y(0);
	std::cout << "done" << std::endl;
	std::cout << "Moving in +z direction..." << std::flush;
	for (int i = 0; i <= 127; i++) {
		serial.get_tx_packet()->set_vel_z(i);
		std::this_thread::sleep_for(ramp_itr_time);
	}
	std::this_thread::sleep_for(run_time);
	serial.get_tx_packet()->set_vel_z(0);
	std::cout << "done" << std::endl;
	std::cout << "Moving in -z direction..." << std::flush;
	for (int i = 0; i >= -128; i--) {
		serial.get_tx_packet()->set_vel_z(i);
		std::this_thread::sleep_for(ramp_itr_time);
	}
	std::this_thread::sleep_for(run_time);
	serial.get_tx_packet()->set_vel_z(0);
	std::cout << "done" << std::endl;
	while (1) ;
}
