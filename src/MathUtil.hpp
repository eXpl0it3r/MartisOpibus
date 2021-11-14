#pragma once

#include <limits>
#include <cmath>

#include <SFML/System/Vector2.hpp>

inline bool InRange(const sf::Vector2f& a, const sf::Vector2f& b, const float epsilon = std::numeric_limits<float>::epsilon())
{
	return a.x + epsilon >= b.x && a.x - epsilon <= b.x
		&& a.y + epsilon >= b.y && a.y - epsilon <= b.y;
}

inline float Norm(const sf::Vector2f& vector)
{
	return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

inline sf::Vector2f Normalize(const sf::Vector2f& vector)
{
	constexpr auto unitsInLastPlace = 2;
	const auto norm = Norm(vector);

	// Prevent division by zero
	if (norm <= std::numeric_limits<float>::epsilon() * norm * unitsInLastPlace
		|| norm < std::numeric_limits<float>::min())
	{
		return sf::Vector2f{};
	}

	return vector / norm;
}

inline float RadToDeg(const float rad)
{
	const auto pi = 3.14159265359f;
	return rad * 180 / pi;
}