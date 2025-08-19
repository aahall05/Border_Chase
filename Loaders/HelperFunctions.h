#pragma once

#include<string>
#include <iostream>
#include <SFML/Graphics.hpp>


void CreateText(sf::Text& item, std::string label, int size, sf::Color color, sf::Vector2f position);
bool isHovering(sf::Text& item, sf::Vector2f mousePostion);
