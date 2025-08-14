#pragma once

#include <SFML/Graphics.hpp>

class GameWindow
{
public:
    GameWindow(float widthFraction = 0.75f, float heightFraction = 0.75f, const std::string& title = "Main Window");

    sf::RenderWindow& getWindow();
    const sf::Vector2i& getCenteredPosition() const;

private:
    sf::RenderWindow window;
    sf::Vector2i centeredPosition;
};

