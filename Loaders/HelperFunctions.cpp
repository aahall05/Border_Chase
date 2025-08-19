#pragma once

#include "HelperFunctions.h"

void CreateText(sf::Text& item, std::string label, int size, sf::Color color, sf::Vector2f position)
{
    item.setString(label);
    item.setCharacterSize(size);
    item.setFillColor(color);
    item.setPosition(position);

    // get bounding box of the text
    sf::FloatRect textRect = item.getLocalBounds();

    // set the origin to the center of the bounding box
    item.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f));
}


bool isHovering(sf::Text& item, sf::Vector2f mousePostion)
{
    
    return item.getGlobalBounds().contains(mousePostion);
}


