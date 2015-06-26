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
	 Logger(std::string filename, Logger::LogType input_max_log_type);
	~Logger();
	void write(std::string log, Logger::LogType type);
 private:
	 std::ofstream log_file;
	LogType max_log_type;
};

#endif				// Logger_hpp
