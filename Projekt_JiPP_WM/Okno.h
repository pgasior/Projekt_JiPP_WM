#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include "Array.h"
#include "MyList.h"
//#include "Control.h"
#include "Button.h"
#include "CheckBox.h"
#include "Label.h"
//#include "WindowManager.h"
class WindowManager;
class Okno : public sf::Drawable, public sf::Transformable
{
public:
	
	Okno(sf::RenderWindow *win, float x, float y, float w, float h, std::string title, sf::Color kolor, sf::Texture *closeButtonTexture, sf::Texture *titleBarTexture, sf::Texture *windowTexture, sf::Font *font, WindowManager* wm);
	Okno();
	~Okno();
	typedef void(*onClickFunction)(Okno*);
	sf::FloatRect getGlobalBounds();
	bool Clicked();
	bool titleBarClicked();
	bool closeButtonClicked();
	void checkControls();
	sf::Vector2f getPosition();
	void startMove();
	//void setPosition(sf::Vector2i nowa);
	void saveMousePosition();
	void updatePosition();
	void addButton(float cx, float cy, float cw, float ch, std::string text, onClickFunction funkcja);
	void addCheckBox(float cx, float cy, std::string text, bool state = false);
	void addLabel(float cx, float cy, std::string text);
	//void markForDelete();
	Array<Button*> Buttons;
	Array<CheckBox*> CheckBoxes;
	Array<Label*> Labels;
	WindowManager *wm;
	bool deleteWindow;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RectangleShape winTitle;
	sf::RectangleShape rectangle;
	sf::RenderWindow *window;
	sf::RectangleShape closeButton;
	sf::RectangleShape leftBound;
	sf::RectangleShape rightBound;
	sf::RectangleShape downBound;
	sf::Font *font;
	float winh;
	float x;
	float y;
	float w;
	float h;
	sf::Vector2i lastMouse;
	

};

