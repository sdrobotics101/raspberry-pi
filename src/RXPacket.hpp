#ifndef RXPacket_hpp
#define RXPacket_hpp

#include <stdint.h>
#include <mutex>

class RXPacket {
 public:
	RXPacket();
	uint16_t get_header();
	void set_mag_x(int16_t mag_x);
	int16_t get_mag_x();
	void set_mag_y(int16_t mag_y);
	int16_t get_mag_y();
	void set_mag_z(int16_t mag_z);
	int16_t get_mag_z();
	void set_pos_z(uint16_t pos_z);
	uint16_t get_pos_z();
	void set_health(uint16_t health);
	uint16_t get_health();
	void set_bat_v(uint8_t bat_v);
	double get_bat_v();
	uint16_t get_checksum();
	size_t size();
	bool valid();
	bool read_buffer(unsigned char buffer[]);
	void get_buffer(unsigned char buffer[]);
 private:
	 uint16_t compute_checksum();
	typedef struct {
		uint16_t header;
		int16_t mag_x;
		int16_t mag_y;
		int16_t mag_z;
		uint16_t pos_z;
		uint16_t health;
		uint8_t bat_v;
		uint16_t checksum;
	} __attribute__ ((__packed__)) rx_packet_t;
	rx_packet_t rx_packet;
	 std::mutex rx_packet_mtx;
	size_t rx_packet_size;
	bool is_valid;
	double bat_v_slope;
	double bat_v_intercept;
};

#endif				// RXPacket_hpp
