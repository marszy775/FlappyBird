#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "bird.hpp"
#include "pipes.hpp"
#include "button.hpp"


class FlappyBird {

	std::shared_ptr<sf::RenderWindow> window;
	sf::Font font;
	sf::Text txt_score, txt_gameover;
	sf::Vector2i mousePos;
	int score, count;
	bool gameover;

public:
	FlappyBird();
	void run();

private:
	Bird bird1;
	Button button;
	Pipes pipes;

	void game();
	void events();
	void draw();
	void pipesAction();
	void birdAction();
};