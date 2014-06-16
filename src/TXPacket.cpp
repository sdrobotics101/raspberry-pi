#include <mutex>
#include <string.h>
#include "TXPacket.hpp"

TXPacket::TXPacket()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.header = 0;
	tx_packet.vel_x = 0;
	tx_packet.vel_y = 0;
	tx_packet.vel_z = 0;
	tx_packet.rot_x = 0;
	tx_packet.rot_y = 0;
	tx_packet.rot_z = 0;
	tx_packet.pos_z = 0;
	tx_packet.torpedo_ctl = 0;
	for (int i = 0; i < servo_ctl_length; i++)
		tx_packet.servo_ctl[i] = 0;
	tx_packet.spare = 0;
	tx_packet.checksum = compute_checksum();
	tx_packet_size = sizeof(tx_packet_t);
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

void TXPacket::set_rot_x(int8_t rot_x)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.rot_x = rot_x;
}

int8_t TXPacket::get_rot_x()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return tx_packet.rot_x;
}

void TXPacket::set_rot_y(int8_t rot_y)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.rot_y = rot_y;
}

int8_t TXPacket::get_rot_y()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return tx_packet.rot_y;
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

void TXPacket::set_pos_z(int16_t pos_z)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.pos_z = pos_z;
}

int16_t TXPacket::get_pos_z()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return tx_packet.pos_z;
}

void TXPacket::set_torpedo_ctl(int8_t torpedo_ctl)
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.torpedo_ctl = torpedo_ctl;
}

int8_t TXPacket::get_torpedo_ctl()
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	return tx_packet.torpedo_ctl;
}

void TXPacket::set_servo_ctl(int8_t servo_ctl[])
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	memcpy(&tx_packet.servo_ctl, servo_ctl, sizeof(tx_packet.servo_ctl));
}

void TXPacket::get_servo_ctl(int8_t servo_ctl[])
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	memcpy(&servo_ctl, tx_packet.servo_ctl, sizeof(servo_ctl));
}

size_t TXPacket::size()
{
	return tx_packet_size;
}

bool TXPacket::read_buffer(unsigned char buffer[])
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet_t old_tx_packet = tx_packet;
	memcpy(&tx_packet, buffer, tx_packet_size);
	if (tx_packet.checksum != compute_checksum()) {
		tx_packet = old_tx_packet;
		return false;
	}
	return true;
}

void TXPacket::get_buffer(unsigned char buffer[])
{
	std::lock_guard < std::mutex > tx_packet_lock(tx_packet_mtx);
	tx_packet.checksum = compute_checksum();
	memcpy(buffer, &tx_packet, tx_packet_size);
}

int16_t TXPacket::compute_checksum()
{
	int32_t checksum32 = 0;
	checksum32 += tx_packet.header;
	checksum32 += tx_packet.vel_x;
	checksum32 += tx_packet.vel_y;
	checksum32 += tx_packet.vel_z;
	checksum32 += tx_packet.rot_x;
	checksum32 += tx_packet.rot_y;
	checksum32 += tx_packet.rot_z;
	checksum32 += tx_packet.pos_z;
	checksum32 += tx_packet.torpedo_ctl;
	for (int i = 0; i < servo_ctl_length; i++)
		checksum32 += tx_packet.servo_ctl[i];
	checksum32 += tx_packet.spare;
	int16_t checksum16 = checksum32;
	return checksum16;
}
