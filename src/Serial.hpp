/* Serial.hpp -- Header file for Serial class

   Copyright (C) 2014 Tushar Pankaj
   
   This file is part of San Diego Robotics 101 Robosub.
   
   San Diego Robotics 101 Robosub is free software: you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.
   
   San Diego Robotics 101 Robosub is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
   Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with San Diego Robotics 101 Robosub.  If not, see
   <http://www.gnu.org/licenses/>. */

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
