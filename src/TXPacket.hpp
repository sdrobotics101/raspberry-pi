/* TXPacket.hpp -- Header file for TXPacket class

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

#ifndef TXPacket_hpp
#define TXPacket_hpp

#include <stdint.h>
#include <mutex>

class TXPacket {
 public:
	TXPacket();
	void set_vel_x(int8_t vel_x);
	int8_t get_vel_x();
	void set_vel_y(int8_t vel_y);
	int8_t get_vel_y();
	void set_vel_z(int8_t vel_z);
	int8_t get_vel_z();
	void set_rot_x(int8_t rot_x);
	int8_t get_rot_x();
	void set_rot_y(int8_t rot_y);
	int8_t get_rot_y();
	void set_rot_z(int8_t rot_z);
	int8_t get_rot_z();
	void set_pos_z(int16_t pos_z);
	int16_t get_pos_z();
	void set_torpedo_ctl(int8_t torpedo_ctl);
	int8_t get_torpedo_ctl();
	void set_servo_ctl(int8_t servo_ctl[]);
	void get_servo_ctl(int8_t servo_ctl[]);
	size_t size();
	bool valid();
	bool read_buffer(unsigned char buffer[]);
	void get_buffer(unsigned char buffer[]);
 private:
	 int16_t compute_checksum();
	typedef struct {
		int16_t header;
		int8_t vel_x;
		int8_t vel_y;
		int8_t vel_z;
		int8_t rot_x;
		int8_t rot_y;
		int8_t rot_z;
		int16_t pos_z;
		int8_t torpedo_ctl;
		int8_t servo_ctl[6];
		int8_t spare;
		int16_t checksum;
	} __attribute__ ((__packed__)) tx_packet_t;
	const int servo_ctl_length = 6;
	tx_packet_t tx_packet;
	 std::mutex tx_packet_mtx;
	size_t tx_packet_size;
	bool is_valid;
};

#endif				// TXPacket_hpp
