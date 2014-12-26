
#include "stdafx.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include "Okno.h"
#include "Array.h"
#include "MyList.h"
#include "WindowManager.h"
//#include <vld.h>

int main()
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}
	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font
	text.setColor(sf::Color::Red);

	sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
	window.setFramerateLimit(60);

	MyList<Okno> Okna;
	WindowManager wm(&window);


	wm.addWindow(10.0f, 10.0f, 90.0f, 90.0f, "Okno1", sf::Color::Green);
	wm.addWindow(50.0f, 60.0f, 35.0f, 78.0f, "Okno2", sf::Color::Blue);
	wm.addWindow(150.0f, 60.0f, 35.0f, 78.0f, "Okno3", sf::Color::Yellow);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
				window.setView(sf::View(visibleArea));
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					wm.pollLeftMouseReleasedEvents();
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			wm.pollLeftMousePressedEvents();
		}
		window.clear();
		wm.drawWindows();
		window.draw(text);

		window.display();
	}

	return 0;
}
