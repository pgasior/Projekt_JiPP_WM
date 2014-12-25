#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MyList.h"
#include "Okno.h"
class WindowManager
{
public:
	void addWindow(float x, float y, float w, float h, std::string title, sf::Color kolor);
	void pollMousePressedEvents();
	void pollMouseNotPressedEvents();
	void drawWindows();
	WindowManager(sf::RenderWindow *win);
	~WindowManager();

private:
	sf::RenderWindow *window;
	MyList<Okno> Okna;
	bool moving;
	bool top;
	bool mouse_hold;
};

