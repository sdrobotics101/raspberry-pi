/* TXPacket.cpp -- Implementation of TXPacket class

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

#include <mutex>
#include <bitset>
#include <string.h>
#include "TXPacket.hpp"

TXPacket::TXPacket()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet_size = sizeof(tx_packet_t);
	tx_packet.header = 0xbdfa;
	tx_packet.vel_x = 0;
	tx_packet.vel_y = 0;
	tx_packet.vel_z = 0;
	tx_packet.rot_z = 0;
	tx_packet.torpedo_ctl = 0;
	tx_packet.servo_ctl = 0;
	tx_packet.led_ctl = 0;
	tx_packet.mode = 0xf1;
	tx_packet.checksum = compute_checksum();
	is_valid = false;
}

uint16_t TXPacket::get_header()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return tx_packet.header;
}

void TXPacket::set_vel_x(int8_t vel_x)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.vel_x = vel_x;
}

int8_t TXPacket::get_vel_x()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return tx_packet.vel_x;
}

void TXPacket::set_vel_y(int8_t vel_y)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.vel_y = vel_y;
}

int8_t TXPacket::get_vel_y()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return tx_packet.vel_y;
}

void TXPacket::set_vel_z(int8_t vel_z)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.vel_z = vel_z;
}

int8_t TXPacket::get_vel_z()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return tx_packet.vel_z;
}

void TXPacket::set_rot_z(int8_t rot_z)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.rot_z = rot_z;
}

int8_t TXPacket::get_rot_z()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return tx_packet.rot_z;
}

void TXPacket::set_torpedo_ctl(std::bitset < 8 > torpedo_ctl)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.torpedo_ctl = torpedo_ctl.to_ulong();
}

std::bitset < 8 > TXPacket::get_torpedo_ctl()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return std::bitset < 8 > (tx_packet.torpedo_ctl);
}

void TXPacket::set_servo_ctl(std::bitset < 8 > servo_ctl)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.servo_ctl = servo_ctl.to_ulong();
}

std::bitset < 8 > TXPacket::get_servo_ctl()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return std::bitset < 8 > (tx_packet.servo_ctl);
}

void TXPacket::set_led_ctl(std::bitset < 8 > led_ctl)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.led_ctl = led_ctl.to_ulong();
}

std::bitset < 8 > TXPacket::get_led_ctl()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return std::bitset < 8 > (tx_packet.led_ctl);
}

void TXPacket::set_mode(std::bitset < 16 > mode)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.mode = mode.to_ulong();
}

std::bitset < 16 > TXPacket::get_mode()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return std::bitset < 16 > (tx_packet.mode);
}

size_t TXPacket::size()
{
	return tx_packet_size;
}

bool TXPacket::valid()
{
	return is_valid;
}

bool TXPacket::read_buffer(unsigned char buffer[])
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet_t old_tx_packet = tx_packet;
	memcpy(&tx_packet, buffer, tx_packet_size);
	if (tx_packet.checksum != compute_checksum()) {
		tx_packet = old_tx_packet;
		is_valid = false;
		return false;
	}
	is_valid = true;
	return true;
}

void TXPacket::get_buffer(unsigned char buffer[])
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.checksum = compute_checksum();
	memcpy(buffer, &tx_packet, tx_packet_size);
}

uint16_t TXPacket::compute_checksum()
{
	uint16_t checksum = 0;
	unsigned char buffer[tx_packet_size];
	memcpy(buffer, &tx_packet, tx_packet_size);
	for (unsigned char *buffer_ptr = buffer;
	     buffer_ptr <
	     buffer + tx_packet_size -
	     sizeof(tx_packet.checksum) /* skip checksum */ ; buffer_ptr++)
		checksum += *buffer_ptr;
	return checksum;
}
