#include "Okno.h"
#include <iostream>

#include <SFML/Graphics.hpp>

Okno::Okno(sf::RenderWindow *win, float x, float y, float w, float h, std::string title, sf::Color kolor) : x(x), y(y), w(w), h(h)
{
	/*view2.setCenter(x - w / 2, y - h / 2);
	view2.setSize(w, h);*/
	window = win;
	winTitle = sf::RectangleShape(sf::Vector2f(w, winh));
	winTitle.setPosition(x, y);
	rectangle = sf::RectangleShape(sf::Vector2f(w, h));
	rectangle.setPosition(x, y + winh);
	rectangle.setFillColor(kolor);
	movingState = false;
	/*winView.setSize(sf::Vector2f(w, h + winh));
	winView.setCenter*/

}
sf::FloatRect Okno::getGlobalBounds()
{
	return rectangle.getGlobalBounds();
}
bool Okno::Clicked()
{
	sf::Vector2f myszf(float(sf::Mouse::getPosition(*window).x), float(sf::Mouse::getPosition(*window).y));
	sf::FloatRect boundr = rectangle.getGlobalBounds();
	sf::FloatRect boundw = winTitle.getGlobalBounds();
	//std::cout << "okno left " << bound.left << "     okno top " << bound.top << std::endl;
	//std::cout << "mysz x " << myszf.x << "     mysz y " << myszf.y << std::endl;
	return (boundr.contains(myszf) || boundw.contains(myszf));
}
bool Okno::titleBarClicked()
{
	sf::Vector2f myszf(float(sf::Mouse::getPosition(*window).x), float(sf::Mouse::getPosition(*window).y));
	sf::FloatRect bound = winTitle.getGlobalBounds();
	return (bound.contains(myszf));
}
sf::Vector2f Okno::getPosition()
{
	return rectangle.getPosition();
}
void Okno::startMove()//(sf::Vector2i startpos)
{
	//sf::Vector2f startposf(startpos.x, startpos.y);
	lastMouse = sf::Mouse::getPosition(*window);
	movingState = true;
}
void Okno::setPosition(sf::Vector2i nowa)
{
	sf::Vector2f nowaf(static_cast<float>(nowa.x), static_cast<float>(nowa.y));
	sf::Vector2f rectpos = rectangle.getPosition();
	sf::Vector2f titlepos = winTitle.getPosition();
	sf::Vector2f inside(nowaf.x - rectpos.x, nowaf.y - rectpos.y);
	//std::cout << "RECT POS X " << rectangle.getPosition().x << " POS Y " << rectangle.getPosition().y << std::endl;
	//std::cout << "NOWA POS X " << nowaf.x << " POS Y " << nowaf.y << std::endl;
	//rectangle.setOrigin(nowa.x - rectpos.x, nowa.y - rectpos.y);
	//std::cout << "RECT POS X " << rectangle.getOrigin().x << " POS Y " << rectangle.getOrigin().y << std::endl;
	//std::cout << "RECT POS X " << rectangle.getPosition().x << " POS Y " << rectangle.getPosition().y << std::endl;
	//std::cout << "NOWA POS X " << nowaf.x - rectpos.x << " POS Y " << nowaf.y - rectpos.y << std::endl;
	rectangle.setPosition(nowaf.x - rectpos.x, nowaf.y - rectpos.y);
}

void Okno::saveMousePosition()
{
	//sf::Vector2i tmp = sf::Mouse::getPosition(*window);
	lastMouse = sf::Mouse::getPosition(*window);

}

bool Okno::getMovingState()
{
	return movingState;
}
void Okno::setMovingstate(bool state)
{
	movingState = state;
}

void Okno::updatePosition()
{
	sf::Vector2f recttmp = rectangle.getPosition();
	sf::Vector2f titletmp = winTitle.getPosition();
	//std::cout << "recttmp x " << recttmp.x << " y " << recttmp.y << std::endl;
	sf::Vector2i newMouse = sf::Mouse::getPosition(*window);
	if (newMouse.x >= static_cast<int>(window->getSize().x) || newMouse.y >= static_cast<int>(window->getSize().y) )
		return;
	//std::cout << "lastmouse x " << lastMouse.x << " y " << lastMouse.y << std::endl;
	//std::cout << "newmouse x " << newMouse.x << " y " << newMouse.y << std::endl;
	rectangle.setPosition(recttmp.x + newMouse.x - lastMouse.x, recttmp.y + newMouse.y - lastMouse.y);
	winTitle.setPosition(titletmp.x + newMouse.x - lastMouse.x, titletmp.y + newMouse.y - lastMouse.y);
	lastMouse = newMouse;
	//movingState = false;
}

void Okno::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	/*states.transform *= getTransform();
	target.draw(winTitle);
	target.draw(rectangle);*/
	//sf::View oldView;
	//target.setView(winView);
	target.draw(winTitle);
	target.draw(rectangle);
	//target.setView(oldView);

}

void Okno::operator=(const Okno &N)
{
	winTitle = N.winTitle;
	rectangle = N.rectangle;
	window = N.window;
	//const float winh = 20.0f;
	x = N.x;
	y = N.y;
	w = N.w;
	h = N.h;
	lastMouse = N.lastMouse;
	movingState = N.movingState;
}
Okno::Okno()
{
}


Okno::~Okno()
{
}
