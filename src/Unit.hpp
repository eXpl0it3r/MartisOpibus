#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
	class Time;
}

class Unit final : public sf::Drawable
{
public:
	explicit Unit(const sf::Texture& texture);
	void Select();
	void Deselect();
	bool IsSelected() const;
	sf::FloatRect GetGlobalBounds() const;
	sf::Vector2f GetPosition() const;
	void MoveTo(const sf::Vector2f& targetPosition);
	void Update(const sf::Time& deltaTime);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite m_sprite;
	sf::RectangleShape m_selection;
	bool m_isSelected;
	sf::Vector2f m_currentTarget;
	sf::Vector2f m_nextPosition;
};
