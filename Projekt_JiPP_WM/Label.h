#pragma once
#include "Control.h"
#include <SFML/Graphics.hpp>
class Label : public Control
{
public:
	Label(float x, float y, std::string text, sf::Font *font, Okno* root);
	~Label();
	void onClick();
	void move(float delta_x, float delta_y);
	sf::FloatRect getGlobalBounds() const;
	void setText(std::string);
	std::string getText();
	void setFont(sf::Font);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Text message;
};

