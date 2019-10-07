#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <vector>
#include <deque>

class Grid final : public sf::Drawable
{
public:
	explicit Grid(const sf::Vector2u& size, sf::Texture& texture);
	[[nodiscard]] bool IsAccessible(const sf::Vector2f& position) const;
	[[nodiscard]] std::deque<sf::Vector2f> CalculatePath(const sf::Vector2f& start, const sf::Vector2f& end) const;
	std::vector<unsigned> RetrieveNeighborsOf(unsigned index) const;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	unsigned int PositionToIndex(const sf::Vector2f& position, float tileSize, unsigned int gridWidth) const;
	sf::Vector2f IndexToPosition(unsigned index, float tileSize, unsigned gridWidth) const;

private:
	std::vector<int> m_collision;
	std::vector<sf::Vertex> m_gridLines;
	std::vector<sf::Vertex> m_tiles;
	sf::Texture& m_tileTexture;
};
