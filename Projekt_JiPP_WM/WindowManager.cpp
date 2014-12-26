#include "WindowManager.h"
#include "Okno.h"


WindowManager::WindowManager(sf::RenderWindow *win)
{
	window = win;
	top = false;
	mouse_hold = false;
	movingWindow = NULL;
}


WindowManager::~WindowManager()
{
}

void WindowManager::addWindow(float x, float y, float w, float h, std::string title, sf::Color kolor)
{
	Okna.push_back(Okno(window, x, y, w, h, title, kolor));
}
void WindowManager::pollLeftMousePressedEvents()
{
	MyList<Okno>::ReverseIterator it = Okna.rbegin();
	while (!mouse_hold && !movingWindow && it != Okna.rend())
	{
		if (/*!mouse_hold && */!top && it->Clicked())
		{
			Okna.push_back(*it);
			it.getnode()->remove();
			it = Okna.rbegin();
				
			if (it->titleBarClicked())
			{
				movingWindow = &(*it);
				it->startMove();
			}
			top = true;
		}		
		it++;
	}
	if (movingWindow)
	{
		movingWindow->updatePosition();
	}
	top = false;
	mouse_hold = true;
	
}
void WindowManager::pollLeftMouseReleasedEvents()
{
	mouse_hold = false;
	movingWindow = NULL;
}

void WindowManager::drawWindows()
{
	for (MyList<Okno>::Iterator it = Okna.begin(); it != Okna.end(); it++)
		window->draw(*it);
}
