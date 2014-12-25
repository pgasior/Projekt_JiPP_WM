#include "WindowManager.h"
#include "Okno.h"


WindowManager::WindowManager(sf::RenderWindow *win)
{
	window = win;
	moving = false;
	top = false;
	mouse_hold = false;
}


WindowManager::~WindowManager()
{
}

void WindowManager::addWindow(float x, float y, float w, float h, std::string title, sf::Color kolor)
{
	Okna.push_back(Okno(window, x, y, w, h, title, kolor));
}
void WindowManager::pollMousePressedEvents()
{
	for (MyList<Okno>::ReverseIterator it = Okna.rbegin(); it != Okna.rend(); it++)
	{
		if (!moving)
			if (!mouse_hold && !top && !(it->getMovingState()) && it->Clicked()) //it->titleBarClicked())
			{
				Okna.push_back(*it);
				it.getnode()->remove();
				it = Okna.rbegin();
				if (it->titleBarClicked())
				{
					moving = true;
					it->startMove();
				}
				top = true;
			}
		if (it->getMovingState())
		{
			it->updatePosition();
		}
	}
	top = false;
	mouse_hold = true;
}
void WindowManager::pollMouseNotPressedEvents()
{
	mouse_hold = false;
	for (MyList<Okno>::Iterator it = Okna.begin(); it != Okna.end(); it++)
	{
		if (it->getMovingState())
			it->setMovingstate(false);
	}
	moving = false;
}

void WindowManager::drawWindows()
{
	for (MyList<Okno>::Iterator it = Okna.begin(); it != Okna.end(); it++)
		window->draw(*it);
}
