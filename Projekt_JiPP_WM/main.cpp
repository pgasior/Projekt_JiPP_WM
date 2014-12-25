
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

	MyList<Okno> Okna;
	WindowManager wm(&window);

	/*Okna.push_back(Okno(&window,10.0f, 10.0f, 90.0f, 90.0f,"Okno1", sf::Color::Green));
	Okna.push_back(Okno(&window,50.0f, 60.0f, 35.0f, 78.0f, "Okno2", sf::Color::Blue));
	Okna.push_back(Okno(&window, 150.0f, 60.0f, 35.0f, 78.0f, "Okno3", sf::Color::Yellow));*/
	wm.addWindow(10.0f, 10.0f, 90.0f, 90.0f, "Okno1", sf::Color::Green);
	wm.addWindow(50.0f, 60.0f, 35.0f, 78.0f, "Okno2", sf::Color::Blue);
	wm.addWindow(150.0f, 60.0f, 35.0f, 78.0f, "Okno3", sf::Color::Yellow);
	//bool moving = false;
	//bool top = false;
	//bool mouse_hold = false;
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
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//for (MyList<Okno>::ReverseIterator it = Okna.rbegin(); it != Okna.rend();it++)
			//{
			//	if (!moving)
			//		if (!mouse_hold && !top && !(it->getMovingState()) &&  it->Clicked()) //it->titleBarClicked())
			//		{
			//			Okna.push_back(*it);
			//			it.getnode()->remove();
			//			it = Okna.rbegin();
			//			if (it->titleBarClicked())
			//			{
			//				moving = true;
			//				it->startMove();
			//			}
			//			top = true;
			//		}
			//	if (it->getMovingState())
			//	{
			//		it->updatePosition();
			//	}
			//}
			//top = false;
			//mouse_hold = true;
			wm.pollMousePressedEvents();
		}
		else //if !(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			/*mouse_hold = false;
			for (MyList<Okno>::Iterator it = Okna.begin(); it != Okna.end(); it++)
			{
			if (it->getMovingState())
			it->setMovingstate(false);
			}
			moving = false;*/
			wm.pollMouseNotPressedEvents();
		}
		window.clear();
		/*for (MyList<Okno>::Iterator it = Okna.begin(); it != Okna.end(); it++)
		window.draw(*it);*/
		wm.drawWindows();
		/*window.draw(okno1);
		window.draw(okno2);*/
		window.draw(text);
		/*text.setString("Okno1");*/

		window.display();
	}

	return 0;
}
