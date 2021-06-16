#include "Display.h"

Display::Display()
{
	this->init_warning();
	this->init_variables();
	this->init_window();
	this->init_textures();
	this->init_fonts();
	this->init_startup();
};

Display::~Display()
{
	// Loop ends, memory objects are expunged.
	delete this->window;
};

// Accessors
const bool Display::running() const // Misleading name, means the program is running.
{
	return this->window->isOpen();
};

void Display::poll_events()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed: // If the close button is clicked.
			this->window->close();
			if (this->debugging == true)
			{
				std::cout << "The user closed the display window with the close button." << std::endl;
			}

			break;
		case sf::Event::KeyPressed: // If the Escape key is pressed.
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				if (this->debugging == true)
				{
					std::cout << "The user closed the display window with the Escape button." << std::endl;
				}

				this->window->close();
			}
			break;
		}
	}
};

void Display::update_mousepositions()
{
	// Updates the mouse positions.
	// Updates relative to the main window (Vector2i)

	this->MousePosWindow = sf::Mouse::getPosition(*this->window); // Dereferenced pointer to the window.
	this->MousePosView = this->window->mapPixelToCoords(this->MousePosWindow); // Float based mouse position coordinated with window pixels
};

void Display::update()
{
	this->poll_events();

	this->update_mousepositions();
};

void Display::render()
{
	/* Renders objects. It clears the frame constantly, refreshing with updated visuals. Then it displays the frame in a window. */

	this->window->clear(sf::Color()); // RGB | The alpha needs to be 255 also.

	this->window->draw(text);

	// Render UI at top by drawing last.
	this->window->display();
};

// Private Methods
void Display::init_warning()
{
	std::cout << "This warning is set to display as soon as the program starts." << std::endl;
	std::cout << "Please do NOT close the console (command prompt) window before closing the Editor Display." << std::endl;
	std::cout << "Doing so may cause your program to close incorrectly. Thank you for your time." << std::endl;
	std::cout << std::endl;
};

void Display::init_variables()
{
	this->window = nullptr; // Make sure the pointer is null first.
};

void Display::init_window()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	// this->videoMode.getDesktopMode(); // Used to obtain local desktop resolution

	this->window = new sf::RenderWindow(this->videoMode, "Editor Display", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
};

// Textures currently disabled.
void Display::init_textures()
{
	/*
	sf::Texture texture;
	if (!texture.loadFromFile("assets/File_Icon.png"))
	{
		std::cout << "Image texture could not be loaded." << std::endl;
		exit(1);
	}

	sf::Sprite FileSprite;
	FileSprite.setTexture(texture);
	FileSprite.setPosition(10, 0);
	*/
};

// Loads in the fonts that allow text to be used in the program.
int Display::init_fonts()
{
	if (!font.loadFromFile("assets/fonts/StintUltraCondensed-Regular.ttf")) // If font doesn't load correctly.
	{
		std::cout << "Font loading error. This process cannot continue." << std::endl;
		system("pause");

		return 1; // Forces function termination and returns an error.
	}

	// Program will only execute this far if nothing is wrong.

	if (debugging == true)
	{
		std::cout << "Font file loaded successfully." << std::endl;
	}
	this->text.setFont(this->font);

	return 0;
};

void Display::init_startup()
{
	// This will only happen if fonts and text initialized correctly.
	text.setString("Welcome to the Visual-Design branch of PageMagic!");
};