/* RXPacket.cpp -- Implementation of RXPacket class

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

#include <vector>
#include <mutex>
#include <string.h>
#include "RXPacket.hpp"
#include <iostream>
RXPacket::RXPacket()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet_size = sizeof(rx_packet_t);
	rx_packet.header = 0x1d3b;
	rx_packet.mag_x = 0;
	rx_packet.mag_y = 0;
	rx_packet.mag_z = 0;
	rx_packet.pos_z = 0;
	rx_packet.health = 0;
	rx_packet.bat_v = 0;
	rx_packet.checksum = compute_checksum();
	is_valid = false;
	bat_v_slope = 0.086202597521733371;
	bat_v_intercept = 0.13758753478973684;
}

uint16_t RXPacket::get_header()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.header;
}

void RXPacket::set_mag_x(int16_t mag_x)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.mag_x = mag_x;
}

int16_t RXPacket::get_mag_x()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.mag_x;
}

void RXPacket::set_mag_y(int16_t mag_y)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.mag_y = mag_y;
}

int16_t RXPacket::get_mag_y()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.mag_y;
}

void RXPacket::set_mag_z(int16_t mag_z)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.mag_z = mag_z;
}

int16_t RXPacket::get_mag_z()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.mag_z;
}

void RXPacket::set_pos_z(uint16_t pos_z)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.pos_z = pos_z;
}

uint16_t RXPacket::get_pos_z()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.pos_z;
}

void RXPacket::set_health(uint16_t health)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.health = health;
}

uint16_t RXPacket::get_health()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.health;
}

void RXPacket::set_bat_v(uint8_t bat_v)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.bat_v = bat_v;
}

double RXPacket::get_bat_v()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return bat_v_slope * (double)rx_packet.bat_v + bat_v_intercept;
}

size_t RXPacket::size()
{
	return rx_packet_size;
}

bool RXPacket::valid()
{
	return is_valid;
}

bool RXPacket::read_buffer(unsigned char buffer[])
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet_t old_rx_packet = rx_packet;
	memcpy(&rx_packet, buffer, rx_packet_size);
	if (rx_packet.checksum != compute_checksum()) {
		rx_packet = old_rx_packet;
		is_valid = false;
		return false;
	}
	is_valid = true;
	return true;
}

void RXPacket::get_buffer(unsigned char buffer[])
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.checksum = compute_checksum();
	memcpy(buffer, &rx_packet, rx_packet_size);
}

uint16_t RXPacket::compute_checksum()
{
	uint16_t checksum = 0;
	unsigned char buffer[rx_packet_size];
	memcpy(buffer, &rx_packet, rx_packet_size);
	for (unsigned char *buffer_ptr = buffer;
	     buffer_ptr <
	     buffer + rx_packet_size -
	     sizeof(rx_packet.checksum) /* skip checksum */ ; buffer_ptr++)
		checksum += *buffer_ptr;
	return checksum;
}
