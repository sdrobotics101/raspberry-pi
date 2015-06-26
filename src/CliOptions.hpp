#ifndef CliOptions_hpp
#define CliOptions_hpp

class CliOptions {
 public:
	CliOptions(int argc, char *argv[]);
	bool is_interactive();
 private:
	 bool is_interactive_flag;
};

#endif				// CliOptions_hpp
