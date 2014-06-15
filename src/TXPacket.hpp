#ifndef TXPacket_hpp
#define TXPacket_hpp

#include <stdint.h>
#include <mutex>

class TXPacket
{
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
//	void read_buffer(char buffer[]);
//	void get_buffer(char buffer[]);
private:
	typedef struct
	{
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
	}__attribute__((__packed__)) tx_packet_t;
	tx_packet_t tx_packet;
	std::mutex tx_packet_mtx;
	size_t tx_packet_size;
};

#endif /* TXPacket_hpp */
