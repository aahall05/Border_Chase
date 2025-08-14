#include "GameWindow.h"

GameWindow::GameWindow(float widthFrac, float heightFrac, const std::string& title)
{
    // get current resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // scale window size
    unsigned int windowWidth = static_cast<unsigned int>(desktop.size.x * widthFrac);
    unsigned int windowHeight = static_cast<unsigned int>(desktop.size.y * heightFrac);

    // create window
    window.create(sf::VideoMode({ windowWidth, windowHeight }), title);

    // center window
    centeredPosition = sf::Vector2i(
        static_cast<int>((desktop.size.x - windowWidth) / 2),
        static_cast<int>((desktop.size.y - windowHeight) / 2)
    );

}

sf::RenderWindow& GameWindow::getWindow()
{
	return window;
}

const sf::Vector2i& GameWindow::getCenteredPosition() const
{
	return centeredPosition;
}
