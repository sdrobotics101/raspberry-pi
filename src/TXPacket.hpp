/* TXPacket.hpp -- Header file for TXPacket class

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

#ifndef TXPacket_hpp
#define TXPacket_hpp

#include <stdint.h>
#include <mutex>
#include <bitset>

class TXPacket {
 public:
	TXPacket();
	uint16_t get_header();
	void set_vel_x(int8_t vel_x);
	int8_t get_vel_x();
	void set_vel_y(int8_t vel_y);
	int8_t get_vel_y();
	void set_vel_z(int8_t vel_z);
	int8_t get_vel_z();
	void set_rot_z(int8_t rot_z);
	int8_t get_rot_z();
	void set_torpedo_ctl(std::bitset<8> torpedo_ctl);
	std::bitset<8> get_torpedo_ctl();
	void set_servo_ctl(std::bitset<8> servo_ctl);
	std::bitset<8> get_servo_ctl();
	void set_led_ctl(std::bitset<8> led_ctl);
	std::bitset<8> get_led_ctl();
	void set_mode(std::bitset<16> mode);
	std::bitset<16> get_mode();
	size_t size();
	bool valid();
	bool read_buffer(unsigned char buffer[]);
	void get_buffer(unsigned char buffer[]);
 private:
	 uint16_t compute_checksum();
	typedef struct {
		uint16_t header;
		int8_t vel_x;
		int8_t vel_y;
		int8_t vel_z;
		int8_t rot_z;
		uint8_t torpedo_ctl;
		uint8_t servo_ctl;
		uint8_t led_ctl;
		uint16_t mode;
		uint16_t checksum;
	} __attribute__ ((__packed__)) tx_packet_t;
	tx_packet_t tx_packet;
	 std::mutex tx_packet_mtx;
	size_t tx_packet_size;
	bool is_valid;
};

#endif				// TXPacket_hpp
