#ifndef RXPacket_hpp
#define RXPacket_hpp

#include <stdint.h>

class RXPacket
{
public:
private:
	typedef struct
	{
		int16_t header;
		int8_t acc_x;
		int8_t acc_y;
		int8_t acc_z;
		int8_t mag_x;
		int8_t mag_y;
		int8_t mag_z;
		int8_t pressure;
		int8_t spare;
		int16_t checksum;
	}__attribute__((__packed__)) rx_packet_t;
	int rx_packet_size;
};

#endif /* RXPacket_hpp */
