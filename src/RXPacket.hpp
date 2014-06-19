/* RXPacket.hpp -- Header file for RXPacket class

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

#ifndef RXPacket_hpp
#define RXPacket_hpp

#include <stdint.h>
#include <mutex>

class RXPacket {
 public:
	RXPacket();
	int16_t get_header();
	void set_acc_x(int8_t acc_x);
	int8_t get_acc_x();
	void set_acc_y(int8_t acc_y);
	int8_t get_acc_y();
	void set_acc_z(int8_t acc_z);
	int8_t get_acc_z();
	void set_mag_x(int8_t mag_x);
	int8_t get_mag_x();
	void set_mag_y(int8_t mag_y);
	int8_t get_mag_y();
	void set_mag_z(int8_t mag_z);
	int8_t get_mag_z();
	void set_depth(int8_t depth);
	int8_t get_depth();
	size_t size();
	bool valid();
	bool read_buffer(unsigned char buffer[]);
	void get_buffer(unsigned char buffer[]);
 private:
	 int16_t compute_checksum();
	typedef struct {
		int16_t header;
		int8_t acc_x;
		int8_t acc_y;
		int8_t acc_z;
		int8_t mag_x;
		int8_t mag_y;
		int8_t mag_z;
		int8_t depth;
		int8_t spare;
		int16_t checksum;
	} __attribute__ ((__packed__)) rx_packet_t;
	rx_packet_t rx_packet;
	 std::mutex rx_packet_mtx;
	size_t rx_packet_size;
	bool is_valid;
};

#endif				// RXPacket_hpp
