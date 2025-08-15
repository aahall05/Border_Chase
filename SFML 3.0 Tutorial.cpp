
#include "Loaders/GameWindow.h"
#include "Loaders/SpriteHandler.h"
#include "Loaders/HelperFunctions.h"
#include "Games/MainMenu.h"
#include "Games/BorderChase.h"




#include <iostream>
#include <SFML/Graphics.hpp>
//#include <algorithm>

int main()
{
    // create window
    GameWindow gameWindow;
    sf::RenderWindow& window = gameWindow.getWindow();
    const sf::Vector2i& pos = gameWindow.getCenteredPosition();
    sf::Vector2f windowDimensions(window.getSize().x,window.getSize().y);

    
    /*
        TODO:
            1. add chevron
                1a. make it move around character
                1b. make it fire in direction of mouse
            2. 
            3. 

        Issues:
            1.

        Ideas:
            1. sprint for a short amount of time with shift
            2. powerups appearing for a short amount of time
            3. aim and shoot powerups with mouse click
            4. have shadow make it harder to fit in
                4a. shadow gets smaller/larger
                4b. shadow rotates (would require player to be able to rotate head)
          
    */
    
    MainMenu(window, windowDimensions);       
    
}