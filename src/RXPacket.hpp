#ifndef RXPacket_hpp
#define RXPacket_hpp

#include <stdint.h>

class RXPacket
{
public:
private:
	typedef struct
	{
		uint8_t test;
	}__attribute__((__packed__)) rx_packet_t;
};

#endif /* RXPacket_hpp */
