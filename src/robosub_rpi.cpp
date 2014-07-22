/* robosub_rpi.cpp -- Robot control code for Raspberry Pi

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

#include <stdlib.h>
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
