#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
class Okno : public sf::Drawable, public sf::Transformable
{
public:
	Okno(sf::RenderWindow *win, float x, float y, float w, float h, std::string title, sf::Color kolor, sf::Texture *closeButtonTexture, sf::Texture *titleBarTexture, sf::Texture *windowTexture);
	Okno();
	~Okno();
	//void operator=(const Okno &N);

	sf::FloatRect getGlobalBounds();
	bool Clicked();
	bool titleBarClicked();
	bool closeButtonClicked();
	sf::Vector2f getPosition();
	void startMove();
	void setPosition(sf::Vector2i nowa);
	void saveMousePosition();
	//bool getMovingState();
	//void setMovingstate(bool state);
	void updatePosition();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RectangleShape winTitle;
	sf::RectangleShape rectangle;
	sf::RenderWindow *window;
	sf::RectangleShape closeButton;
	sf::RectangleShape leftBound;
	sf::RectangleShape rightBound;
	sf::RectangleShape downBound;
	//sf::Texture *closeButtonTexture;
	float winh;
	float x;
	float y;
	float w;
	float h;
	//sf::View viewTitle;
	//sf::View viewRectangle;
	//sf::View winView;
	sf::Vector2i lastMouse;
	//bool movingState;
};

