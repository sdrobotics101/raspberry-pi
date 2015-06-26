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
	void set_torpedo_ctl(std::bitset < 8 > torpedo_ctl);
	 std::bitset < 8 > get_torpedo_ctl();
	void set_servo_ctl(std::bitset < 8 > servo_ctl);
	 std::bitset < 8 > get_servo_ctl();
	void set_led_ctl(std::bitset < 8 > led_ctl);
	 std::bitset < 8 > get_led_ctl();
	void set_mode(std::bitset < 16 > mode);
	 std::bitset < 16 > get_mode();
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
