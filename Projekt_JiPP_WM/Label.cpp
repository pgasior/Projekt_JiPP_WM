#include "Label.h"
#include <iostream>

Label::Label(float x, float y, std::string text, sf::Font *font, Okno* root)
{
	
	message.setFont(*font);
	message.setCharacterSize(10);
	message.setString(text);
	message.setPosition(x, y);
	message.setColor(sf::Color::Black);
	//std::cout << message.getFont()->getInfo().family << std::endl;
}


Label::~Label()
{
}

void Label::onClick()
{
}

void Label::move(float delta_x, float delta_y)
{
	x += delta_x;
	y += delta_y;
	message.move(delta_x, delta_y);

}

sf::FloatRect Label::getGlobalBounds() const
{
	return message.getGlobalBounds();
}

void Label::setText(std::string new_nessage)
{
	message.setString(new_nessage);
}

std::string Label::getText()
{
	return message.getString();
}

void Label::setFont(sf::Font tmpfont)
{
	message.setFont(tmpfont);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//std::cout << std::string(message.getString()) << std::endl;
	target.draw(message);
}

