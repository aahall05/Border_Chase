#include "MainMenu.h"

void MainMenu(sf::RenderWindow& window, sf::Vector2f windowDimensions)
{
    // constants
    float menuItemsX = windowDimensions.x / 2;

    sf::Font menuFont;
    int padding = 15;
    int titleSize = 150;
    int optionSize = 100;

    // load font
    if (!menuFont.openFromFile("Fonts/upheavtt.ttf"))
    {
        std::cout << "font not loaded";
    }

    // create menu title
    sf::Text menuTitle(menuFont);
    CreateText(menuTitle, "Border Chase", titleSize, sf::Color::White, sf::Vector2f(menuItemsX, windowDimensions.y / 3));
    
    // create start button and outline
    sf::Text startButton(menuFont);
    CreateText(startButton, "Start", optionSize, sf::Color::White, sf::Vector2f(menuItemsX, windowDimensions.y - (windowDimensions.y / 3)));
    
    sf::Text startButtonOutline(menuFont);
    CreateText(startButtonOutline, "Start", optionSize, sf::Color::Transparent, sf::Vector2f(menuItemsX, windowDimensions.y - (windowDimensions.y / 3)));
    startButtonOutline.setOutlineColor(sf::Color::Red);
    startButtonOutline.setOutlineThickness(0.75f);
            
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(menuTitle);

        // draw first option, check for hovering
        window.draw(startButton);
        if (startButtonOutline.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            window.draw(startButtonOutline);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                BorderChase(window, windowDimensions);
        }
       
        window.display();
    }
}
