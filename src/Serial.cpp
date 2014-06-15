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
	stop();
}

void Serial::open_serial()
{
	uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (uart0_filestream == -1)
	{
		std::cerr << "Unable to open UART stream on /dev/ttyAMA0." << std::endl;
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

TXPacket* Serial::get_tx_packet()
{
	return &tx_packet;
}

RXPacket* Serial::get_rx_packet()
{
	return &rx_packet;
}

void Serial::run_thread()
{
	is_running = true;
	while (is_running)
	{
		receive_packet();
		transmit_packet();
	}
}

void Serial::receive_packet()
{
}

void Serial::transmit_packet()
{
}
