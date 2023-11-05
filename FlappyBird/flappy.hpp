#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <SFML/Audio.hpp>

class FlappyBird {
	std::shared_ptr<sf::RenderWindow> window;
	float gravity, frame, space;
	int count, score;
	bool gameover, add;
	sf::Texture bg, flappy, pipe, play, title;
	std::shared_ptr<sf::Sprite> background, bird, pipeBottom, pipeTop, title_;
	sf::Sprite play_button;
	std::vector<sf::Sprite> pipes;
	sf::Font font;
	sf::Text txt_score, txt_gameover;
	sf::SoundBuffer die_buffer, point_buffer, hit_buffer, flap_buffer, click_buffer;
	sf::Sound die_sound, point_sound, hit_sound, flap_sound, click_sound;
	sf::Vector2i mousePos;

	protected:
		void events();
		void draw();
		void game();
		void movePipes();
		void setAnimeBird();
		void moveBird();
		void button();

	public:
		FlappyBird();
		void run();
	

};
