#include "Game.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Unit.hpp"
#include "Grid.hpp"
#include "MathUtil.hpp"

void Game::Run()
{
	const auto size = sf::Vector2u{ 1280, 800 };
	
	m_window.create({ size.x, size.y }, "Martis Opibus", sf::Style::Default, sf::ContextSettings{ 0, 0, 8 });
	m_window.setFramerateLimit(60);

	auto highlight = sf::RectangleShape{ { 32.f, 32.f } };
	highlight.setFillColor(sf::Color::Transparent);
	highlight.setOutlineThickness(1.f);
	highlight.setOutlineColor(sf::Color::Green);
	
	auto unitTexture = sf::Texture{};
	if (!unitTexture.loadFromFile("assets/unit.png"))
	{
		throw std::exception{ "Couldn't load unit texture" };
	}
	
	auto backgroundTexture = sf::Texture{};
	if (!backgroundTexture.loadFromFile("assets/background.png"))
	{
		throw std::exception{ "Couldn't load background texture" };
	}

	auto unit = Unit{ unitTexture };
	auto grid = Grid{ size, backgroundTexture };

	auto clock = sf::Clock{};

	auto path = std::deque<sf::Vector2f>{};
	
	while (m_window.isOpen())
	{
		auto deltaTime = clock.restart();
		
		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				{
					auto mousePosition = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (unit.GetGlobalBounds().contains(mousePosition))
						{
							unit.Select();
						}
						else
						{
							unit.Deselect();
						}
					}
					else if(event.mouseButton.button == sf::Mouse::Right)
					{
						if (unit.IsSelected() && grid.IsAccessible(mousePosition))
						{
							auto gridLockedPosition = sf::Vector2f{
								std::floor((mousePosition / 32.f).x) * 32.f + 16.f,
								std::floor((mousePosition / 32.f).y) * 32.f + 16.f
							};

							path = grid.CalculatePath(unit.GetPosition(), gridLockedPosition);
						}
					}
				}
				break;
			case sf::Event::MouseMoved:
				{
					auto mousePosition = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
					auto gridLockedPosition = sf::Vector2f{
									std::floor((mousePosition / 32.f).x) * 32.f,
									std::floor((mousePosition / 32.f).y) * 32.f
					};
					highlight.setPosition(gridLockedPosition);
				}
				break;
			default:
				break;
			}
		}

		if (!path.empty() && InRange(unit.GetPosition(), path.front(), 2.f))
		{
			path.pop_front();

			if (!path.empty())
			{
				unit.MoveTo(path.front());
			}
		}
		unit.Update(deltaTime);
		
		m_window.clear();
		m_window.draw(grid);
		m_window.draw(unit);
		m_window.draw(highlight);
		m_window.display();
	}
}
