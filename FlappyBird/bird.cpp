#include "bird.hpp"

Bird::Bird() {
	flappy.loadFromFile("flappy_resources/images/flappybird.png");
	bird = std::make_shared<sf::Sprite>();
	bird->setTexture(flappy);

	gravity = frame = 0;

	// 0 position of bird

	birdPos();

	bird->setScale(2, 2);
	bird->setTextureRect(sf::IntRect(0, 0, 34, 24));

	die_buffer.loadFromFile("flappy_resources/sounds/die.mp3");
	flap_buffer.loadFromFile("flappy_resources/sounds/flap.mp3");

	die_sound.setBuffer(die_buffer);
	flap_sound.setBuffer(flap_buffer);
}

void Bird::setAnimeBird() {
	frame += 0.15f;

	if (frame > 3) {
		frame -= 3;
	}

	bird->setTextureRect(sf::IntRect(34 * (int)frame, 0, 34, 24));
}

void Bird::moveBird() {
	bird->move(0, gravity);
	gravity += 0.25f;
}

void Bird::birdState() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		gravity = -4;
		flap_sound.play();
		bird->setRotation(-frame - 10);
	}
	else {
		bird->setRotation(frame - 10);
	}
}

sf::Sprite& Bird::getSprite() {
	return *bird;
}

void Bird::drawBird(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(*bird);
}

void Bird::birdPos() {
	bird->setPosition(
		500.f - static_cast<float>(flappy.getSize().x) / 2.f,
		300.f - static_cast<float>(flappy.getSize().y) / 2.f
	);
}

bool Bird::birdCollision() {
	//bottom collision
	if (bird->getPosition().y + bird->getGlobalBounds().height > 610) {
		bird->setPosition(bird->getPosition().x, 610 - bird->getGlobalBounds().height);
		die_sound.play();
		return true;
	}

	//top collision
	if (bird->getPosition().y < 0) {
		bird->setPosition(bird->getPosition().x, 0);
		die_sound.play();
		return true;
	}

	return false;
}