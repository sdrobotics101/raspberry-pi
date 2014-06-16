#ifndef RXPacket_hpp
#define RXPacket_hpp

#include <stdint.h>
#include <mutex>

class RXPacket {
 public:
	RXPacket();
	void set_acc_x(int8_t acc_x);
	int8_t get_acc_x();
	void set_acc_y(int8_t acc_y);
	int8_t get_acc_y();
	void set_acc_z(int8_t acc_z);
	int8_t get_acc_z();
	void set_mag_x(int8_t mag_x);
	int8_t get_mag_x();
	void set_mag_y(int8_t mag_y);
	int8_t get_mag_y();
	void set_mag_z(int8_t mag_z);
	int8_t get_mag_z();
	void set_depth(int8_t depth);
	int8_t get_depth();
	size_t size();
	bool read_buffer(unsigned char buffer[]);
	void get_buffer(unsigned char buffer[]);
 private:
	 int16_t compute_checksum();
	typedef struct {
		int16_t header;
		int8_t acc_x;
		int8_t acc_y;
		int8_t acc_z;
		int8_t mag_x;
		int8_t mag_y;
		int8_t mag_z;
		int8_t depth;
		int8_t spare;
		int16_t checksum;
	} __attribute__ ((__packed__)) rx_packet_t;
	rx_packet_t rx_packet;
	 std::mutex rx_packet_mtx;
	size_t rx_packet_size;
};

#endif				// RXPacket_hpp
