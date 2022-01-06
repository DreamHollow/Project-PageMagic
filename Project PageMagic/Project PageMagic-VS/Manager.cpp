#include "Manager.hpp"
// extern std::string full_file;

Manager::Manager()
{
	this->error_state = 0;
	this->file_access = true;
};

Manager::~Manager()
{
	if (file)
	{
		close_file();
	}

	this->clear_strings();

	this->file_access = false;
};

int Manager::file_process()
{
	file_init(full_file);
	if (file_verified() == true)
	{
		return 0;
	}
	else
	{
		std::cout << "An error occurred trying to access the file." << std::endl;
		std::cout << "The file editing function will now terminate." << std::endl;
		std::cout << std::endl;

		return 1;
	}
};

bool Manager::file_created()
{
	this->full_file.clear(); // Clear the file name and prepare for file creation

	// extern std::string full_file;

	// Start directory search/creation - TODO(?)

	std::cout << "Please enter the name of the file you are trying to create." << std::endl;
	std::cout << "Filename: ";
	std::cin >> this->f_name;
	std::cout << std::endl;

	// Make sure there are no periods so the program doesn't get confused.

	if (f_name.find('.') != std::string::npos)
	{
		std::cout << "Your file cannot be saved as " << f_name << filetype << "!" << std::endl;
		std::cout << "Your filename cannot contain periods (.) or the file will become corrupted. Please re-launch the program and try again.";
		std::cout << std::endl;

		this->error_state = 1;

		return false;
	}
	//else if (f_name.find("`" || "~" || "!" || "@" || "#" || "$" || "%" || "^" || "&" || "*"))
	//{
	//	std::cout << "Your file cannot be saved as " << f_name << filetype << " !" << std::endl;
	//	std::cout << "Please remove any non-alphanumeric characters from your file name. It will cause file corruption and is not allowed." << std::endl;
	//	std::cout << std::endl;

	//	this->error_state = 1;

	//	return false;
	//}
	//else if (f_name.find("{" || "}" || "|" || "<" || ">"))
	//{
	//	std::cout << "Your file cannot be saved as " << f_name << filetype << " !" << std::endl;
	//	std::cout << "Please remove any non-alphanumeric characters from your file name." << std::endl;
	//	std::cout << "The characters you selected will cause filetype errors and are not allowed." << std::endl;
	//	std::cout << std::endl;

	//	this->error_state = 1;

	//	return false;
	//}

	// String is concatenated so that the file is valid.
	this->full_file = this->f_name + this->filetype; // "full_file".html

	this->f_name = full_file;

	/* Not only is this the name of the file that will be created, this is the file name that will stay in memory.
	As long as the class remains active in the user session, full_file should not change unless the user calls for it to be closed. */

	if (std::ifstream(this->f_name))
	{
		std::cout << "File already exists!" << std::endl;
		std::cout << "Could not create file." << std::endl;

		this->error_state = 1;

		return false;
	}
	std::ofstream file(this->f_name);

	if (!file)
	{
		std::cout << "The file could not be opened. It may be corrupt, missing, or moved." << std::endl;
		std::cout << "Please check your file settings and report this error to the developer." << std::endl;

		this->error_state = 1;

		return false;
	}

	this->validate(full_file);
	this->error_state = 0;

	file.close(); // Always close the file when you're done with it.
	return true;
};

// Only start actual file initialization after the file exists
bool Manager::file_init(std::string &local_file)
{
	// Set file string to argument parameters

	// If this is not possible, return an error
	try
	{
		file.open(local_file, std::ios::in | std::ios::out);
		if (!file)
		{
			throw "Error opening file!";
		}
	}
	catch (const char* cstr) // If the file can't actually open, it should cut off here.
	{
		std::cerr << cstr << std::endl;

		this->file_access = false;

		return false; // File could not open
	}

	this->file_access = true;

	return true;
};

int Manager::validate(std::string& local_file) // Declaration should always just emphasize that a file exists and is accessible.
{
	if (std::ifstream(local_file))
	{
		std::cout << local_file + " was validated successfully." << std::endl;

		if (file_debug.is_debugging() == true)
		{
			std::cout << "validate(std::string local_file) returned a value of 0";
			std::cout << std::endl;
		}

		return 0;
	}
	else
	{
		std::cout << "There was a problem with validating the file name. Please double check file parameters." << std::endl;
		std::cout << std::endl;

		if (file_debug.is_debugging() == true)
		{
			std::cout << "declare() returned a value of 1";
			std::cout << std::endl;
		}

		return 1;
	}
};

void Manager::file_write(std::string input_param)
{
	file << input_param;
	file << std::endl; // Then create a newline
};

void Manager::close_file()
{
	if (!file)
	{
		std::cout << "Error, the file isn't open! There is no file to close." << std::endl;
		std::cout << std::endl;
	}

	file.close();
};

void Manager::clear_strings()
{
	std::cout << "Clearing unsaved file data..." << std::endl;
	std::cout << std::endl;

	f_name.clear();
	full_file.clear();
};