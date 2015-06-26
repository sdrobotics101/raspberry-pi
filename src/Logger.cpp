#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <chrono>
#include "Logger.hpp"

Logger::Logger(std::string filename, Logger::LogType input_max_log_type)
{
	log_file.open(filename, std::ofstream::app);
	max_log_type = input_max_log_type;
}

Logger::~Logger()
{
	log_file.close();
}

void Logger::write(std::string log, Logger::LogType type)
{
	if (type <= max_log_type) {
		std::time_t current_time =
		    std::chrono::system_clock::to_time_t(std::chrono::
							 system_clock::now());
		std::string time_str = ctime(&current_time);
		time_str = time_str.substr(0, time_str.size() - 1);
		log_file << "[" << time_str << "]: " << log << std::endl;
	}
}
