#include "Menu.h"

ABS_Menu::ABS_Menu(int s,sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st): ABS(mode,win,ev,st)
{
	but = new Button[s];
	font.loadFromFile("comic.ttf");
	name.setFont(font);
	for(int i=0;i<s;i++)
		but[i].txt.setFont(font);
	control = false;
}

ABS_Menu::~ABS_Menu()
{
	delete[]but;
}

Menu::Menu(sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st): ABS_Menu(3,mode,win,ev,st)
{
	mt = status::Menu;
	but[0].txt.setString(L"UTWÓRZ GRÊ");
	but[1].txt.setString(L"DO£¥CZ DO GRY");
	but[2].txt.setString(L"WYJŒCIE");
	for (int i = 0; i < 3; i++)
	{
		but[i].shape.setSize(sf::Vector2f(mp->width, mp->height / 6));
		but[i].shape.setOrigin(mp->width / 2, mp->height / 16);
		but[i].txt.setCharacterSize(mp->height / 14);
		but[i].txt.setLetterSpacing(mp->width / 600);
		but[i].txt.setOrigin(but[i].txt.getLocalBounds().width / 2, but[i].txt.getLocalBounds().height / 2);
	}
	but[0].active = true;
	but[0].shape.setPosition(mp->width / 2, mp->height / 5);
	but[0].txt.setPosition(mp->width / 2, mp->height / 4.5);
	but[1].shape.setPosition(mp->width / 2, mp->height / 2);
	but[1].txt.setPosition(mp->width / 2, mp->height / 2);
	but[2].shape.setPosition(mp->width / 2, mp->height / 1.25);
	but[2].txt.setPosition(mp->width / 2, mp->height / 1.22);
	name.setString("SFML\tLAN\tPONG");
	name.setCharacterSize(mp->height / 10);
	name.setFillColor(sf::Color(25, 255, 33));
	name.setLetterSpacing(mp->width / 500);
	name.setOrigin(name.getLocalBounds().width / 2, name.getLocalBounds().height / 2);
	name.setPosition(mp->width / 2, mp->height / 24);
	for (int i = 0; i < 3; i++)
	{
		if (but[i].active)
		{
			but[i].shape.setFillColor(sf::Color(255, 228, 25));
			but[i].shape.setOutlineThickness(-(mp->height * 0.005));
			but[i].shape.setOutlineColor(sf::Color(23, 255, 174));
			but[i].txt.setFillColor(sf::Color(23, 255, 174));
		}
		else
		{
			but[i].shape.setFillColor(sf::Color(255, 228, 25, 150));
			but[i].shape.setOutlineThickness(false);
			but[i].txt.setFillColor(sf::Color(23, 255, 174, 150));
		}
	}
}

void Menu::draw()
{
	for (int i = 0; i < 3; i++)
	{
		wp->draw(but[i].shape);
		wp->draw(but[i].txt);
	}
	wp->draw(name);
}


void Menu::sw()
{
	control = false;
	if (ep->type == sf::Event::KeyPressed)
	{
		switch (ep->key.code)
		{
		case sf::Keyboard::Up:
		{
			if (but[0].active)
				return;
			for (int i = 1; i < 3; i++)
			{
				if (but[i].active)
				{
					but[i].active = false;
					but[i - 1].active = true;
					control = true;
				}
			}
		}
		break;
		case sf::Keyboard::Down:
		{
			if (but[2].active)
				return;
			for (int i = 1; i > -1; i--)
			{
				if (but[i].active)
				{
					but[i].active = false;
					but[i + 1].active = true;
					control = true;
				}
			}
		}
		break;
		case sf::Keyboard::Enter:
		{
			if (but[0].active)
				*sp = status::Server;
			else if (but[1].active)
				*sp = status::Client;
			else
				wp->close();
		}
		}
	}
	if (control)
	{
		for (int i = 0; i < 3; i++)
		{
			if (but[i].active)
			{
				but[i].shape.setFillColor(sf::Color(255, 228, 25));
				but[i].shape.setOutlineThickness(-(mp->height * 0.005));
				but[i].shape.setOutlineColor(sf::Color(23, 255, 174));
				but[i].txt.setFillColor(sf::Color(23, 255, 174));
			}
			else
			{
				but[i].shape.setFillColor(sf::Color(255, 228, 25, 150));
				but[i].shape.setOutlineThickness(false);
				but[i].txt.setFillColor(sf::Color(23, 255, 174, 150));
			}
		}
	}
}

Server::Server(sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st, sf::TcpSocket& sck) : ABS_Menu(2,mode,win,ev,st)
{
	mt = status::Server;
	sckp = &sck;
	ip = sf::IpAddress::getLocalAddress();
	name.setCharacterSize(mp->height / 12);
	name.setFillColor(sf::Color(219, 46, 20));
	name.setString("ADRES SERWERA");
	name.setLetterSpacing(mp->width / 500);
	name.setOrigin(name.getLocalBounds().width / 2, name.getLocalBounds().height / 2);
	name.setPosition(mp->width / 2, mp->height / 24);
	but[0].txt.setString(ip.toString());
	but[0].txt.setFillColor(sf::Color(25, 255, 33));
	but[0].txt.setCharacterSize(mp->height / 10);
	but[0].txt.setLetterSpacing(mp->width / 600);
	but[0].txt.setOrigin(but[0].txt.getLocalBounds().width / 2, but[0].txt.getLocalBounds().height / 2);
	but[0].shape.setFillColor(sf::Color(255, 131, 15, 40));
	but[0].shape.setSize(sf::Vector2f(mp->width / 1.5, mp->height / 2));
	but[0].shape.setOrigin(mp->width / 3, mp->height / 4);
	but[0].shape.setPosition(mp->width / 2, mp->height / 2.5);
	but[0].txt.setPosition(mp->width / 2, mp->height / 2.7);
	but[1].txt.setString(L"WRÓÆ DO MENU");
	but[1].shape.setSize(sf::Vector2f(mp->width, mp->height / 6));
	but[1].shape.setOrigin(mp->width / 2, mp->height / 12);
	but[1].txt.setFont(font);
	but[1].txt.setCharacterSize(mp->height / 14);
	but[1].txt.setLetterSpacing(mp->width / 600);
	but[1].txt.setOrigin(but[1].txt.getLocalBounds().width / 2, but[1].txt.getLocalBounds().height / 2);
	but[1].shape.setPosition(mp->width / 2, mp->height / 1.25);
	but[1].txt.setPosition(mp->width / 2, mp->height / 1.25);
	but[1].shape.setFillColor(sf::Color(255, 228, 25));
	but[1].shape.setOutlineThickness(-(mp->height * 0.005));
	but[1].shape.setOutlineColor(sf::Color(23, 255, 174));
	but[1].txt.setFillColor(sf::Color(23, 255, 174));
	lp.setBlocking(false);
}

void Server::draw()
{
	con();
	wp->draw(name);
	for (int i = 0; i < 2; i++)
	{
		wp->draw(but[i].shape);
		wp->draw(but[i].txt);
	}
}

void Server::sw()
{
	if (ep->type == sf::Event::KeyPressed)
		if (ep->key.code == sf::Keyboard::Enter)
		{
			*sp = status::Menu;
			lp.close();
			return;
		}
}


void Server::con()
{
	if (!control)
	{
		lp.listen(55555);
		control = true;
		return;
	}
	if(*sp==status::Server)
	if (lp.accept(*sckp) ==sf::Socket::Done)
	{
		lp.close();
		*sp = status::S_Game;
	}
}

Client::Client(sf::VideoMode& mode, sf::RenderWindow& win, sf::Event& ev, status& st, sf::TcpSocket& sck) : ABS_Menu(3,mode,win,ev,st)
{
	mt = status::Client;
	sckp = &sck;
	name.setCharacterSize(mp->height / 12);
	name.setFillColor(sf::Color(219, 46, 20));
	name.setString("PODAJ ADRES SERWERA");
	name.setLetterSpacing(mp->width / 500);
	name.setOrigin(name.getLocalBounds().width / 2, name.getLocalBounds().height / 2);
	name.setPosition(mp->width / 2, mp->height / 24);
	but[0].txt.setString("127.0.0.1");
	but[0].txt.setCharacterSize(mp->height / 10);
	but[0].txt.setFillColor(sf::Color(147, 252, 18, 150));
	but[0].txt.setOrigin(but[0].txt.getLocalBounds().width / 2, but[0].txt.getLocalBounds().height / 2);
	but[0].txt.setPosition(mp->width / 2, mp->height / 3.65);
	but[0].shape.setSize(sf::Vector2f(mp->width / 1.5, mp->height / 5));
	but[0].shape.setFillColor(sf::Color(255, 131, 15, 20));
	but[0].shape.setOrigin(mp->width / 3, mp->height / 10);
	but[0].shape.setPosition(mp->width / 2, mp->height / 3.35);
	but[1].txt.setString(L"DO£¥CZ");
	but[2].txt.setString(L"WRÓÆ DO MENU");
	but[1].shape.setSize(sf::Vector2f(mp->width, mp->height / 6));
	but[2].shape.setSize(sf::Vector2f(mp->width, mp->height / 6));
	but[1].shape.setOrigin(mp->width / 2, mp->height / 12);
	but[2].shape.setOrigin(mp->width / 2, mp->height / 12);
	but[1].txt.setCharacterSize(mp->height / 14);
	but[2].txt.setCharacterSize(mp->height / 14);
	but[1].txt.setLetterSpacing(mp->width / 600);
	but[2].txt.setLetterSpacing(mp->width / 600);
	but[1].txt.setOrigin(but[1].txt.getLocalBounds().width / 2, but[1].txt.getLocalBounds().height / 2);
	but[2].txt.setOrigin(but[2].txt.getLocalBounds().width / 2, but[2].txt.getLocalBounds().height / 2);
	but[1].shape.setPosition(mp->width / 2, mp->height / 1.7);
	but[2].shape.setPosition(mp->width / 2, mp->height / 1.2);
	but[1].txt.setPosition(mp->width / 2, mp->height / 1.75);
	but[2].txt.setPosition(mp->width / 2, mp->height / 1.2);
	but[1].active = true;
	for (int i = 1; i < 3; i++)
	{
		if (but[i].active)
		{
			but[i].shape.setFillColor(sf::Color(255, 228, 25));
			but[i].shape.setOutlineThickness(-(mp->height * 0.005));
			but[i].shape.setOutlineColor(sf::Color(23, 255, 174));
			but[i].txt.setFillColor(sf::Color(23, 255, 174));
		}
		else
		{
			but[i].shape.setFillColor(sf::Color(255, 228, 25, 150));
			but[i].shape.setOutlineThickness(false);
			but[i].txt.setFillColor(sf::Color(23, 255, 174, 150));
		}
	}
}

void Client::draw()
{
	wp->draw(name);
	for (int i = 0; i < 3; i++)
	{
		wp->draw(but[i].shape);
		wp->draw(but[i].txt);
	}
}

void Client::sw()
{
	control = false;
	if (ep->type == sf::Event::KeyPressed)
	{
		switch (ep->key.code)
		{
		case sf::Keyboard::Up:
		{
			if (but[0].active)
				return;
			for (int i = 1; i < 3; i++)
			{
				if (but[i].active)
				{
					but[i].active = false;
					but[i - 1].active = true;
					control = true;
				}
			}
		}
		break;
		case sf::Keyboard::Down:
		{
			if (but[2].active)
				return;
			for (int i = 1; i > -1; i--)
			{
				if (but[i].active)
				{
					but[i].active = false;
					but[i + 1].active = true;
					control = true;
				}
			}
		}
		break;
		case sf::Keyboard::Enter:
		{
			if (but[1].active)
			{
				if (str.getSize() < 1)
					return;
				if (sckp->connect(str.toAnsiString(), 55555) != sf::Socket::Error)
				{
					*sp = status::C_Game;
				}
			}
			else if (but[2].active)
				*sp = status::Menu;
		}
		break;
		}
	}
	if (but[0].active)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))return;
		else if (ep->key.code == sf::Keyboard::Backspace)
		{
			if (str.getSize() < 1)
				return;
			str.erase(str.getSize() - 1);
		}
		else if (ep->type == sf::Event::TextEntered)
		{
			if (str.getSize() > 19)
				return;
			str += ep->text.unicode;
		}
		but[0].txt.setString(str);
		but[0].txt.setOrigin(but[0].txt.getLocalBounds().width / 2, but[0].txt.getLocalBounds().height / 2);
		but[0].txt.setPosition(mp->width / 2, mp->height / 3.65);
	}
	if (control)
	{
		if (but[0].active)
		{
			but[0].shape.setFillColor(sf::Color(255, 131, 15, 40));
			but[0].shape.setOutlineThickness(-(mp->height * 0.005));
			but[0].shape.setOutlineColor(sf::Color(219, 46, 20));
			but[0].txt.setFillColor(sf::Color(147, 252, 18));
			but[1].shape.setFillColor(sf::Color(255, 228, 25, 150));
			but[1].shape.setOutlineThickness(false);
			but[1].txt.setFillColor(sf::Color(23, 255, 174, 150));
			return;
		}
		but[0].shape.setFillColor(sf::Color(255, 131, 15, 20));
		but[0].txt.setFillColor(sf::Color(147, 252, 18, 150));
		but[0].shape.setOutlineThickness(false);
		if (!str.getSize())
		{
			but[0].txt.setString("127.0.0.1");
			but[0].txt.setOrigin(but[0].txt.getLocalBounds().width / 2, but[0].txt.getLocalBounds().height / 2);
			but[0].txt.setPosition(mp->width / 2, mp->height / 3.65);
		}
		for (int i = 1; i < 3; i++)
		{
			if (but[i].active)
			{
				but[i].shape.setFillColor(sf::Color(255, 228, 25));
				but[i].shape.setOutlineThickness(-(mp->height * 0.005));
				but[i].shape.setOutlineColor(sf::Color(23, 255, 174));
				but[i].txt.setFillColor(sf::Color(23, 255, 174));
			}
			else
			{
				but[i].shape.setFillColor(sf::Color(255, 228, 25, 150));
				but[i].shape.setOutlineThickness(false);
				but[i].txt.setFillColor(sf::Color(23, 255, 174, 150));
			}
		}
	}
}