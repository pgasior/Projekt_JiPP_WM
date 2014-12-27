#include "Control.h"


Control::Control()
{
}
Control::Control(float x, float y, float w, float h, std::string text, sf::Font* font) : text(text), x(x), y(y), w(w), h(h), font(font)
{
}


Control::~Control()
{
}

//void Control::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{}

