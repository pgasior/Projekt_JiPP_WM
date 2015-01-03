#pragma once
#include "Control.h"
class CheckBox : public Control
{
public:
	CheckBox(float x, float y, std::string text, sf::Font *tmpfont, Okno* root, bool state = false);
	~CheckBox();

	void onClick();
	void move(float delta_x, float delta_y);
	sf::FloatRect getGlobalBounds() const;
	void setFont(sf::Font);
	bool isChecked();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RectangleShape outer;
	sf::RectangleShape inner;
	sf::RectangleShape fill;
	sf::Text checkBoxText;
	sf::Texture texture;
	bool state;
};

