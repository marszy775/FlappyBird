#include "button.hpp"

Button::Button() {
	bg.loadFromFile("flappy_resources/images/background.jpg");
	play.loadFromFile("flappy_resources/images/button.png");
	title.loadFromFile("flappy_resources/images/Flappy_Logo.png");

	background = std::make_shared<sf::Sprite>();
	title_ = std::make_shared<sf::Sprite>();

	background->setTexture(bg);
	title_->setTexture(title);
	play_button.setTexture(play);

	//position of title and button

	title_->setPosition(250, 100);
	play_button.setPosition(390, 270);
	play_button.setColor(sf::Color(0, 0, 0));

	//click sound

	click_buffer.loadFromFile("flappy_resources/sounds/click.wav");
	click_sound.setBuffer(click_buffer);
}

void Button::drawButton(std::shared_ptr<sf::RenderWindow> window) {
	window->clear(sf::Color::Black);
	window->draw(*background);
	window->draw(*title_);
	window->draw(play_button);

	mousePos = sf::Mouse::getPosition(*window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	if (play_button.getGlobalBounds().contains(mousePosF)) {
		play_button.setColor(sf::Color(4, 146, 4));
	}
	else {
		play_button.setColor(sf::Color(4, 172, 4));
		click_sound.play();
	}

	window->display();
}

sf::Sprite& Button::getButton() {
	return play_button;
}

void Button::drawBackground(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(*background);
}