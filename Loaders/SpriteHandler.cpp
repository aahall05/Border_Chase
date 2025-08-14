#pragma once

#include "SpriteHandler.h"

SpriteHandler::SpriteHandler(sf::Sprite& sprite, sf::Vector2f position, sf::Vector2f scale)
{
    sprite.setPosition(position);
    sprite.setScale(scale);
    sprite.setOrigin(sf::Vector2f(sprite.getTexture().getSize().x / 2, sprite.getTexture().getSize().y / 2));
}

