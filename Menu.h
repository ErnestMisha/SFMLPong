#pragma once
#include "ABS.h"

class ABS_Menu: public ABS
{
protected:
	struct Button
	{
		sf::RectangleShape shape;
		sf::Text txt;
		bool active = false;
	};
	Button* but;
	sf::Text name;
	bool control;
public:
	ABS_Menu(int s,sf::VideoMode&,sf::RenderWindow&,sf::Event&,status&);
	virtual void draw()=0;
	virtual void sw() = 0;
	virtual ~ABS_Menu()  = 0;
};

class Menu: public ABS_Menu
{
public:
	Menu(sf::VideoMode&, sf::RenderWindow&, sf::Event&, status&);
	void draw();
	void sw();
};

class Server : public ABS_Menu
{
	sf::TcpListener lp;
	sf::IpAddress ip;
	void con();
	sf::TcpSocket* sckp;
public:
	Server(sf::VideoMode&, sf::RenderWindow&, sf::Event&, status&, sf::TcpSocket&);
	void draw();
	void sw();
};

class Client : public ABS_Menu
{
	sf::String str;
	sf::TcpSocket* sckp;
public:
	Client(sf::VideoMode&, sf::RenderWindow&, sf::Event&, status&, sf::TcpSocket&);
	void draw();
	void sw();
};