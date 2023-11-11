#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class Pipes{

	sf::Texture pipe;
	std::shared_ptr<sf::Sprite> pipeBottom, pipeTop;
	std::vector<sf::Sprite> pipes;
	sf::SoundBuffer point_buffer, hit_buffer;
	sf::Sound point_sound, hit_sound;

	bool add;

public:
	Pipes();
	void addPipes(int c);
	void movePipes(std::size_t i);
	void pipesErase();
	std::vector<sf::Sprite>& getPipesVec();
	void drawPipe(std::shared_ptr<sf::RenderWindow> &window);
	bool addScore(std::size_t i);
	bool pipeCollision(std::size_t i, sf::Sprite &bird);
	void pipesClear();
};
