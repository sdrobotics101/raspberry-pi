#include <stdlib.h>
#include <iostream>
#include "CliOptions.hpp"
#include "Robot.hpp"

int main(int argc, char *argv[])
{
	CliOptions opts = CliOptions(argc, argv);
	Robot robot;
	if (opts.is_interactive())
		robot.teleop_mode();
	else
		robot.autonomous_mode();
	return EXIT_SUCCESS;
}
