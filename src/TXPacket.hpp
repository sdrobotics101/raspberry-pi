#ifndef TXPacket_hpp
#define TXPacket_hpp

#include <stdint.h>

class TXPacket
{
public:
private:
	typedef struct
	{
		uint8_t test;
	}__attribute__((__packed__)) tx_packet_t;
};

#endif /* TXPacket_hpp */
