#include "Game.h"

ABS_Game::ABS_Game(sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st, sf::TcpSocket& sock): ABS(mode,win,ev,st)
{
	tex[0].loadFromFile("back.jpg");
	tex[1].loadFromFile("plank.jpg");
	tex[2].loadFromFile("blade.png");
	font.loadFromFile("pfont.ttf");
	rec[0].setSize(sf::Vector2f(mp->width,mp->height));
	rec[0].setTexture(&tex[0]);
	for (int i = 1; i < 3; i++)
	{
		rec[i].setSize(sf::Vector2f(mp->width/40,mp->height/4));
		rec[i].setTexture(&tex[1]);
		rec[i].setOrigin(mp->width/80,mp->height/8);
	}
	rec[1].setPosition(mp->width/50,mp->height/2);
	rec[2].setPosition(mp->width/1.02,mp->height/2);
	ball.setTexture(&tex[2]);
	ball.setRadius(mp->height/35);
	ball.setOrigin(ball.getLocalBounds().width/2,ball.getLocalBounds().height/2);
	ball.setPosition(mp->width/2,mp->height/2);
	txt[0].setString("0");
	txt[1].setString(":");
	txt[2].setString("0");
	for (int i = 0; i < 3; i++)
	{
		txt[i].setFont(font);
		txt[i].setFillColor(sf::Color(250, 15, 15, 90));
		txt[i].setCharacterSize(mp->height);
		txt[i].setOrigin(txt[i].getLocalBounds().width / 2, txt[i].getLocalBounds().height / 2);
	}
	txt[0].setPosition(mp->width/4.2,mp->height/6.8);
	txt[1].setPosition(mp->width/2.11,mp->height/80);
	txt[2].setPosition(mp->width/1.4,mp->height/6.8);
	sckp = &sock;
	sckp->setBlocking(false);
	socket[0].setBlocking(false);
	socket[1].setBlocking(false);
	pck.padpos = mp->height/2;
	socket[1].bind(sckp->getLocalPort());
	ip[0] =ip[1]=ip[2]= sckp->getRemoteAddress();
	port[0]=port[1] =port[2]= sckp->getRemotePort();
	sckp->disconnect();
}

void ABS_Game::move(int n)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rec[n].getGlobalBounds().top > 0)
	{
			rec[n].move(0, -static_cast<int>(mp->height) / 40);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rec[n].getGlobalBounds().top + rec[n].getGlobalBounds().height < mp->height)
	{
		rec[n].move(0, mp->height / 40);
	}
}

void ABS_Game::draw()
{
	for (int i = 0; i < 3; i++)
	{
		wp->draw(rec[i]);
		wp->draw(txt[i]);
	}
	wp->draw(ball);
	ball.rotate(24);
}

void S_Game::handle()
{
	txt[0].setString(std::to_string(points[0]));
	txt[2].setString(std::to_string(points[1]));
	txt[0].setOrigin(txt[0].getLocalBounds().width / 2, txt[0].getLocalBounds().height / 2);
	txt[2].setOrigin(txt[2].getLocalBounds().width / 2, txt[2].getLocalBounds().height / 2);
	txt[0].setPosition(mp->width / 4.2, mp->height / 6.8);
	txt[2].setPosition(mp->width / 1.4, mp->height / 6.8);
	rec[2].setPosition(rec[2].getPosition().x, mp->height / opos);
	ball.move(std::cos(angle) *mp->width/80, std::sin(angle)*mp->height/80 );
	if (ball.getPosition().y - mp->height / 35 < 0.f)
	{
		angle = -angle;
		ball.setPosition(ball.getPosition().x, mp->height / 35);
	}
	else if (ball.getPosition().y + mp->height / 35 > mp->height)
	{
		angle = -angle;
		ball.setPosition(ball.getPosition().x, mp->height - mp->height / 35);
	}
	else if (ball.getPosition().x + mp->height / 35 < 0.f)
	{
		points[1]++;
		do
		{
			angle = (std::rand() % 360) * 2 * 3.14 / 360;
		} while (std::abs(std::cos(angle)) < 0.6f);
		ball.setPosition(mp->width / 2, mp->height / 2);
	}
	else if (ball.getPosition().x - mp->height / 35 > mp->width)
	{
		points[0]++;
		do
		{
			angle = (std::rand() % 360) * 2 * 3.14 / 360;
		} while (std::abs(std::cos(angle)) < 0.6f);
		ball.setPosition(mp->width / 2, mp->height / 2);
	}
	if (points[0] == 9 || points[1] == 9)
	{
		thw = false;
		thd.join();
		*sp = status::Menu;
		update();
	}
	if (ball.getPosition().x - mp->height / 35 < rec[1].getPosition().x + mp->width / 80 &&
		ball.getPosition().x - mp->height / 35 > rec[1].getPosition().x &&
		ball.getPosition().y + mp->height / 35 >= rec[1].getPosition().y - mp->height / 8 &&
		ball.getPosition().y - mp->height / 35 <= rec[1].getPosition().y + mp->height / 8)
	{
		if (ball.getPosition().y > rec[1].getPosition().y)
			angle = 3.14 - angle + (std::rand() % 20) * 3.14 / 180;
		else
			angle = 3.14 - angle - (std::rand() % 20) * 3.14 / 180;

		ball.setPosition(rec[1].getPosition().x + mp->height / 35 + mp->width / 80 + 0.1f, ball.getPosition().y);
	}

	if (ball.getPosition().x + mp->height / 35 > rec[2].getPosition().x - mp->width / 80 &&
		ball.getPosition().x + mp->height / 35 < rec[2].getPosition().x &&
		ball.getPosition().y + mp->height / 35 >= rec[2].getPosition().y - mp->height / 8 &&
		ball.getPosition().y - mp->height / 35 <= rec[2].getPosition().y + mp->height / 8)
	{
		if (ball.getPosition().y > rec[2].getPosition().y)
			angle = 3.14 - angle + (std::rand() % 20) * 3.14 / 180;
		else
			angle = 3.14 - angle - (std::rand() % 20) * 3.14 / 180;
		ball.setPosition(rec[2].getPosition().x - mp->height / 35 - mp->width / 80 - 0.1f, ball.getPosition().y);
	}
}

void S_Game::update()
{
	pck.points[0] = points[0];
	pck.points[1] = points[1];
	pck.padpos= mp->height/rec[1].getPosition().y;
	pck.ballpos[0] = mp->width/ball.getPosition().x;
	pck.ballpos[1] = mp->height/ball.getPosition().y;
	lk.lock();
	ip[0] = ip[1]=ip[2];
	port[0] = port[1]=port[2];
	lk.unlock();
	socket[0].send(&pck, sizeof(pck), ip[0], port[0]);
	if(thw)
	handle();
}

void srv(S_Game* p)
{
	while (p->thw)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		p->lk.lock();
		p->socket[1].receive(&p->pos, sizeof(p->pos), p->receive, p->ip[1], p->port[1]);
		p->opos = p->pos;
		p->lk.unlock();
	}
}

S_Game::S_Game(sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st, sf::TcpSocket& sock): ABS_Game(mode,win,ev,st,sock)
{
	std::srand(std::time(NULL));
	do
	{
		angle = (std::rand() % 360) * 2 * 3.14 / 360;
	} while (std::abs(std::cos(angle)) < 0.3f);
	points[0] = points[1] = 0;
	mt = status::S_Game;
	thd = std::thread(srv, this);
}

void S_Game::draw()
{
	move(1);
	update();
	ABS_Game::draw();
}

void C_Game::update()
{
	pos = mp->height/rec[2].getPosition().y;
	rec[1].setPosition(rec[1].getPosition().x, mp->height / opck.padpos);
	ball.setPosition(mp->width / opck.ballpos[0], mp->height / opck.ballpos[1]);
	txt[0].setString(std::to_string(opck.points[0]));
	txt[2].setString(std::to_string(opck.points[1]));
	txt[0].setOrigin(txt[0].getLocalBounds().width / 2, txt[0].getLocalBounds().height / 2);
	txt[2].setOrigin(txt[2].getLocalBounds().width / 2, txt[2].getLocalBounds().height / 2);
	txt[0].setPosition(mp->width / 4.2, mp->height / 6.8);
	txt[2].setPosition(mp->width / 1.4, mp->height / 6.8);
	if (opck.points[0] == 9 || opck.points[1] == 9)
	{
		thw = false;
		thd.join();
		*sp = status::Menu;
	}
	lk.lock();
	ip[0] = ip[1]=ip[2];
	port[0] = port[1]=port[2];
	lk.unlock();
	socket[0].send(&pos, sizeof(pos), ip[0], port[0]);
}

void crv(C_Game* p)
{
	while (p->thw)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		p->lk.lock();
		p->socket[1].receive(&p->pck, sizeof(p->pck), p->receive, p->ip[1], p->port[1]);
		p->opck = p->pck;
		p->lk.unlock();
	}
}

C_Game::C_Game(sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st, sf::TcpSocket& sock):ABS_Game(mode,win,ev,st,sock)
{
	mt = status::C_Game;
	thd = std::thread(crv, this);
}

void C_Game::draw()
{
	move(2);
	update();
	ABS_Game::draw();
}