#ifndef TXPacket_hpp
#define TXPacket_hpp

#include <stdint.h>

class TXPacket
{
public:
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
	int tx_packet_size;
};

#endif /* TXPacket_hpp */
