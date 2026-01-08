#pragma once
#include<vector>
#include<SFML/Graphics.hpp>

struct Playercontext {
	std::vector<sf::IntRect> Rects;
};

struct Gamesystem {
	sf::RenderTexture canvas;
};
