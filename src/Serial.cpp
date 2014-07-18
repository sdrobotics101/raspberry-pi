/* Serial.cpp -- Implementation of Serial class

   Copyright (C) 2014 Tushar Pankaj
   
   This file is part of San Diego Robotics 101 Robosub.
   
   San Diego Robotics 101 Robosub is free software: you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by he Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.
   
   San Diego Robotics 101 Robosub is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
   Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with San Diego Robotics 101 Robosub.  If not, see
   <http://www.gnu.org/licenses/>. */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "Serial.hpp"

Serial::Serial()
{
	is_running = false;
	uart0_filestream = -1;
}

Serial::~Serial()
{
	is_running = false;
	transmit_thread->join();
	receive_thread->join();
	delete transmit_thread;
	delete receive_thread;
	close(uart0_filestream);
}

void Serial::open_serial()
{
	uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (uart0_filestream == -1) {
		std::cerr << "Unable to open UART stream on /dev/ttyAMA0." <<
		    std::endl;
		exit(EXIT_FAILURE);
	}
	struct termios options;
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);
}

void Serial::start()
{
	transmit_thread = new std::thread(&Serial::run_transmit_thread, this);
	receive_thread = new std::thread(&Serial::run_receive_thread, this);
}

TXPacket *Serial::get_tx_packet()
{
	return &tx_packet;
}

RXPacket *Serial::get_rx_packet()
{
	return &rx_packet;
}

void Serial::run_transmit_thread()
{
	is_running = true;
	while (is_running) {
		transmit_packet();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void Serial::run_receive_thread()
{
	is_running = true;
	while (is_running)
		receive_packet();
}

bool Serial::receive_packet()
{
	if (uart0_filestream == -1) {
		std::cerr << "UART RX error on /dev/ttyAMA0." << std::endl;
		exit(EXIT_FAILURE);
	}
	unsigned char rx_buffer[rx_packet.size() + 1];
	size_t rx_length = 0;
	while (rx_length < rx_packet.size()) {
		unsigned char tmp_rx_buffer[2];
		int tmp_rx_length =
		    read(uart0_filestream, (void *)tmp_rx_buffer, 1);
		rx_buffer[rx_length] = *tmp_rx_buffer;
		rx_length += tmp_rx_length;
		if (rx_length == 2
		    && (rx_buffer[0] != (int8_t) (rx_packet.get_header())
			|| rx_buffer[1] !=
			(int8_t) (rx_packet.get_header() >> 8))) {
			rx_buffer[0] = rx_buffer[1];
			rx_length--;
		}
	}
	return rx_packet.read_buffer(rx_buffer);
}

void Serial::transmit_packet()
{
	if (uart0_filestream == -1) {
		std::cerr << "UART TX error on /dev/ttyAMA0." << std::endl;
		exit(EXIT_FAILURE);
	}
	unsigned char tx_buffer[tx_packet.size()];
	tx_packet.get_buffer(tx_buffer);
	write(uart0_filestream, &tx_buffer[0], tx_packet.size());
}
