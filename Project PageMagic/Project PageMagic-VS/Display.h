#ifndef DISPLAY_H
#define DISPLAY_H

#include "pch.h"

class Display
{
public:
	// Constructors etc.
	Display();
	virtual ~Display();

	// Variables

	// Accessors
	const bool running() const;

	// Methods
	void poll_events();

	// Update Methods
	void update_mousepositions();
	void update();

	// Render Methods
	void render();
	// void render_default();

private:
	// Variables
	bool debugging = true;

	// Mouse Positions
	sf::Vector2i MousePosWindow;
	sf::Vector2f MousePosView;

	// Objects
	sf::Texture texture;

	// Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Font font;
	sf::Text text;

	// Methods
	void init_warning();
	void init_variables();
	void init_window();
	void init_textures();
	int init_fonts();
	void init_startup();
};

#endif