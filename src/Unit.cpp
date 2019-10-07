#include "Unit.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>
#include "MathUtil.hpp"
#include <iostream>

Unit::Unit(const sf::Texture& texture)
: m_isSelected(false)
{
	m_currentTarget = { 80.f, 80.f };

	m_sprite.setOrigin({ 16.f, 16.f });
	m_sprite.setTexture(texture, true);
	m_sprite.setPosition(m_currentTarget);
	
	m_selection.setOrigin({ 16.f, 16.f });
	m_selection.setSize({ 32.f, 32.f });
	m_selection.setPosition(m_sprite.getGlobalBounds().getPosition());
	m_selection.setOutlineThickness(1.f);
	m_selection.setOutlineColor(sf::Color{ 20, 220, 0, 200 });
	m_selection.setFillColor(sf::Color::Transparent);
}

void Unit::Select()
{
	m_isSelected = true;
}

void Unit::Deselect()
{
	m_isSelected = false;
}

bool Unit::IsSelected() const
{
	return m_isSelected;
}

sf::FloatRect Unit::GetGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Unit::GetPosition() const
{
	return m_sprite.getPosition();
}

void Unit::MoveTo(const sf::Vector2f& targetPosition)
{
	m_currentTarget = { std::round(targetPosition.x), std::round(targetPosition.y) };
	m_nextPosition = m_sprite.getPosition();
}

void Unit::Update(const sf::Time& deltaTime)
{
	if (InRange(m_sprite.getPosition(), m_currentTarget, 2.f))
	{
		m_sprite.setPosition(m_currentTarget);
		m_nextPosition = m_sprite.getPosition();
	}
	else
	{
		const auto direction = Normalize(m_currentTarget - m_sprite.getPosition());
		const auto velocity = 200.f * direction;
		m_nextPosition += velocity * deltaTime.asSeconds();

		const auto angle = std::atan2f(direction.y, direction.x);
		m_sprite.setRotation(RadToDeg(angle));
		
		m_sprite.setPosition(sf::Vector2f{ sf::Vector2i{ m_nextPosition } });
	}

	m_selection.setPosition(m_sprite.getPosition());
}

void Unit::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(m_sprite, states);

	if (m_isSelected)
	{
		target.draw(m_selection, states);
	}

	auto vertexLines = sf::VertexArray{ sf::Lines, 2 };
	vertexLines.append({ m_sprite.getPosition(), sf::Color::White });
	vertexLines.append({ m_sprite.getPosition() + (Normalize(m_currentTarget - m_sprite.getPosition()) * 64.f), sf::Color::White });
	//target.draw(vertexLines);
	
	auto targetShape = sf::CircleShape{};
	targetShape.setFillColor(sf::Color::Red);
	targetShape.setRadius(4.f);
	targetShape.setOrigin({ 2.f,2.f });
	targetShape.setPosition(m_currentTarget);
	//target.draw(targetShape);
}
