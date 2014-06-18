#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include "Serial.hpp"

Serial::Serial()
{
	is_running = false;
	uart0_filestream = -1;
}

Serial::~Serial()
{
	if (is_running)
		stop();
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
	serial_thread = new std::thread(&Serial::run_thread, this);
}

void Serial::stop()
{
	is_running = false;
	serial_thread->join();
	close(uart0_filestream);
}

TXPacket *Serial::get_tx_packet()
{
	return &tx_packet;
}

RXPacket *Serial::get_rx_packet()
{
	return &rx_packet;
}

void Serial::run_thread()
{
	is_running = true;
	while (is_running) {
		if (receive_packet())
			transmit_packet();
	}
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
		    && (rx_buffer[0] != (int8_t) (rx_packet.get_header() >> 8)
			|| rx_buffer[1] != (int8_t) rx_packet.get_header())) {
			return false;
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
	int count = write(uart0_filestream, &tx_buffer[0], tx_packet.size());
	if (count < 0) {
		std::cerr << "UART TX error on /dev/ttyAMA0." << std::endl;
		exit(EXIT_FAILURE);
	}
}
