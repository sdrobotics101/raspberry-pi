#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>

#include "Serial.hpp"

Serial::Serial()
{
	uart0_filestream = -1;
}

Serial::~Serial()
{
	close(uart0_filestream);
}

void Serial::open()
{
	uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (uart0_filestream == -1)
	{
		std::cerr << "Unable to open UART stream on /dev/ttyAMA0" << std::endl;
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
}
