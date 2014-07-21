/* CliOptions.hpp -- Header file for CliOptions class

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

#ifndef CliOptions_hpp
#define CliOptions_hpp

class CliOptions {
 public:
	CliOptions(int argc, char* argv[]);
	bool is_interactive();
 private:
	bool is_interactive_flag;
};

#endif				// CliOptions_hpp
