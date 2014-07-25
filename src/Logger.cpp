/* Logger.cpp -- Implementation of Logger class

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

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <chrono>
#include "Logger.hpp"

Logger::Logger(std::string filename, Logger::LogType input_min_log_type)
{
	log_file.open(filename, std::ofstream::app);
	min_log_type = input_min_log_type;
}

Logger::~Logger()
{
	log_file.close();
}

void Logger::write(std::string log, Logger::LogType type)
{
	if (type >= min_log_type) {
		std::time_t current_time =
		    std::chrono::system_clock::to_time_t(std::chrono::
							 system_clock::now());
		log_file << "[" << ctime(&current_time) << "]: " << log << std::
		    endl;
	}
}
