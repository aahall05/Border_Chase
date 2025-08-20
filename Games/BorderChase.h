#pragma once

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <random>

#include "../Loaders/HelperFunctions.h"


void BorderChase(sf::RenderWindow& window, sf::Vector2f windowDimensions);

sf::Sprite& LoadPlayer(sf::Texture& playerTexture, sf::Vector2f scale);
sf::Sprite& LoadChevron(sf::Texture& chevronTexture, sf::Vector2f scale, sf::Sprite& player);
sf::Sprite& LoadEnemy(sf::Texture& enemyTexture, sf::Vector2f windowDimensions, sf::Vector2f scale);
void scalePosOrig(sf::Sprite& sprite, sf::Vector2f position, sf::Vector2f scale);

sf::Vector2f PlayerMovement(sf::Sprite& player, sf::Vector2f& minPlayableArea, sf::Vector2f& maxPlayableArea);
float ChevRotation(sf::RenderWindow& window, sf::Sprite& player, sf::Sprite& chevronSprite, sf::Vector2f chevRadius);
sf::Vector2f EnemyMovement(sf::Vector2f position, sf::Vector2f direction, sf::Vector2f& minPlayableArea, sf::Vector2f& maxPlayableArea);