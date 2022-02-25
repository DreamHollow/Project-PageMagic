#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "pch.h"
#include <string>

class Manager
{
public:
	Manager();
	virtual ~Manager();

	// Accessors
	const bool debugging() const { return file_debugging; };

	// Variables
	int error_state;
	std::string full_file;

	// Functions
	bool file_created();
	int file_process();
	void file_write(std::string input_param);
	void close_file();

private:
	// Variables
	bool file_debugging;
	bool file_access;
	const std::string filetype{ ".html" };
	std::string f_name;

	// Functions
	bool file_init(std::string& local_file);
	int validate(std::string& local_file);
	void clear_strings();

	// Accessors
	const bool file_verified() const { return file_access; };

	// File System Operator
	std::fstream file;

	// Debugger
};

#endif