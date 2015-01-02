#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MyList.h"
#include "Array.h"
#include "Okno.h"
#include "Control.h"
class WindowManager
{
public:
	//typedef void(*function)(Okno*);
	Okno* addWindow(float x, float y, float w, float h, std::string title, sf::Color kolor);
	void pollLeftMouseHoldEvents();
	void pollLeftMousePressedEvents();
	void pollLeftMouseReleasedEvents();
	void drawWindows();
	void MessageBox(std::string message);
	//void addButton(Okno *handle, float control_x, float control_y, float control_w, float control_h, function,  std::string text );
	WindowManager(sf::RenderWindow *win);
	~WindowManager();
	typedef void(*onClickFunction)(Okno*);

private:
	sf::RenderWindow *window;
	MyList<Okno> Okna;
	bool top;
	bool mouse_hold;
	Okno *movingWindow;
	sf::Texture closeButtonTexture;
	sf::Texture titleBarTexture;
	sf::Texture windowTexture;
	sf::Font font;
	static void closeWindowFunction(Okno*);
};

