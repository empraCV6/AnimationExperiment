#include"Game.hpp"

void Game() {
	Gamesystem Gsystem;
	sf::RenderWindow window(sf::VideoMode{ 512,224 },"Test");
	Gsystem.canvas.create(512, 224);
	sf::Clock frameClock;
	Player player(&Gsystem);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float dt = frameClock.restart().asSeconds();
		player.stateupdate(dt);
		player.Positionupdate(dt);
		player.PlayerAnim.updateAnimation(dt, &player.Context);
		window.clear(sf::Color::Blue);
		player.draw(&window);

		// FPSŒÅ’è
		float sleepTime = 1/60.f - dt;
		if (sleepTime > 0)
			sf::sleep(sf::seconds(sleepTime));
	}
}