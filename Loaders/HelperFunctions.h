#pragma once

#include<string>
#include <iostream>
#include <SFML/Graphics.hpp>


void CreateText(sf::Text& item, std::string label, int size, sf::Color color, sf::Vector2f position);
void scalePosOrig(sf::Sprite& sprite, sf::Vector2f position, sf::Vector2f scale);
bool isHovering(sf::Text& item, sf::Vector2f mousePostion);
