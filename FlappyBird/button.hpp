#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class Button {
	sf::Texture bg, play, title;
	std::shared_ptr<sf::Sprite> background, title_;
	sf::Sprite play_button;
	sf::Vector2i mousePos;
	sf::SoundBuffer click_buffer;
	sf::Sound click_sound;

public:
	Button();
	void drawButton(std::shared_ptr<sf::RenderWindow> window);
	void drawBackground(std::shared_ptr<sf::RenderWindow> window);
	sf::Sprite& getButton();
};