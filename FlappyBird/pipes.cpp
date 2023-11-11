#include "pipes.hpp"

Pipes::Pipes() {

	pipe.loadFromFile("flappy_resources/images/pipe.png");

	pipeBottom = std::make_shared<sf::Sprite>();
	pipeTop = std::make_shared<sf::Sprite>();

	pipeBottom->setTexture(pipe);
	pipeTop->setTexture(pipe);

	// pipes size

	pipeBottom->setScale(1.5, 1.5);
	pipeTop->setScale(1.5, -1.5);

	//point sound

	point_buffer.loadFromFile("flappy_resources/sounds/point.mp3");
	hit_buffer.loadFromFile("flappy_resources/sounds/flappy-bird-hit-sound.mp3");

	point_sound.setBuffer(point_buffer);
	hit_sound.setBuffer(hit_buffer);

	add = false;
}

void Pipes::addPipes(int c) {
	float space = 160;

	if (c % 150 == 0) {
		int pos = std::rand() % 275 + 175;

		pipeBottom->setPosition(1000, static_cast<float>(pos) + space);
		pipeTop->setPosition(1000, static_cast<float>(pos));

		pipes.push_back(*pipeBottom);
		pipes.push_back(*pipeTop);
	}
}

void Pipes::pipesErase() {
	while (!pipes.empty() && pipes.front().getPosition().x < -100)
		pipes.erase(pipes.begin());
}

void Pipes::movePipes(std::size_t i) {
	pipes[i].move(-3, 0);
}

std::vector<sf::Sprite>& Pipes::getPipesVec() {
	return pipes;
}

void Pipes::drawPipe(std::shared_ptr<sf::RenderWindow>& window) {
	for (auto& p : pipes) {
		window->draw(p);
	}
}

bool Pipes::addScore(std::size_t i) {

	if (pipes[i].getPosition().x == 298 && !add) {
		point_sound.play();
		add = true;
		return add;
	}
	else {
		add = false;
		return add;
	}
}

bool Pipes::pipeCollision(std::size_t i, sf::Sprite& bird) {
	if (pipes[i].getGlobalBounds().intersects(bird.getGlobalBounds())) {
		hit_sound.play();
		return true;
	}
	return false;
}

void Pipes::pipesClear() {
	pipes.clear();
}
