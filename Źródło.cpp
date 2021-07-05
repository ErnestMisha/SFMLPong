#include "Game.h"

int WinMain()
{	
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow win(mode,"SFML LAN Pong", sf::Style::Fullscreen);
	win.setMouseCursorVisible(false);
	win.setVerticalSyncEnabled(true); 
	sf::TcpSocket sock;
	sf::Event ev;
	status st = status::Menu;
	ABS* p = new Menu(mode, win, ev, st);
	while (win.isOpen())
	{
		if (p->mt != st)
		{
			delete p;
			switch (st)
			{
			case status::Menu:
				p = new Menu(mode, win, ev, st);
				break;
			case status::Server:
				p = new Server(mode, win, ev, st,sock);
				break;
			case status::Client:
				p = new Client(mode, win, ev, st,sock);
				break;
			case status::S_Game:
				p = new S_Game(mode, win, ev, st,sock);
				break;
			case status::C_Game:
				p = new C_Game(mode, win, ev, st,sock);
				break;
			}
		}
		while (win.pollEvent(ev))
		{
			p->sw();
		}
		win.clear(sf::Color::Black);
		p->draw();
		win.display();
	}
	delete p;
}