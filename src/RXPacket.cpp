#include <vector>
#include <mutex>
#include <string.h>
#include "RXPacket.hpp"
#include <iostream>
RXPacket::RXPacket()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.header = 0x1d3b;
	rx_packet.acc_x = 0;
	rx_packet.acc_y = 0;
	rx_packet.acc_z = 0;
	rx_packet.mag_x = 0;
	rx_packet.mag_y = 0;
	rx_packet.mag_z = 0;
	rx_packet.depth = 0;
	rx_packet.spare = 0;
	rx_packet.checksum = compute_checksum();
	rx_packet_size = sizeof(rx_packet_t);
	is_valid = false;
	std::cout << (int8_t) (get_header() >> 8) << std::endl;
	std::cout << (int8_t) get_header() << std::endl;
}

int16_t RXPacket::get_header()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.header;
}

void RXPacket::set_acc_x(int8_t acc_x)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.acc_x = acc_x;
}

int8_t RXPacket::get_acc_x()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.acc_x;
}

void RXPacket::set_acc_y(int8_t acc_y)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.acc_y = acc_y;
}

int8_t RXPacket::get_acc_y()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.acc_y;
}

void RXPacket::set_acc_z(int8_t acc_z)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.acc_z = acc_z;
}

int8_t RXPacket::get_acc_z()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.acc_z;
}

void RXPacket::set_mag_x(int8_t mag_x)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.mag_x = mag_x;
}

int8_t RXPacket::get_mag_x()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.mag_x;
}

void RXPacket::set_mag_y(int8_t mag_y)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.mag_y = mag_y;
}

int8_t RXPacket::get_mag_y()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.mag_y;
}

void RXPacket::set_mag_z(int8_t mag_z)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.mag_z = mag_z;
}

int8_t RXPacket::get_mag_z()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.mag_z;
}

void RXPacket::set_depth(int8_t depth)
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	rx_packet.depth = depth;
}

int8_t RXPacket::get_depth()
{
	std::lock_guard < std::mutex > rx_packet_lock(rx_packet_mtx);
	return rx_packet.depth;
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

int16_t RXPacket::compute_checksum()
{
	int32_t checksum32 = 0;
	checksum32 += rx_packet.header;
	checksum32 += rx_packet.acc_x;
	checksum32 += rx_packet.acc_y;
	checksum32 += rx_packet.acc_z;
	checksum32 += rx_packet.mag_x;
	checksum32 += rx_packet.mag_y;
	checksum32 += rx_packet.mag_z;
	checksum32 += rx_packet.depth;
	checksum32 += rx_packet.spare;
	int16_t checksum16 = checksum32;
	return checksum16;
}
