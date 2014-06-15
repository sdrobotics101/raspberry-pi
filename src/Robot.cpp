#include <stdlib.h>
#include "Robot.hpp"

int Robot::start()
{
	serial.open_serial();
	return EXIT_SUCCESS;
}
