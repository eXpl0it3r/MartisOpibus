#include "Game.hpp"
#include <iostream>

#define SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main()
{
	auto game = Game{};
	
	try
	{
		game.Run();
	}
	catch (std::exception& exception)
	{
		std::cerr << "An unhandled exception was thrown:\n" << exception.what() << "\n";
	}
}
