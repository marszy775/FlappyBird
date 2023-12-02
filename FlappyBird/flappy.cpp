#include "flappy.hpp"

FlappyBird::FlappyBird() {
	window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(1000, 600),
		"FlappyBird",
		sf::Style::Titlebar | sf::Style::Close
	);
	window->setFramerateLimit(60);
	window->setPosition(sf::Vector2i(0, 0));

	font.loadFromFile("flappy_resources/font/FlappyFont.ttf");

	// setting texts

	txt_gameover.setFont(font);
	txt_gameover.setString("Press SPACE to restart");
	txt_gameover.setPosition(350, 300);
	txt_gameover.setCharacterSize(50);
	txt_gameover.setOutlineThickness(2);

	txt_score.setFont(font);
	txt_score.setString(std::to_string(score));
	txt_score.setPosition(10, -20);
	txt_score.setCharacterSize(70);
	txt_score.setOutlineThickness(2);

	count = 0;
	score = 0;
	gameover = false;
}

void FlappyBird::events() {

	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
		}
	}

	if (gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		score = 0;
		txt_score.setString(std::to_string(score));
		pipes.pipesClear();

		bird1.birdPos();
		gameover = false;
	}

	bird1.birdState();
}

void FlappyBird::game() {
	if (!gameover) {
		birdAction();
		pipesAction();
	}
}

void FlappyBird::run() {
	while (window->isOpen()) {
		events();
		button.drawButton(window);

		mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

		if (button.getButton().getGlobalBounds().contains(mousePosF)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				while (window->isOpen()) {
					events();
					game();
					draw();
				}
			}
		}
	}
}

void FlappyBird::draw() {
	window->clear(sf::Color::Black);
	button.drawBackground(window);

	pipes.drawPipe(window);

	bird1.drawBird(window);

	if (gameover) {
		window->draw(txt_gameover);
	}
	window->draw(txt_score);
	window->display();

	++count;
}

void FlappyBird::pipesAction() {

	pipes.pipesErase();
	pipes.addPipes(count);

	for (std::size_t i = 0; i < pipes.getPipesVec().size(); i++) {
		if (pipes.pipeCollision(i, bird1.getSprite()))
			gameover = true;

		if (pipes.addScore(i))
			txt_score.setString(std::to_string(++score));

		pipes.movePipes(i);
	}
}

void FlappyBird::birdAction() {

	bird1.setAnimeBird();
	bird1.moveBird();

	if (bird1.birdCollision()) {
		gameover = true;
	}
}
