#pragma once
#include "Control.h"
#include <string>
#include <SFML/Graphics.hpp>
class Button : public Control
{
public:
	typedef void(*onClickFunction)(Okno*);
	Button(float x, float y, float w, float h, std::string text, sf::Font *font, onClickFunction function, Okno* root);
	void onClick();
	void move(float delta_x, float delta_y);
	sf::FloatRect getGlobalBounds() const;
	void setFont(sf::Font tmpfont);
	~Button();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	onClickFunction function;
	sf::RectangleShape outer;
	sf::RectangleShape inner;
	sf::Text buttonText;
	sf::Texture texture;
};

