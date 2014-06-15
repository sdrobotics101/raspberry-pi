#include <mutex>
#include <string.h>
#include "TXPacket.hpp"

TXPacket::TXPacket()
{
	tx_packet_size = sizeof(tx_packet_t);
}

void TXPacket::set_vel_x(int8_t vel_x)
{
	tx_packet.vel_x = vel_x;
}

int8_t TXPacket::get_vel_x()
{
	return tx_packet.vel_x;
}

void TXPacket::set_vel_y(int8_t vel_y)
{
	tx_packet.vel_y = vel_y;
}

int8_t TXPacket::get_vel_y()
{
	return tx_packet.vel_y;
}

void TXPacket::set_vel_z(int8_t vel_z)
{
	tx_packet.vel_z = vel_z;
}

int8_t TXPacket::get_vel_z()
{
	return tx_packet.vel_z;
}

void TXPacket::set_rot_x(int8_t rot_x)
{
	tx_packet.rot_x = rot_x;
}

int8_t TXPacket::get_rot_x()
{
	return tx_packet.rot_x;
}

void TXPacket::set_rot_y(int8_t rot_y)
{
	tx_packet.rot_y = rot_y;
}

int8_t TXPacket::get_rot_y()
{
	return tx_packet.rot_y;
}

void TXPacket::set_rot_z(int8_t rot_z)
{
	tx_packet.rot_z = rot_z;
}

int8_t TXPacket::get_rot_z()
{
	return tx_packet.rot_z;
}

void TXPacket::set_pos_z(int16_t pos_z)
{
	tx_packet.pos_z = pos_z;
}

int16_t TXPacket::get_pos_z()
{
	return tx_packet.pos_z;
}

void TXPacket::set_torpedo_ctl(int8_t torpedo_ctl)
{
	tx_packet.torpedo_ctl = torpedo_ctl;
}

int8_t TXPacket::get_torpedo_ctl()
{
	return tx_packet.torpedo_ctl;
}

void TXPacket::set_servo_ctl(int8_t servo_ctl[])
{
	memcpy(&tx_packet.servo_ctl, servo_ctl, sizeof(tx_packet.servo_ctl));
}

void TXPacket::get_servo_ctl(int8_t servo_ctl[])
{
	memcpy(&servo_ctl, tx_packet.servo_ctl, sizeof(servo_ctl));
}

size_t TXPacket::size()
{
	return tx_packet_size;
}
