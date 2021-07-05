#pragma once
#include "Menu.h"
#include <thread>
#include <mutex>
#include <chrono>

class ABS_Game: public ABS
{
protected:
	struct packet 
	{
		float padpos;
		float ballpos[2];
		short points[2];
	};
	virtual void update() = 0;
	sf::TcpSocket* sckp;
	sf::UdpSocket socket[2];
	sf::IpAddress ip[3];
	unsigned short port[3];
	sf::RectangleShape rec[3];
	sf::CircleShape ball;
	sf::Text txt[3];
	sf::Texture tex[3];
	packet pck;
	float pos;
	std::size_t receive;
	virtual void move(int);
	std::thread thd;
	bool thw = true;
	std::mutex lk;
public:
	ABS_Game(sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st,sf::TcpSocket&);
	virtual void draw() = 0;
	virtual void sw() {}
	virtual ~ABS_Game() {}
};

class S_Game : public ABS_Game
{
	void update();
	void handle();
	float angle;
	int points[2];
	float opos;
	friend void srv(S_Game*);
public:
	S_Game(sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st, sf::TcpSocket&);
	void draw();
};

class C_Game :public ABS_Game
{
	packet opck;
	void update();
	friend void crv(C_Game*);
public:
	C_Game(sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st, sf::TcpSocket&);
	void draw();
};