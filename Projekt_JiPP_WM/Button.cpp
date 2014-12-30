#include "Button.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

Button::Button(float x, float y, float w, float h, std::string text, sf::Font *tmpfont, onClickFunction function, Okno* root) : Control(x, y, w, h, text ,tmpfont,root), function(function)
{
	outer = sf::RectangleShape(sf::Vector2f(w, h));
	outer.setPosition(x, y);
	outer.setFillColor(sf::Color::Black);

	inner = sf::RectangleShape(sf::Vector2f(w - 2, h - 2));
	inner.setPosition(x + 1, y + 1);
	inner.setFillColor(sf::Color::White);
	buttonText.setFont(*font);
	buttonText.setCharacterSize(10);
	buttonText.setString(text);
	buttonText.setPosition(x + static_cast<int>(((inner.getGlobalBounds().width - buttonText.getGlobalBounds().width) / 2)), y+static_cast<int>(((inner.getGlobalBounds().height - buttonText.getGlobalBounds().height) / 2)));
	buttonText.setColor(sf::Color::Black);
}

void Button::setFont(sf::Font tmpfont)
{
	buttonText.setFont(tmpfont);
}

void Button::move(float delta_x, float delta_y)
{
	x += delta_x;
	y += delta_y;
	outer.setPosition(x, y);
	inner.setPosition(x + 1, y + 1);
	buttonText.move(delta_x, delta_y);
}
sf::FloatRect Button::getGlobalBounds() const
{
	return outer.getGlobalBounds();
}

Button::~Button()
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(outer);
	target.draw(inner);
	target.draw(buttonText);
}

void Button::onClick()
{
	if (function!=NULL)
		function(root);
}
