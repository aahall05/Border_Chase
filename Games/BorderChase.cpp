#include "BorderChase.h"

void BorderChase(sf::RenderWindow& window, sf::Vector2f windowDimensions)
{
    // scale constants
    sf::Vector2f spriteScale(1, 1);
    sf::Vector2f chevScale(0.5, 0.5);

    // load player texture
    sf::Texture playerTexture;
    std::string playerPath = "Images/playerFace.png";
    playerTexture.loadFromFile(playerPath);

    // create player sprite 
    sf::Sprite player(playerTexture);
    // get position (top left corner)
    sf::Vector2f playerPosition(sf::Vector2f((player.getTexture().getSize().x * spriteScale.x) / 2, (player.getTexture().getSize().y * spriteScale.y) / 2));
    // set position, scale, and origin
    scalePosOrig(player, playerPosition, spriteScale);

    // load enemy texture
    sf::Texture enemyTexture;
    std::string enemyPath = "Images/playerFace_outline.png";
    enemyTexture.loadFromFile(enemyPath);

    // create enemy sprite
    sf::Sprite enemy(enemyTexture);
    // get position (center of screen)
    sf::Vector2f enemyPosition(windowDimensions.x / 2, windowDimensions.y / 2);
    // set position, scale, and origin
    scalePosOrig(enemy, enemyPosition, spriteScale);

    // load chevron texture
    sf::Texture chevronTexture;
    std::string chevronPath = "Images/chevron.png";
    chevronTexture.loadFromFile(chevronPath);

    // create chevron sprite
    sf::Sprite chevronSprite(chevronTexture);
    sf::Vector2f chevPosition(playerPosition.x, playerPosition.y + 50);
    
    chevronSprite.setScale(chevScale);
    chevronSprite.setOrigin(sf::Vector2f(chevronSprite.getTexture().getSize().x / 2, chevronSprite.getTexture().getSize().y / 2));
    chevronSprite.setColor(sf::Color::Green);
    // set distance from sprite using half of sprite radius plus some padding
    sf::Vector2f chevRadius((player.getTexture().getSize().x * spriteScale.x / 2) + 20, (player.getTexture().getSize().y * spriteScale.y / 2) + 20);
    

    // clock for controlled movement
    sf::Clock clock;

    // variables for playable area taking in to account for sprite size
    // window size - half of sprite size determines largest x or y value to prevent moving off screen 
    sf::Vector2f maxPlayableArea(windowDimensions.x - ((player.getTexture().getSize().x * spriteScale.x) / 2), windowDimensions.y - ((player.getTexture().getSize().y * spriteScale.y) / 2));
    sf::Vector2f minPlayableArea(0 + ((player.getTexture().getSize().x * spriteScale.x) / 2), 0 + ((player.getTexture().getSize().y * spriteScale.y) / 2));

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            break;

        sf::Time timeSinceLastFrame = clock.restart();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // get player movement
        sf::Vector2f vRequestedPlayerMovement(0.0f, 0.0f);
        float speed = 150.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            // only move up if 
            if (player.getPosition().y > minPlayableArea.y)
                vRequestedPlayerMovement += sf::Vector2f(0.0f, -1.0f);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            if (player.getPosition().x > minPlayableArea.x)
                vRequestedPlayerMovement += sf::Vector2f(-1.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            if (player.getPosition().y < maxPlayableArea.y)
                vRequestedPlayerMovement += sf::Vector2f(0.0f, 1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if (player.getPosition().x < maxPlayableArea.x)
                vRequestedPlayerMovement += sf::Vector2f(1.0f, 0.0f);
        }

        player.move(vRequestedPlayerMovement * timeSinceLastFrame.asSeconds() * speed);

        // get mouse position
        sf::Vector2f vMousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
        // get vector from sprite to cursor
        sf::Vector2f vPlayerToChev = vMousePosition - player.getPosition();
        
        chevronSprite.setPosition(player.getPosition() + vPlayerToChev.normalized().componentWiseMul(chevRadius));
        
        chevronSprite.setRotation(sf::degrees(180));
        
        //std::cout << player.getPosition().angleTo(vMousePosition).asDegrees() << ", ";


        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.draw(chevronSprite);
        window.display();

    }
}
