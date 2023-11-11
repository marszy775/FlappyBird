#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

extern bool gameover;

class Bird
{
    float frame, gravity;
    sf::Texture flappy;
    std::shared_ptr<sf::Sprite> bird;
    sf::SoundBuffer die_buffer, flap_buffer;
    sf::Sound die_sound, flap_sound;

public:
    Bird();
    void setAnimeBird();
    void moveBird();
    void birdState();
    void birdPos();
    bool birdCollision();
    sf::Sprite& getSprite();
    void drawBird(std::shared_ptr<sf::RenderWindow> window);
};

