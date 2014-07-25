/* Logger.hpp -- Header file for Logger class

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

#ifndef Logger_hpp
#define Logger_hpp

#include <iostream>
#include <fstream>
#include <string>

class Logger {
 public:
	enum LogType {
		ERROR,
		WARNING,
		MESSAGE,
		VERBOSE,
		DEBUG
	};
	 Logger(std::string filename, Logger::LogType input_min_log_type);
	~Logger();
	void write(std::string log, Logger::LogType type);
 private:
	 std::ofstream log_file;
	LogType min_log_type;
};

#endif				// Logger_hpp
