#include "MainMenu.h"

void MainMenu(sf::RenderWindow& window, sf::Vector2f windowDimensions)
{
    // constants
    float menuItemsX = windowDimensions.x / 2;

    sf::Font menuFont;
    int padding = 15;
    int titleSize = 100;
    int optionSize = 50;

    // load font
    if (!menuFont.openFromFile("Fonts/upheavtt.ttf"))
    {
        std::cout << "font not loaded";
    }

    // create menu tile
    sf::Text menuTitle(menuFont);
    CreateText(menuTitle, "Main Menu", 100, sf::Color::White, sf::Vector2f(menuItemsX, windowDimensions.y / 3));
    
    // create item and outline
    sf::Text borderChase(menuFont);
    CreateText(borderChase, "Border Chase", 50, sf::Color::White, sf::Vector2f(menuItemsX, menuTitle.getPosition().y + titleSize + (1 * padding)));
    
    sf::Text borderChaseOutline(menuFont);
    CreateText(borderChaseOutline, "Border Chase", 50, sf::Color::Transparent, sf::Vector2f(menuItemsX, menuTitle.getPosition().y + titleSize + (1 * padding)));
    borderChaseOutline.setOutlineColor(sf::Color::Red);
    borderChaseOutline.setOutlineThickness(0.75f);
    
    // create item and outline
    sf::Text optionTwo(menuFont);
    CreateText(optionTwo, "Option Two", 50, sf::Color::White, sf::Vector2f(menuItemsX, borderChase.getPosition().y + optionSize + (2 * padding)));
    sf::Text optionTwoOutline(menuFont);

    CreateText(optionTwoOutline, "Option Two", 50, sf::Color::Transparent, sf::Vector2f(menuItemsX, borderChase.getPosition().y + optionSize + (2 * padding)));
    optionTwoOutline.setOutlineColor(sf::Color::Red);
    optionTwoOutline.setOutlineThickness(0.75f);

    // store in array for display
    sf::Text menuItems[2] = { borderChase, optionTwo };
    


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
        window.draw(borderChase);
        if (borderChaseOutline.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
            window.draw(borderChaseOutline);
        // draw second option check for hovering
        window.draw(optionTwo);
        if (optionTwoOutline.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
            window.draw(optionTwoOutline);

        window.display();
    }
}
