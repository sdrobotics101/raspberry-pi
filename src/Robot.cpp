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
#include <iomanip>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <bitset>
#include "Robot.hpp"
#include "Serial.hpp"
#include "TXPacket.hpp"
#include "Logger.hpp"
#include "BaseVideoDevice.hpp"
#include "USBVideoDevice.hpp"
#ifdef RPI_COMPILE
#include "RPIVideoDevice.hpp"
#include <wiringPi.h>
#endif
#include "StartingGateMission.hpp"

 Robot::Robot():logger("/tmp/rpi_log/rpi_log.log", Logger::DEBUG)
{
	logger.write("Initializing robot", Logger::MESSAGE);
	period = 10;
	logger.write("Initialized Robot.period to " + std::to_string(period),
		     Logger::MESSAGE);
	bat_v_threshold = 6.0;
	logger.write("Initialized Robot.bat_v_threshold to " +
		     std::to_string(bat_v_threshold), Logger::MESSAGE);
	hreset_pin = 4;
	logger.write("Initialized Robot.hreset_pin to " +
		     std::to_string(hreset_pin), Logger::MESSAGE);
#ifdef RPI_COMPILE
	logger.write("Starting serial driver", Logger::MESSAGE);
	serial.open_serial();
	serial.start();
	logger.write("Finished starting serial driver", Logger::MESSAGE);
#endif
#ifdef RPI_COMPILE
	logger.write("Initializing forward camera as RPIVideoDevice",
		     Logger::MESSAGE);
	//forward_camera = new RPIVideoDevice();
	logger.write("Finished initializing forward camera as RPIVideoDevice",
		     Logger::MESSAGE);
#else
	logger.write("Initializing forward camera as USBVideoDevice(1)",
		     Logger::MESSAGE);
	//forward_camera = new USBVideoDevice(1);
	logger.write
	    ("Finished initializing forward camera as USBVideoDevice(1)",
	     Logger::MESSAGE);
#endif
	logger.write("Initializing downward camera as USBVideoDevice(0)",
		     Logger::MESSAGE);
	//downward_camera = new USBVideoDevice(0);
	logger.write
	    ("Finished initializing downward camera as USBVideoDevice(0)",
	     Logger::MESSAGE);
	logger.write("Starting forward camera", Logger::MESSAGE);
	//forward_camera->start();
	logger.write("Finished starting forward camera", Logger::MESSAGE);
	logger.write("Starting downward camera", Logger::MESSAGE);
	//downward_camera->start();
	logger.write("Finished starting downward camera", Logger::MESSAGE);
	logger.write("Finished initializing robot", Logger::MESSAGE);
#ifdef RPI_COMPILE
	wiringPiSetup();
	pinMode(hreset_pin, OUTPUT);
	digitalWrite(hreset_pin, HIGH);
#endif
}

Robot::~Robot()
{
	//delete forward_camera;
	//delete downward_camera;
}

void Robot::set_period(int new_period)
{
	period = new_period;
	logger.write("Robot.period changed to" + std::to_string(period),
		     Logger::MESSAGE);
}

void Robot::autonomous_mode()
{
	logger.write("Running autonomous_init()", Logger::MESSAGE);
	autonomous_init();
	logger.write("Running autonomous_periodic()", Logger::MESSAGE);
	while (true) {
		autonomous_periodic();
		std::this_thread::sleep_for(std::chrono::milliseconds(period));
	}
}

void Robot::autonomous_init()
{
	StartingGateMission starting_gate_mission = StartingGateMission(this);
	starting_gate_mission.run();
}

void Robot::autonomous_periodic()
{
}

void Robot::teleop_mode()
{
	logger.write("Running teleop_init()", Logger::MESSAGE);
	teleop_init();
	logger.write("Running teleop_periodic()", Logger::MESSAGE);
	while (true) {
		teleop_periodic();
		std::this_thread::sleep_for(std::chrono::milliseconds(period));
	}
}

void Robot::teleop_init()
{
	int_base = "dec";
	std::cout << "Cubeception Helm" << std::endl;
	std::cout << "Type \"help\" for help with commands" << std::
	    endl << std::endl;
}

void Robot::teleop_periodic()
{
	if (serial.get_rx_packet()->get_bat_v() < bat_v_threshold)
		std::cout << std::
		    endl << "WARNING: LOW BATTERY VOLTAGE" << std::endl;
	std::cout << "cubeception> ";
	std::string input;
	std::getline(std::cin, input);
	logger.write("Interpreter input: " + input, Logger::VERBOSE);
	if (input.find(" ") == std::string::npos) {
		if (input == "mag_x")
			std::cout << "mag_x = " << (int)serial.get_rx_packet()->
			    get_mag_x() << std::endl;
		else if (input == "mag_y")
			std::cout << "mag_y = " << (int)serial.get_rx_packet()->
			    get_mag_y() << std::endl;
		else if (input == "mag_z")
			std::cout << "mag_z = " << (int)serial.get_rx_packet()->
			    get_mag_z() << std::endl;
		else if (input == "pos_z")
			std::cout << "pos_z = " << (int)serial.get_rx_packet()->
			    get_pos_z() << std::endl;
		else if (input == "health")
			std::
			    cout << "health = " << (int)serial.get_rx_packet()->
			    get_health() << std::endl;
		else if (input == "bat_v")
			std::cout << "bat_v = " << serial.get_rx_packet()->
			    get_bat_v() << std::endl;
		else if (input == "sreset") {
			std::bitset < 16 > mode;
			mode[15] = 1;
			serial.get_tx_packet()->set_mode(std::bitset < 16 >(0x80f1));
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			serial.get_tx_packet()->set_mode(std::bitset < 16 >(0x00f1));
			std::cout << "Soft reset Arduino control loops" << std::endl;
		} else if (input == "hreset") {
			hreset_arduino();
			std::cout << "Hard reset Arduino" << std::endl;
		} else if (input == "kill") {
			serial.get_tx_packet()->set_mode(std::bitset < 16 >
							 (0x40f1));
			std::cout << "Set mode = " << serial.
			    get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (input == "notest") {
			serial.get_tx_packet()->set_mode(std::bitset<16>(0x00f1));
			hreset_arduino();
			std::cout << "Set mode = " << serial.
				get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (input == "motor") {
			serial.get_tx_packet()->set_mode(std::bitset<16>(0x10f1));
			std::cout << "Set mode = " << serial.
				get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (input == "imu") {
			serial.get_tx_packet()->set_mode(std::bitset<16>(0x20f1));
			std::cout << "Set mode = " << serial.
				get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (input == "pressure") {
			serial.get_tx_packet()->set_mode(std::bitset<16>(0x30f1));
			std::cout << "Set mode = " << serial.
				get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (input == "dec") {
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
			std::cout << "Available commands:" << std::endl << std::
			    endl;
			std::cout << std::right << std::
			    setw(14) << "vel_x  " << std::left << std::
			    setw(8) << "INT8" << std::
			    setw(0) << "set linear velocity along x-axis" <<
			    std::endl;
			std::cout << std::right << std::
			    setw(14) << "vel_y  " << std::left << std::
			    setw(8) << "INT8" << std::
			    setw(0) << "set linear velocity along y-axis" <<
			    std::endl;
			std::cout << std::right << std::
			    setw(14) << "vel_z  " << std::left << std::
			    setw(8) << "INT8" << std::
			    setw(0) << "set linear velocity along z-axis" <<
			    std::endl;
			std::cout << std::right << std::
			    setw(14) << "rot_z  " << std::left << std::
			    setw(8) << "INT8" << std::
			    setw(0) <<
			    "set relative angular position about z-axis" <<
			    std::endl;
			std::cout << std::right << std::
			    setw(14) << "torpedo_ctl  " << std::left << std::
			    setw(8) << "UINT8" << std::
			    setw(0) << "set torpedo control byte" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "servo_ctl  " << std::left << std::
			    setw(8) << "UINT8" << std::
			    setw(0) << "set servo control byte" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "led_ctl  " << std::left << std::
			    setw(8) << "UINT8" << std::
			    setw(0) << "set led control byte" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "mode  " << std::left << std::
			    setw(8) << "UINT16" << std::
			    setw(0) << "set mode bytes" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "lin  " << std::left << std::
			    setw(8) << "UINT16" << std::
			    setw(0) << "set linear loop control" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "rot  " << std::left << std::
			    setw(8) << "UINT8" << std::
			    setw(0) << "set rotational loop control" << std::
			    endl;
			std::cout << std::right << std::
			    setw(14) << "dep  " << std::left << std::
			    setw(8) << "UINT8" << std::
			    setw(0) << "set depth loop control" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "stb  " << std::left << std::
			    setw(8) << "UINT8" << std::
			    setw(0) << "set stabilization loop control" << std::
			    endl;
			std::cout << std::right << std::
			    setw(14) << "norm  " << std::left << std::
			    setw(8) << "UINT8" << std::
			    setw(0) << "set normal mode bit" << std::
			    endl;
			std::cout << std::right << std::
			    setw(14) << "cal  " << std::left << std::
			    setw(8) << "UINT8" << std::
			    setw(0) << "set calibration mode bit" << std::
			    endl;
			std::cout << std::right << std::
			    setw(14) << "loops  " << std::left << std::
			    setw(8) << "UINT8" << std::
			    setw(0) << "set loop state" << std::
			    endl;
			std::cout << std::right << std::
			    setw(14) << "cs  " << std::left << std::
			    setw(8) << "UINT8" << std::
			    setw(0) << "set pid coefficients" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "sleep  " << std::left << std::
			    setw(8) << "UINT32" << std::
			    setw(0) << "sleep for given number of milliseconds"
			    << std::endl;
			std::cout << std::right << std::
			    setw(14) << "mag_x  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "get magnetometer x-axis value" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "mag_y  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "get magnetometer y-axis value" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "mag_z  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "get magnetometer z-axis value" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "pos_z  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "get position along z-axis" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "health  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "get arduino health metric" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "bat_v  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "get battery voltage" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "kill  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "kill all motors" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "sreset  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "soft reset arduino control loops" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "hreset  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "hard reset arduino" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "notest  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "leave testing mode" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "motor  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "run motor test" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "pressure  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "run pressure sensor test" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "imu  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "run imu test" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "dec  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "set integer base to decimal" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "hex  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "set integer base to hex" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "oct  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "set integer base to octal" << std::endl;
			std::cout << std::right << std::
			    setw(14) << "help  " << std::left << std::
			    setw(8) << "        " << std::setw(0)
			    << "show this help" << std::endl;
		} else
			std::cout << input << ": command not found" << std::
			    endl;
	} else {
		std::string key;
		int value;
		if (int_base == "dec")
			std::istringstream(input) >> key >> value;
		else if (int_base == "hex")
			std::istringstream(input) >> std::hex >> key >> value;
		else if (int_base == "oct")
			std::istringstream(input) >> std::oct >> key >> value;
		if (key == "vel_x") {
			serial.get_tx_packet()->set_vel_x(value);
			std::cout << "Set vel_x = " << value << std::endl;
		} else if (key == "vel_y") {
			serial.get_tx_packet()->set_vel_y(value);
			std::cout << "Set vel_y = " << value << std::endl;
		} else if (key == "vel_z") {
			serial.get_tx_packet()->set_vel_z(value);
			std::cout << "Set vel_z = " << value << std::endl;
		} else if (key == "rot_z") {
			serial.get_tx_packet()->set_rot_z(value);
			std::cout << "Set rot_z = " << value << std::endl;
		} else if (key == "torpedo_ctl") {
			serial.get_tx_packet()->set_torpedo_ctl(std::bitset <
								8 > ((uint8_t)
								     value));
			std::cout << "Set torpedo_ctl = " << value << std::endl;
		} else if (key == "servo_ctl") {
			serial.get_tx_packet()->set_servo_ctl(std::bitset < 8 >
							      ((uint8_t)
							       value));
			std::cout << "Set servo_ctl = " << value << std::endl;
		} else if (key == "led_ctl") {
			serial.get_tx_packet()->set_led_ctl(std::bitset < 8 >
							    ((uint8_t) value));
			std::cout << "Set led_ctl = " << value << std::endl;
		} else if (key == "mode") {
			serial.get_tx_packet()->set_mode(std::bitset < 16 >
							 ((uint16_t) value));
			std::cout << "Set mode = " << value << std::endl;
		} else if (key == "cs") {
			std::bitset < 8 > cs_command((uint8_t) value);
			std::bitset < 16 > mode =
			    serial.get_tx_packet()->get_mode();
			mode[11] = cs_command[3];
			mode[10] = cs_command[2];
			mode[9] = cs_command[1];
			mode[8] = cs_command[0];
			serial.get_tx_packet()->set_mode(mode);
			std::cout << "Set mode = " << serial.
			    get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (key == "lin") {
			std::bitset < 8 > lin_command((uint8_t) value);
			std::bitset < 16 > mode =
			    serial.get_tx_packet()->get_mode();
			mode[7] = lin_command[0];
			serial.get_tx_packet()->set_mode(mode);
			std::cout << "Set mode = " << serial.
			    get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (key == "rot") {
			std::bitset < 8 > rot_command((uint8_t) value);
			std::bitset < 16 > mode =
			    serial.get_tx_packet()->get_mode();
			mode[6] = rot_command[0];
			serial.get_tx_packet()->set_mode(mode);
			std::cout << "Set mode = " << serial.
			    get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (key == "dep") {
			std::bitset < 8 > dep_command((uint8_t) value);
			std::bitset < 16 > mode =
			    serial.get_tx_packet()->get_mode();
			mode[5] = dep_command[0];
			serial.get_tx_packet()->set_mode(mode);
			std::cout << "Set mode = " << serial.
			    get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (key == "stb") {
			std::bitset < 8 > stb_command((uint8_t) value);
			std::bitset < 16 > mode =
			    serial.get_tx_packet()->get_mode();
			mode[4] = stb_command[0];
			serial.get_tx_packet()->set_mode(mode);
			std::cout << "Set mode = " << serial.
			    get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (key == "norm") {
			std::bitset < 8 > norm_command((uint8_t) value);
			std::bitset < 16 > mode =
			    serial.get_tx_packet()->get_mode();
			mode[2] = norm_command[0];
			serial.get_tx_packet()->set_mode(mode);
			std::cout << "Set mode = " << serial.
			    get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (key == "loops") {
			std::bitset < 8 > loops_command((uint8_t) value);
			std::bitset < 16 > mode =
				serial.get_tx_packet()->get_mode();
			if (loops_command[0] == 0)
			{
				serial.get_tx_packet()->set_mode(std::bitset<16>(0x00f1));
				std::cout << "Set mode = " << serial.
					get_tx_packet()->get_mode().to_ulong() << std::endl;
			}
			else
			{
				mode[7] = 0;
				mode[6] = 0;
				mode[5] = 0;
				mode[4] = 0;
				mode[2] = 1;
				serial.get_tx_packet()->set_mode(mode);
				std::cout << "Set mode = " << serial.
					get_tx_packet()->get_mode().to_ulong() << std::endl;
			}
		} else if (key == "cal") {
			std::bitset < 8 > cal_command((uint8_t) value);
			std::bitset < 16 > mode =
				serial.get_tx_packet()->get_mode();
			mode[3] = cal_command[0];
			serial.get_tx_packet()->set_mode(mode);
			std::cout << "Set mode = " << serial.
				get_tx_packet()->get_mode().to_ulong() << std::endl;
		} else if (key == "sleep") {
			std::cout << "Sleeping for " << value << " ms" <<
			    std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds
						    (value));
		} else
			std::cout << key << ": command not found" << std::endl;
	}
}

BaseVideoDevice *Robot::get_forward_camera()
{
	return forward_camera;
}

BaseVideoDevice *Robot::get_downward_camera()
{
	return downward_camera;
}

Logger *Robot::get_logger()
{
	return &logger;
}

Serial *Robot::get_serial()
{
	return &serial;
}

void Robot::hreset_arduino()
{
#ifdef RPI_COMPILE
	digitalWrite(hreset_pin, LOW);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	digitalWrite(hreset_pin, HIGH);
#endif
}
