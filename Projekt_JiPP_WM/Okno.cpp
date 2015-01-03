#include "Okno.h"
#include <iostream>
#include "Button.h"
#include "WindowManager.h"
#include <SFML/Graphics.hpp>

Okno::Okno(sf::RenderWindow *win, float x, float y, float w, float h, std::string title, sf::Color kolor, sf::Texture *closeButtonTexture, sf::Texture *titleBarTexture, sf::Texture *windowTexture, sf::Font *font, WindowManager* wm) : wm(wm),window(win), x(x), y(y), w(w), h(h) , font(font)//, closeButtonTexture(closeButtonTexture)
{
	winh = 20.0f;
	deleteWindow = false;

	//window = win;
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
	

	for (Array<CheckBox*>::Iterator it = CheckBoxes.begin(); it != CheckBoxes.end(); it++)
	{
		if ((*it)->getGlobalBounds().contains(myszf))
			(*it)->onClick();
	}
	for (Array<Button*>::Iterator it = Buttons.begin(); it != Buttons.end(); it++)
	{
		if ((*it)->getGlobalBounds().contains(myszf))
			(*it)->onClick();
	}
	/*for (Array<Label*>::Iterator it = Labels.begin(); it != Labels.end(); it++)
	{
		if ((*it)->getGlobalBounds().contains(myszf))
			(*it)->onClick();
	}*/

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
}

void Okno::saveMousePosition()
{
	lastMouse = sf::Mouse::getPosition(*window);
}

void Okno::updatePosition()
{
	sf::Vector2i newMouse = sf::Mouse::getPosition(*window);
	if (newMouse.x >= static_cast<int>(window->getSize().x) || newMouse.y >= static_cast<int>(window->getSize().y) )
		return;
	rectangle.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	winTitle.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	closeButton.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	leftBound.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	rightBound.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	downBound.move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	for (Array<Button*>::Iterator it = Buttons.begin(); it != Buttons.end(); it++)
	{
		(*it)->move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	}

	for (Array<CheckBox*>::Iterator it = CheckBoxes.begin(); it != CheckBoxes.end(); it++)
	{
		(*it)->move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	}
	for (Array<Label*>::Iterator it = Labels.begin(); it != Labels.end(); it++)
	{
		(*it)->move(static_cast<float>(newMouse.x - lastMouse.x), static_cast<float>(newMouse.y - lastMouse.y));
	}
	lastMouse = newMouse;
}

void Okno::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(winTitle);
	target.draw(rectangle);
	target.draw(closeButton);
	target.draw(leftBound);
	target.draw(rightBound);
	target.draw(downBound);
	for (Array<Button*>::Iterator it = Buttons.begin(); it != Buttons.end();it++)
	{
		target.draw(*(*it));
	}
	for (Array<CheckBox*>::Iterator it = CheckBoxes.begin(); it != CheckBoxes.end(); it++)
	{
		target.draw(*(*it));
	}
	for (Array<Label*>::Iterator it = Labels.begin(); it != Labels.end(); it++)
	{
		target.draw(*(*it));
	}
}


Okno::Okno()
{
}


Okno::~Okno()
{
	Buttons.clear();
	CheckBoxes.clear();
	Labels.clear();
}

void Okno::addButton(float cx, float cy, float cw, float ch, std::string text, onClickFunction funkcja)
{
	Buttons.push_back(new Button(x + cx, y + cy + winh, cw, ch, text, font, funkcja , this));
}

void Okno::addCheckBox(float cx, float cy, std::string text, bool state)
{
	CheckBoxes.push_back(new CheckBox(x+cx, y+cy+winh, text, font, this, state));
}

void Okno::addLabel(float cx, float cy, std::string text)
{
	Labels.push_back(new Label(x+cx, y+cy+winh, text, font, this));
}
