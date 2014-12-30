#pragma once
#include <string>
#include <SFML/Graphics.hpp>
//#include "Okno.h"
class Okno;
class Control : public sf::Drawable, public sf::Transformable
{
public:

	virtual void onClick() = 0;
	virtual ~Control();
	virtual void move(float delta_x, float delta_y) = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;
	void setText(std::string);
	std::string getText();
	virtual void setFont(sf::Font) = 0;

protected:
	Control(float x, float y, float w, float h, std::string text, sf::Font* font , Okno* root);
	Control();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	std::string text;
	float x; 
	float y; 
	float w; 
	float h;
	sf::Font *font;
	Okno* root;
};

