#include "CheckBox.h"


CheckBox::CheckBox(float x, float y, std::string text, sf::Font *tmpfont, Okno* root, bool state) : Control(x, y, 10, 10,text,tmpfont,root), state(state)
{
	outer = sf::RectangleShape(sf::Vector2f(w, h));
	outer.setPosition(x, y);
	outer.setFillColor(sf::Color::Black);

	inner = sf::RectangleShape(sf::Vector2f(w - 2, h - 2));
	inner.setPosition(x + 1, y + 1);
	inner.setFillColor(sf::Color::White);

	fill = sf::RectangleShape(sf::Vector2f(w - 4, h - 4));
	fill.setPosition(x + 2, y + 2);
	fill.setFillColor(sf::Color::Blue);

	checkBoxText.setFont(*font);
	checkBoxText.setCharacterSize(10);
	checkBoxText.setString(text);
	checkBoxText.setColor(sf::Color::Black);
	checkBoxText.setPosition(x + w+2, y + static_cast<int>(((inner.getGlobalBounds().height - checkBoxText.getGlobalBounds().height) / 2)));

}

void CheckBox::onClick()
{
	state = !state;
}

void CheckBox::move(float delta_x, float delta_y)
{
	x += delta_x;
	y += delta_y;
	outer.move(delta_x, delta_y);
	inner.move(delta_x, delta_y);
	fill.move(delta_x, delta_y);
	checkBoxText.move(delta_x, delta_y);
}

sf::FloatRect CheckBox::getGlobalBounds() const
{
	return outer.getGlobalBounds();
}

void CheckBox::setFont(sf::Font font)
{
	checkBoxText.setFont(font);
}

void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(outer);
	target.draw(inner);
	target.draw(checkBoxText);
	if (state)
		target.draw(fill);
}
bool CheckBox::isChecked()
{
	return state;
}

CheckBox::~CheckBox()
{
}
