
#include "Loaders/GameWindow.h"
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
            1. make outline move
            2. reset game when outline is caught
            3. make player shoot

        Issues:
            1. 

        Ideas:
            1. sprint for a short amount of time with shift
            2. powerups appearing for a short amount of time
                Powerup Ideas
                a. make shadow larger so you can fit in easier
                b. slow shadow down
                c. make shadow move towards you
            3. aim and shoot powerups with mouse click
            4. have shadow make it harder or easier to fit in
                a. shadow gets smaller/larger
                b. shadow rotates (would require player to be able to rotate head)
          
    */
    
    MainMenu(window, windowDimensions);       
    
}