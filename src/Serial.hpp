#ifndef Serial_hpp
#define Serial_hpp

#include "TXPacket.hpp"
#include "RXPacket.hpp"

class Serial
{
public:
	Serial();
	void start();
private:
	TXPacket tx_packet;
	RXPacket rx_packet;
};

#endif /* Serial_hpp */
