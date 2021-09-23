#include <cstdint>
#include "Page.h"

#if INTPTR_MAX == INT64_MAX
// Define 64 bit system
#elif INTPTR_MAX == INT32_MAX
// Define 32 bit system
#else
#error Unknown pointer size or missing macros!
#endif

std::string full_file; // Global file name, should be kept consistent across everything
bool program_debug = true; // A boolean that determines whether debug processes are shown
int err_code{}; // Global error code - interrupts processes that violate program rules
int& err_ref = err_code;

int main()
{
	// Using this boolean to determine event outcomes.
	bool debug_state = true;
	
	// Still figuring out exceptions. In the meantime this boolean catches unintended breaks in loops or user inputs.
	bool app_exit = false;

	std::string decision; // Just a short string, not meant to be anything impressive.

	std::cout << "This program is designed to create webpages using C++." << std::endl;
	std::cout << "It is currently a WIP and may be lacking features." << std::endl;

	std::cout << "Would you like to create or edit a webpage?" << std::endl;
	std::cout << "Please enter yes or no to respond." << std::endl;
	std::cout << std::endl;
	std::cout << "Your answer: ";
	std::cin >> decision;

	std::transform(decision.begin(), decision.end(), decision.begin(), [](unsigned char c) { return std::tolower(c); }); // String is transformed to lower case to catch outliers.

	std::cout << std::endl;
	std::cout << "You responded: " << decision << std::endl;
	std::cout << std::endl;

	if(decision == "yes")
	{
		int prompt{};
		// Create a new standard HTML5 webpage.
		std::cout << "Would you like to create a new webpage or edit an old one?" << std::endl;
		std::cout << std::endl; // Create a line break for design sake.
		std::cout << "1. Create one." << std::endl;
		std::cout << "2. View a previous HTML document (Web Page)." << std::endl;
		std::cout << "3. End program." << std::endl;

		std::cout << "Your choice: ";
		std::cin >> prompt; // Prompt and decision are not the same; prompt actually starts file manipulation.
		std::cout << std::endl;

		switch (prompt)
		{
		case 1:
			// Unique pointer object remains in it's own scope. This creates safer exception handling. (I'm still figuring out smart pointers.)
			{
				std::unique_ptr<Page> MyPage = std::make_unique<Page>();

				// Set this variable to true until an event terminates it
				MyPage->is_running = true;

				// This error-catching function currently doesn't do anything, needs logic updates so it fills it's primary function -- TODO
				while (MyPage->is_running && MyPage->error_detected(MyPage->err_ref) == false)
				{
					// Create a new file.
					MyPage->create_file();

					MyPage->setup();

					// Terminate the loop here no matter what
					MyPage->is_running = false;
				}

				if (MyPage->err_ref != 0)
				{
					app_exit = false;
				}
				else if (MyPage->err_ref == 2)
				{
					std::cout << "The program has encountered a serious error and has ceased it's standard functions." << std::endl;

					app_exit = false;
				}
				else
				{
					app_exit = true;
				}
			}

			break;
		case 2:
			std::cout << "This feature is currently disabled. It will be re-enabled when functionality is restored. Thank you." << std::endl;

			// When this feature is successfully implemented, it should be able to read created files.
			// MyPage->open_file();

			// I'm not interested in having this menu loop.

			app_exit = true;

			break;
		case 3:
			// The program already has an exit protocol so just flag an exit.
			app_exit = true;

			break;
		default: // Not a valid response
			std::cout << "Either you typed in letters or you made an invalid number choice." << std::endl;
			std::cout << "This program cannot continue without valid input, forcing program halt." << std::endl;
			std::cout << std::endl;

			// err_code = 1;
			// error_message();
			app_exit = false; // The user made an invalid choice, so the exit is flagged as an error.
			break;
		}
	}
	else if(decision == "no")
	{
		app_exit = true;
	}
	else // If the answer isn't yes OR no; catches numbers, too.
	{
		std::cout << "Sorry," << std::endl;
		std::cout << "This is an invalid response." << std::endl;

		app_exit = false;
	}

	// The program had a clean exit and all user activities have stopped.
	if(app_exit == true)
	{
		std::cout << std::endl;
		std::cout << "Program exit success." << std::endl;
		std::cout << "Thank you for using PageMagic!";
		std::cout << std::endl;
	}

	// The program had an unclean exit and errors occured.
	else if(app_exit == false)
	{
		std::cout << std::endl;
		std::cout << "An error occured. Please try again later." << std::endl;
		std::cout << "Program shutting down..." << std::endl;

		// Window is forcefully closed because of an error.
		return 1;
	}

	// Window closes without error.
	system("pause"); // So the user can actually read the goodbye screen.
	return 0;
};