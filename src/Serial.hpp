#ifndef Serial_hpp
#define Serial_hpp

#include "TXPacket.hpp"
#include "RXPacket.hpp"

class Serial
{
public:
	Serial();
	~Serial();
	void open();
	void start();
private:
	int uart0_filestream;
	TXPacket tx_packet;
	RXPacket rx_packet;
};

#endif /* Serial_hpp */
