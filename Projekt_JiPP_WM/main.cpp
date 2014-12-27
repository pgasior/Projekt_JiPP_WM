
#include "stdafx.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include "Okno.h"
#include "Array.h"
#include "MyList.h"
#include "WindowManager.h"
#include "Button.h"
#include <vld.h>

void b1()
{
	std::cout << "Test" << std::endl;
}

int main()
{


	// select the font


	sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
	window.setFramerateLimit(60);

	MyList<Okno> Okna;
	WindowManager wm(&window);


	Okno *handle = wm.addWindow(10.0f, 10.0f, 90.0f, 90.0f, "Okno1", sf::Color::White);
	wm.addWindow(50.0f, 60.0f, 35.0f, 78.0f, "Okno2", sf::Color::White);
	wm.addWindow(150.0f, 60.0f, 35.0f, 78.0f, "Okno3", sf::Color::White);

	handle->addButton(1, 1, 100, 40, "tekst", b1);
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
		//std::cout << "tu" << std::endl;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			wm.pollLeftMouseHoldEvents();
		}
		window.clear();
		wm.drawWindows();
	

		window.display();
	}

	return 0;
}
