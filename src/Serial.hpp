#ifndef Serial_hpp
#define Serial_hpp

#include <thread>
#include "TXPacket.hpp"
#include "RXPacket.hpp"

class Serial {
 public:
	Serial();
	~Serial();
	void open_serial();
	void start();
	void stop();
	TXPacket *get_tx_packet();
	RXPacket *get_rx_packet();
 private:
	void run_transmit_thread();
	void run_receive_thread();
	bool receive_packet();
	void transmit_packet();
	int uart0_filestream;
	TXPacket tx_packet;
	RXPacket rx_packet;
	bool is_running;
	 std::thread * transmit_thread;
	 std::thread * receive_thread;
};

#endif				// Serial_hpp
