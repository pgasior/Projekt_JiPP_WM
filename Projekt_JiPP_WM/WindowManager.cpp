#include "WindowManager.h"
#include "Okno.h"


WindowManager::WindowManager(sf::RenderWindow *win)
{
	window = win;
	top = false;
	mouse_hold = false;
	movingWindow = NULL;
	closeButtonTexture.loadFromFile("close-icon.png");
	titleBarTexture.loadFromFile("titlebar.png");
	windowTexture.loadFromFile("window.png");
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Blad wczytywania czcionki" << std::endl;
	}	
}


WindowManager::~WindowManager()
{
}

Okno* WindowManager::addWindow(float x, float y, float w, float h, std::string title, sf::Color kolor)
{

	return Okna.push_back(Okno(window, x, y, w, h, title, kolor,&closeButtonTexture,&titleBarTexture,&windowTexture, &font));
}

void WindowManager::pollLeftMouseHoldEvents()
{
	MyList<Okno>::ReverseIterator it = Okna.rbegin();
	while (!mouse_hold && !movingWindow && it != Okna.rend())
	{
		if (!top && it->Clicked())
		{
			Okna.push_back(&(*it));
			it.getnode()->remove(false);
			it = Okna.rbegin();

			
			it->checkControls();
			if (it->titleBarClicked())
			{
				movingWindow = &(*it);
				it->startMove();
			}
			if (it->closeButtonClicked())
			{
				it.getnode()->remove(true);
				movingWindow = false;
				it = Okna.rbegin();
				break;
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
void WindowManager::pollLeftMousePressedEvents()
{
	MyList<Okno>::ReverseIterator it = Okna.rbegin();
	while (it != Okna.rend())
	{
		if (!top && it->Clicked())
		{
			Okna.push_back(&(*it));
			it.getnode()->remove(false);
			it = Okna.rbegin();
			it->checkControls();
			top = true;
		}
		it++;
	}
	top = false;
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

