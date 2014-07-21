/* CliOptions.cpp -- Implementation of CliOptions class

   Copyright (C) 2014 Tushar Pankaj
   
   This file is part of San Diego CliOptionsics 101 Robosub.
   
   San Diego CliOptionsics 101 Robosub is free software: you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by he Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.
   
   San Diego CliOptionsics 101 Robosub is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
   Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with San Diego CliOptionsics 101 Robosub.  If not, see
   <http://www.gnu.org/licenses/>. */

#include <stdlib.h>
#include <getopt.h>
#include "CliOptions.hpp"

CliOptions::CliOptions(int argc, char* argv[])
{
	is_interactive_flag = false;
	while (true)
	{
		static struct option long_options[] = {
			{"interactive", no_argument, 0, 'i'},
			{0, 0, 0, 0}
		};
		int option_index = 0;
		int c = getopt_long(argc, argv, "i", long_options, &option_index);
		if (c == -1)
			break;
		switch (c)
		{
		case 0:
			break;
		case 'i':
			is_interactive_flag = true;
			break;
		case '?':
			exit(127);
			break;
		default:
			abort();
		}
	}
}

bool CliOptions::is_interactive()
{
	return is_interactive_flag;
}
