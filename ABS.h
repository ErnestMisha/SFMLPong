#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

enum class status { Menu, Server, Client, S_Game, C_Game };

class ABS
{
protected:
	sf::Font font;
	sf::VideoMode* mp;
	sf::RenderWindow* wp;
	sf::Event* ep;
	status* sp;
public:
	status mt;
	ABS(sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st)
	{
		mp = &mode;
		wp = &win;
		ep = &ev;
		sp = &st;
	}
	virtual void draw() = 0;
	virtual void sw() = 0;
	virtual ~ABS() {}
};