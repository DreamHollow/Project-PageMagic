#include "Page.h"
#include "Display.h"

/* Heads up! If you are looking at the source code of this program, it's very important you understand this. 
* I am going to be actively implementing SFML into the program for more dynamic web page creation.
* This means some of the core code will be altered to accomodate the changes and the final version of PageMagic may be VERY different.
* All of the data for the visual version of this program will be pushed to an alternate branch. When it's being worked on, look for it there.
* Make no mistake; when the visual version is stable it will likely supercede this existing console version. */

// Global variables are usually VERY BAD but in this case it's considered useful.
std::string full_file;

int main()
{
	// Using this boolean to determine event outcomes.
	bool debug_state = true;

	// Original page object.
	// Page Defacto;

	// Decided to use smart pointers for better and more practical allocation.
	std::unique_ptr<Page> MyPage(new Page()); // Generate heap based pointer
	std::unique_ptr<Display> MyDisplay(new Display()); // Same with this

	// I will be creating options to adjust this resolution later.
	// sf::VideoMode currentMode = sf::VideoMode::getDesktopMode();
	// window.create(sf::VideoMode(currentMode), "Visual Display");

	// While the user has made no effort to close the visual display.
	while (MyDisplay->running())
	{
		MyDisplay->update();
		MyDisplay->render();
	}

	// ATTENTION:
	// Because of the way this is set up right now, the program does NOT terminate here. It will run the console program until otherwise instructed.
	// All of the functions will be moved over to the Display as the program's structure evolves.

	// Still figuring out exceptions. In the meantime this boolean catches unintended breaks in loops or user inputs.
	bool app_exit = false;

	std::string decision;

	// Begin console program parameters.

	std::cout << "This program is designed to create webpages using C++." << std::endl;
	std::cout << "It is currently a WIP and may be lacking features." << std::endl;

	std::cout << "Would you like to create or edit a webpage?" << std::endl;
	std::cout << "Please enter yes or no to respond." << std::endl;
	std::cout << std::endl;
	std::cout << "Your answer: ";
	std::cin >> decision;

	std::transform(decision.begin(), decision.end(), decision.begin(), [](unsigned char c) { return std::tolower(c); }); // String is transformed to lower case.

	std::cout << std::endl;
	std::cout << "You responded: " << decision << std::endl;
	std::cout << std::endl;

	if(decision == "yes")
	{
		int prompt{}; // Initialized to 0
		// Create a new standard HTML5 webpage.
		std::cout << "Would you like to create a new webpage or edit an old one?" << std::endl;
		std::cout << "1. Create one." << std::endl;
		std::cout << "2. View a previous HTML document (Web Page)." << std::endl;
		std::cout << "3. End program." << std::endl;

		std::cout << "Your choice: ";
		std::cin >> prompt;
		std::cout << std::endl;

		switch (prompt)
		{
		case 1:
			// Create a new file.
			MyPage->create_file();

			// Generate standard HTML layouts.
			MyPage->setup();

			app_exit = true; // If the file was created and modified succesfully, it should return this.

			break;
		case 2:
			std::cout << "This feature is currently disabled. It will be re-enabled when functionality is restored. Thank you." << std::endl;

			// MyPage->open_file();

			// I'm not interested in having this menu loop.

			app_exit = true;

			break;
		case 3:
			// The program already has an exit protocol so just flag an exit.
			app_exit = true;

			break;
		default:
			std::cout << "This choice is not supported." << std::endl;

			app_exit = false; // The user made an invalid choice.
			break;
		}
	}
	else if(decision == "no")
	{
		app_exit = true;
	}
	else // If the answer isn't yes OR no
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
	else
	{
		std::cout << std::endl;
		std::cout << "An error occured. Please try again later." << std::endl;
		std::cout << "Shutting down..." << std::endl;

		// Window is forcefully closed because of an error.
		exit(1);
	}

	// Window closes without error.
	system("pause"); // So the user can actually read the goodbye screen.
	return 0;
};