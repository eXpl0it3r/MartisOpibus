#include "Grid.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <random>
#include <queue>
#include <unordered_set>
#include <unordered_map>

Grid::Grid(const sf::Vector2u& size, sf::Texture& texture)
: m_tileTexture(texture)
{
	m_collision = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
					10,  1,  2,  2,  5,  5,  2,  5,  2,  5,  5,  5,  2,  2,  2,  2,  2,  5,  5,  2,  2,  5,  5,  2,  2,  4, 10, 10, 10,  1,  5,  5,  5,  2,  2,  5,  5,  4, 10, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10, 10, 10,  3, 21, 21, 21,  0,  0,  0,  0, 13,  4, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 13,  4, 10, 10,  3, 21, 21,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10, 10,  3, 21,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 13,  5,  2, 14,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 20, 20, 20,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0, 20, 20,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 20, 20, 20,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0, 20,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 20,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0, 17,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0, 17,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 17,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 19, 19, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0, 16, 19, 15, 16, 15, 15, 16, 16, 16, 15, 16, 16, 19, 19,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 17,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10,  9, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10, 10,  9,  7,  7,  7, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10, 10, 10, 10, 10, 10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10, 10, 10, 10, 10, 10,  9, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,  7,  7,  7, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 10,
					10, 10, 10, 10, 10, 10, 10,  3,  0,  0,  0,  0,  0,  0,  0,  0, 12,  8, 10, 10, 10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,  7,  8, 10,
					10, 10, 10, 10, 10, 10, 10,  3,  0,  0,  0,  0,  0,  0,  0,  12, 8, 10, 10, 10, 10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 21, 21, 12,  8, 10, 10, 10,
					10, 10, 10, 10, 10, 10, 10,  9,  7,  7,  7,  7,  7,  7,  7,  8, 10, 10, 10, 10, 10,  9,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 10, 10, 10, 10,
					10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	
	const auto gridColor = sf::Color{ 220,  200,  200,  30 };
	
	for (auto x = 0u; x < size.x / 32u; ++x)
	{
		m_gridLines.emplace_back(sf::Vector2f{ x * 32.f + 0.5f,  0.5f },  gridColor);
		m_gridLines.emplace_back(sf::Vector2f{ x * 32.f + 0.5f,  static_cast<float>(size.y) + 0.5f },  gridColor);
	}
	
	for (auto y = 0u; y < size.y / 32u; ++y)
	{
		m_gridLines.emplace_back(sf::Vector2f{ 0.5f,  y * 32.f + 0.5f },  gridColor);
		m_gridLines.emplace_back(sf::Vector2f{ static_cast<float>(size.x) + 0.5f,  y * 32.f + 0.5f },  gridColor);
	}

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	const std::uniform_int_distribution<> distribution(0,  8);

	for (auto y = 0u; y < size.y / 32u; ++y)
	{
		for (auto x = 0u; x < size.x / 32u; ++x)
		{
			const auto tileType = m_collision[x + (y * (size.x / 32u))];
			const auto randomBlankTile = distribution(randomEngine) * 32.f;
			auto tilePosition = sf::Vector2f{};

			if (tileType == 0)
			{
				tilePosition = { 0.f,  randomBlankTile };
			}
			else if (tileType > 0)
			{
				tilePosition = { 32.f,  (tileType - 1) * 32.f };
			}
			
			m_tiles.emplace_back(sf::Vector2f{ x * 32.f, y * 32.f }, sf::Vector2f{ tilePosition.x, tilePosition.y });
			m_tiles.emplace_back(sf::Vector2f{ x * 32.f, y * 32.f + 32.f }, sf::Vector2f{ tilePosition.x, tilePosition.y + 32.f });
			m_tiles.emplace_back(sf::Vector2f{ x * 32.f + 32.f, y * 32.f + 32.f }, sf::Vector2f{ tilePosition.x + 32.f, tilePosition.y + 32.f });
			m_tiles.emplace_back(sf::Vector2f{ x * 32.f + 32.f, y * 32.f }, sf::Vector2f{ tilePosition.x + 32.f, tilePosition.y });
		}
	}
}

bool Grid::IsAccessible(const sf::Vector2f& position) const
{
	return m_collision[PositionToIndex(position, 32.f, 40u)] == 0;
}

std::deque<sf::Vector2f> Grid::CalculatePath(const sf::Vector2f& start, const sf::Vector2f& end) const
{
	auto startIndex = PositionToIndex(start, 32.f, 40u);
	auto endIndex = PositionToIndex(end, 32.f, 40u);

	auto frontier = std::queue<unsigned int>{};
	frontier.push(startIndex);

	auto cameFrom = std::unordered_map<unsigned int, unsigned int>{};
	cameFrom[startIndex] = startIndex;
	
	while (!frontier.empty())
	{
		auto current = frontier.front();
		frontier.pop();

		if (current == endIndex)
		{
			break;
		}
		
		for (auto next : RetrieveNeighborsOf(current))
		{
			if (cameFrom.find(next) == cameFrom.end())
			{
				frontier.push(next);
				cameFrom[next] = current;
			}
		}
	}

	auto path = std::deque<sf::Vector2f>{};
	path.push_front(IndexToPosition(endIndex, 32.f, 40u));
	
	for (auto next = cameFrom.find(endIndex); next != cameFrom.find(startIndex) && next != cameFrom.end(); next = cameFrom.find(next->second))
	{
		path.push_front(IndexToPosition(next->second, 32.f, 40u));
	}
	
	return path;
}

std::vector<unsigned int> Grid::RetrieveNeighborsOf(const unsigned int index) const
{
	auto neighbors = std::vector<unsigned int>{};
	
	if (index > 0u && m_collision[index - 1u] == 0)
	{
		neighbors.push_back(index - 1u);
	}
	if (index + 1u < m_collision.size() && m_collision[index + 1u] == 0)
	{
		neighbors.push_back(index + 1u);
	}
	if (index >= 40u && m_collision[index - 40u] == 0)
	{
		neighbors.push_back(index - 40u);
	}
	if (index + 40u < m_collision.size() && m_collision[index + 40u] == 0)
	{
		neighbors.push_back(index + 40u);
	}

	return neighbors;
}

void Grid::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	auto tileStates = states;
	tileStates.texture = &m_tileTexture;
	target.draw(m_tiles.data(), m_tiles.size(), sf::Quads, tileStates);
	
	target.draw(m_gridLines.data(), m_gridLines.size(), sf::Lines, states);
}

unsigned int Grid::PositionToIndex(const sf::Vector2f& position, const float tileSize, const unsigned int gridWidth) const
{
	return static_cast<unsigned int>(std::floor(position.x / tileSize) + static_cast<unsigned int>(std::floor(position.y / tileSize)) * gridWidth);
}

sf::Vector2f Grid::IndexToPosition(unsigned int index, const float tileSize, const unsigned int gridWidth) const
{
	return { (index - ((index / gridWidth) * gridWidth)) * tileSize + 16.f,
		(index / gridWidth) * tileSize + 16.f
	};
}