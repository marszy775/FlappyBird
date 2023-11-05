#include "flappy.hpp"


FlappyBird::FlappyBird() {
	window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(1000, 600),
		"FlappyBird",
		sf::Style::Titlebar | sf::Style::Close
	);
	window->setFramerateLimit(60);
	window->setPosition(sf::Vector2i(0, 0));

	gravity = frame = 0;
	space = 160;
	count = 0;
	gameover = false;
	add = false;
	score = 0;

	
	// adding images

	bg.loadFromFile("flappy_resources/images/background.jpg");
	flappy.loadFromFile("flappy_resources/images/flappybird.png");
	pipe.loadFromFile("flappy_resources/images/pipe.png");
	font.loadFromFile("flappy_resources/font/FlappyBirdRegular-9Pq0.ttf");
	title.loadFromFile("flappy_resources/images/Flappy_Logo.png");
	play.loadFromFile("flappy_resources/images/button.png");

	background = std::make_shared<sf::Sprite>();
	bird = std::make_shared<sf::Sprite>();
	pipeBottom = std::make_shared<sf::Sprite>();
	pipeTop = std::make_shared<sf::Sprite>();
	title_ = std::make_shared<sf::Sprite>();
	

	background->setTexture(bg);
	bird->setTexture(flappy);
	pipeBottom->setTexture(pipe);
	pipeTop->setTexture(pipe);
	title_->setTexture(title);
	play_button.setTexture(play);

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

	//sounds

	die_buffer.loadFromFile("flappy_resources/sounds/die.mp3");
	point_buffer.loadFromFile("flappy_resources/sounds/point.mp3");
	hit_buffer.loadFromFile("flappy_resources/sounds/flappy-bird-hit-sound.mp3");
	flap_buffer.loadFromFile("flappy_resources/sounds/flap.mp3");
	click_buffer.loadFromFile("flappy_resources/sounds/click.wav");

	die_sound.setBuffer(die_buffer);
	point_sound.setBuffer(point_buffer);
	hit_sound.setBuffer(hit_buffer);
	flap_sound.setBuffer(flap_buffer);
	click_sound.setBuffer(click_buffer);

	//position of title and button

	title_->setPosition(250, 100);
	play_button.setPosition(390, 270);
	play_button.setColor(sf::Color(0,0,0));

	// 0 position of bird

	bird->setPosition(
		500.f - flappy.getSize().x / 2.f,
		300.f - flappy.getSize().y / 2.f
	);
	bird->setScale(2, 2);
	bird->setTextureRect(sf::IntRect(0, 0, 34, 24));

	// pipes size

	pipeBottom->setScale(1.5, 1.5);
	pipeTop->setScale(1.5, -1.5);


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
		pipes.clear();

		bird->setPosition(
			500 - flappy.getSize().x / 2,
			300 - flappy.getSize().y / 2
		);
		gameover = false;
	}
}

void FlappyBird::button() {
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

void FlappyBird::draw() {
	window->clear(sf::Color::Black);
	window->draw(*background);

	for (auto& p : pipes) {
		window->draw(p);
	}

	window->draw(*bird);

	if (gameover) {
		window->draw(txt_gameover);
	}
	window->draw(txt_score);
	window->display();

	++count;
	

}

void FlappyBird::game() {
	if (!gameover) {
		setAnimeBird();
		moveBird();
		movePipes();
	}
}

void FlappyBird::run() {
	while (window->isOpen()) {
		events();
		button();

		mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

		if (play_button.getGlobalBounds().contains(mousePosF)) {
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

void FlappyBird::movePipes() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		gravity = -4;
		flap_sound.play();
		bird->setRotation(-frame - 10);
	}
	else {
		bird->setRotation(frame - 10);
	}

	if (count % 150 == 0) {
		int pos = std::rand() % 275 + 175;

		pipeBottom->setPosition(1000, pos + space);
		pipeTop->setPosition(1000, pos);

		pipes.push_back(*pipeBottom);
		pipes.push_back(*pipeTop);
	}


	for (std::size_t i=0; i < pipes.size(); i++) {
		if (pipes[i].getPosition().x < -100) {
			pipes.erase(pipes.begin() + i);
		}

		if (pipes[i].getGlobalBounds().intersects(bird->getGlobalBounds())) {
			hit_sound.play();
			gameover = true;
		}


		pipes[i].move(-3, 0);

		if (pipes[i].getPosition().x == 298 && !add) {
			txt_score.setString(std::to_string(++score));
			point_sound.play();
			add = true;
		}
		else {
			add = false;
		}
	}
}

void FlappyBird::setAnimeBird() {
	frame += 0.15;

	if (frame > 3) {
		frame -= 3;
	}

	bird->setTextureRect(sf::IntRect(34 * (int)frame, 0, 34, 24));
}

void FlappyBird::moveBird() {
	bird->move(0, gravity);
	gravity += 0.25;

	//bottom collision
	if (bird->getPosition().y + bird->getGlobalBounds().height > 610) {
		bird->setPosition(bird->getPosition().x, 610 - bird->getGlobalBounds().height);
		die_sound.play();
		gameover = true;
	}

	//top collision
	if (bird->getPosition().y < 0) {
		bird->setPosition(bird->getPosition().x, 0);
		die_sound.play();
		gameover = true;
	}
}