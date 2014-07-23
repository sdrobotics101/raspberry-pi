/* mode_setting.cpp -- Experiment which manipulates individual bits

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
#include <stdint.h>
#include <stdio.h>
#include <bitset>
#include <iostream>

int main(int argc, char *argv[])
{
	std::bitset < 8 > mode;
	mode[5] = 1;
	mode[2] = 1;
	mode[0] = 1;
	uint8_t mode8 = mode.to_ulong();
	printf("%d", mode8);
	return EXIT_SUCCESS;
}
