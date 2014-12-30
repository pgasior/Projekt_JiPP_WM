#include "Okno.h"
#include <iostream>
#include "Button.h"

#include <SFML/Graphics.hpp>

Okno::Okno(sf::RenderWindow *win, float x, float y, float w, float h, std::string title, sf::Color kolor, sf::Texture *closeButtonTexture, sf::Texture *titleBarTexture, sf::Texture *windowTexture, sf::Font *font) : x(x), y(y), w(w), h(h), font(font)//, closeButtonTexture(closeButtonTexture)
{
	//kontrolki = new 
	//Kontrolki.push_back(new int(5));
	winh = 20.0f;

	//view = sf::View(sf::FloatRect(x, y, w, h + winh));
	window = win;
	winTitle = sf::RectangleShape(sf::Vector2f(w, winh));
	winTitle.setPosition(x, y);
	winTitle.setTexture(titleBarTexture);
	rectangle = sf::RectangleShape(sf::Vector2f(w, h));
	rectangle.setPosition(x, y + winh);
	rectangle.setFillColor(kolor);
	rectangle.setTexture(windowTexture);

	closeButton = sf::RectangleShape(sf::Vector2f(16, 16));
	closeButton.setPosition(x + w - 16 - 2, y + 2);
	closeButton.setTexture(closeButtonTexture);

	leftBound = sf::RectangleShape(sf::Vector2f(2, h));
	leftBound.setTexture(titleBarTexture);
	leftBound.setPosition(x, y + winh);

	downBound = sf::RectangleShape(sf::Vector2f(w, 2));
	downBound.setTexture(titleBarTexture);
	downBound.setPosition(x, y + winh + h);

	rightBound = sf::RectangleShape(sf::Vector2f(2, h));
	rightBound.setTexture(titleBarTexture);
	rightBound.setPosition(x+w-2, y + winh);
	//std::cout <<"Okno: " << Okno::font->getInfo().family << std::endl;
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
void Okno::checkControls()
{
	sf::Vector2f myszf(float(sf::Mouse::getPosition(*window).x), float(sf::Mouse::getPosition(*window).y));
	for (Array<Button*>::Iterator it = Buttons.begin(); it != Buttons.end(); it++)
	{
		if ((*it)->getGlobalBounds().contains(myszf))
			(*it)->onClick();
	}

}
sf::Vector2f Okno::getPosition()
{
	return rectangle.getPosition();
}

bool Okno::closeButtonClicked()
{
	sf::Vector2f myszf(float(sf::Mouse::getPosition(*window).x), float(sf::Mouse::getPosition(*window).y));
	return closeButton.getGlobalBounds().contains(myszf);
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
	//sf::Vector2f recttmp = rectangle.getPosition();
	//sf::Vector2f titletmp = winTitle.getPosition();
	//sf::Vector2f closeTemp = closeButton.getPosition();
	//sf::Vector2f leftBoundTemp = leftBound.getPosition();
	sf::Vector2i newMouse = sf::Mouse::getPosition(*window);
	if (newMouse.x >= static_cast<int>(window->getSize().x) || newMouse.y >= static_cast<int>(window->getSize().y) )
		return;
	rectangle.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	//rectangle.setPosition(recttmp.x + newMouse.x - lastMouse.x, recttmp.y + newMouse.y - lastMouse.y);
	winTitle.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	//winTitle.setPosition(titletmp.x + newMouse.x - lastMouse.x, titletmp.y + newMouse.y - lastMouse.y);
	//closeButton.setPosition(closeTemp.x + newMouse.x - lastMouse.x, closeTemp.y + newMouse.y - lastMouse.y);
	closeButton.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	leftBound.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	rightBound.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	downBound.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	for (Array<Button*>::Iterator it = Buttons.begin(); it != Buttons.end(); it++)
	{
		(*it)->move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	}
	lastMouse = newMouse;
}

void Okno::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//sf::View tmp = target.getView();
	//target.setView(view);
	target.draw(winTitle);
	target.draw(rectangle);
	target.draw(closeButton);
	target.draw(leftBound);
	target.draw(rightBound);
	target.draw(downBound);
	//for (int i = 0; i < Kontrolki.size(); i++)
	for (Array<Button*>::Iterator it = Buttons.begin(); it != Buttons.end();it++)
	{
		//Kontrolki[i]->draw();
		target.draw(*(*it));
	}

	//target.setView(tmp);

}

//void Okno::operator=(const Okno &N)
//{
//	winTitle = N.winTitle;
//	rectangle = N.rectangle;
//	window = N.window;
//	x = N.x;
//	y = N.y;
//	w = N.w;
//	h = N.h;
//	lastMouse = N.lastMouse;
//	//movingState = N.movingState;
//}
Okno::Okno()
{
}


Okno::~Okno()
{
	Buttons.clear();
}

//void Okno::operator=(const Okno &N)
//{
//	std::cout << "operator=" << std::endl;
//}
//Okno::Okno(const Okno &stary)
//{
//	//std::cout << "kopiujacy" << std::endl;
//	winh = stary.winh;
//	x = stary.x;
//	y = stary.y;
//	w = stary.w;
//	h = stary.h;
//	lastMouse = stary.lastMouse;
//	winTitle = stary.winTitle;
//	rectangle = stary.rectangle;
//	window = stary.window;
//	closeButton = stary.closeButton;
//	leftBound = stary.leftBound;
//	rightBound = stary.rightBound;
//	downBound  =stary.downBound;
//	font = stary.font;
//}

void Okno::addButton(float cx, float cy, float cw, float ch, std::string text, onClickFunction funkcja)
{
	//kontrolka->setFont(font);
	/*std::cout << "Okno adres " << font << std::endl;
	Button * tmp = new Button(x + cx, y + cy + winh, cw, ch, text, font, funkcja);
	std::cout << "NEW BUTTON " << tmp << std::endl;*/
	Buttons.push_back(new Button(x + cx, y + cy + winh, cw, ch, text, font, funkcja , this));
	//delete tmp;
}
