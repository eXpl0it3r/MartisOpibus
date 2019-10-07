#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Game
{
public:
	void Run();
	
private:
	sf::RenderWindow m_window;
};
