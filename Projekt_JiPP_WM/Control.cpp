#include "Control.h"
//#include "Okno.h"


Control::Control()
{
}
Control::Control(float x, float y, float w, float h, std::string text, sf::Font* font, Okno* root) : text(text), x(x), y(y), w(w), h(h), font(font), root(root)
{
}


Control::~Control()
{
}


