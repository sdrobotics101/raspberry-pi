#include <vector>
#include <mutex>
#include <string.h>
#include "RXPacket.hpp"

RXPacket::RXPacket()
{
	rx_packet_size = sizeof(rx_packet_t);
}

void RXPacket::set_acc_x(int8_t acc_x)
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	rx_packet.acc_x = acc_x;
}

int8_t RXPacket::get_acc_x()
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	return rx_packet.acc_x;
}

void RXPacket::set_acc_y(int8_t acc_y)
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	rx_packet.acc_y = acc_y;
}

int8_t RXPacket::get_acc_y()
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	return rx_packet.acc_y;
}

void RXPacket::set_acc_z(int8_t acc_z)
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	rx_packet.acc_z = acc_z;
}

int8_t RXPacket::get_acc_z()
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	return rx_packet.acc_z;
}

void RXPacket::set_mag_x(int8_t mag_x)
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	rx_packet.mag_x = mag_x;
}

int8_t RXPacket::get_mag_x()
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	return rx_packet.mag_x;
}

void RXPacket::set_mag_y(int8_t mag_y)
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	rx_packet.mag_y = mag_y;
}

int8_t RXPacket::get_mag_y()
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	return rx_packet.mag_y;
}

void RXPacket::set_mag_z(int8_t mag_z)
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	rx_packet.mag_z = mag_z;
}

int8_t RXPacket::get_mag_z()
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	return rx_packet.mag_z;
}

void RXPacket::set_depth(int8_t depth)
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	rx_packet.depth = depth;
}

int8_t RXPacket::get_depth()
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	return rx_packet.depth;
}

size_t RXPacket::size()
{
	return rx_packet_size;
}

void RXPacket::read_buffer(unsigned char buffer[])
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	memcpy(&rx_packet, buffer, rx_packet_size);
}

void RXPacket::get_buffer(unsigned char buffer[])
{
	std::lock_guard<std::mutex> rx_packet_lock(rx_packet_mtx);
	memcpy(buffer, &rx_packet, rx_packet_size);
}
