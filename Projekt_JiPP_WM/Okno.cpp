#include "Okno.h"
#include <iostream>

#include <SFML/Graphics.hpp>

Okno::Okno(sf::RenderWindow *win, float x, float y, float w, float h, std::string title, sf::Color kolor) : x(x), y(y), w(w), h(h)
{

	window = win;
	winTitle = sf::RectangleShape(sf::Vector2f(w, winh));
	winTitle.setPosition(x, y);
	rectangle = sf::RectangleShape(sf::Vector2f(w, h));
	rectangle.setPosition(x, y + winh);
	rectangle.setFillColor(kolor);
	//movingState = false;


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
void Okno::startMove()
{
	lastMouse = sf::Mouse::getPosition(*window);
	//movingState = true;
}
void Okno::setPosition(sf::Vector2i nowa)
{
	sf::Vector2f nowaf(static_cast<float>(nowa.x), static_cast<float>(nowa.y));
	sf::Vector2f rectpos = rectangle.getPosition();
	sf::Vector2f titlepos = winTitle.getPosition();
	sf::Vector2f inside(nowaf.x - rectpos.x, nowaf.y - rectpos.y);
	rectangle.setPosition(nowaf.x - rectpos.x, nowaf.y - rectpos.y);
}

void Okno::saveMousePosition()
{
	lastMouse = sf::Mouse::getPosition(*window);
}

//bool Okno::getMovingState()
//{
//	return movingState;
//}
//void Okno::setMovingstate(bool state)
//{
//	movingState = state;
//}

void Okno::updatePosition()
{
	sf::Vector2f recttmp = rectangle.getPosition();
	sf::Vector2f titletmp = winTitle.getPosition();
	sf::Vector2i newMouse = sf::Mouse::getPosition(*window);
	if (newMouse.x >= static_cast<int>(window->getSize().x) || newMouse.y >= static_cast<int>(window->getSize().y) )
		return;
	rectangle.setPosition(recttmp.x + newMouse.x - lastMouse.x, recttmp.y + newMouse.y - lastMouse.y);
	winTitle.setPosition(titletmp.x + newMouse.x - lastMouse.x, titletmp.y + newMouse.y - lastMouse.y);
	lastMouse = newMouse;
}

void Okno::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(winTitle);
	target.draw(rectangle);

}

void Okno::operator=(const Okno &N)
{
	winTitle = N.winTitle;
	rectangle = N.rectangle;
	window = N.window;
	x = N.x;
	y = N.y;
	w = N.w;
	h = N.h;
	lastMouse = N.lastMouse;
	//movingState = N.movingState;
}
Okno::Okno()
{
}


Okno::~Okno()
{
}
