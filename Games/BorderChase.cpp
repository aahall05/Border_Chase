#include "BorderChase.h"


void BorderChase(sf::RenderWindow& window, sf::Vector2f windowDimensions)
{
    // scale constants
    sf::Vector2f spriteScale(1, 1);
    sf::Vector2f chevScale(0.5, 0.5);

    // create player sprite
    sf::Texture playerTexture("Images/playerFace.png");
    sf::Sprite player = LoadPlayer(playerTexture, spriteScale);
    
    // create chevron
    sf::Texture chevronTexture("Images/chevron.png");
    sf::Sprite chevronSprite = LoadChevron(chevronTexture, chevScale, player);

    // set distance from sprite using half of sprite radius plus some padding
    sf::Vector2f chevRadius((player.getTexture().getSize().x * spriteScale.x / 2) + 20, (player.getTexture().getSize().y * spriteScale.y / 2) + 20);
    
    // load enemy
    sf::Texture enemyTexture("Images/playerFace_outline.png");
    sf::Sprite enemy = LoadEnemy(enemyTexture, windowDimensions, spriteScale);
    
    // clock for controlled movement
    sf::Clock clock;

    // playable area boundry variables for player
    // window size - half of sprite size determines largest x or y value to prevent moving off screen 
    sf::Vector2f maxPlayableArea_player(windowDimensions.x - ((player.getTexture().getSize().x * spriteScale.x) / 2), windowDimensions.y - ((player.getTexture().getSize().y * spriteScale.y) / 2));
    sf::Vector2f minPlayableArea_player(((player.getTexture().getSize().x * spriteScale.x) / 2), ((player.getTexture().getSize().y * spriteScale.y) / 2));
    
    // playable area boundry variables for enemy
    sf::Vector2f maxPlayableArea_enemy(windowDimensions.x - ((enemy.getTexture().getSize().x * spriteScale.x) / 2), windowDimensions.y - ((enemy.getTexture().getSize().y * spriteScale.y) / 2));
    sf::Vector2f minPlayableArea_enemy(((enemy.getTexture().getSize().x * spriteScale.x) / 2), ((enemy.getTexture().getSize().y * spriteScale.y) / 2));

    // initialize random angle generator
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 2 * M_PI);
    
    // get random angle and its x and y components
    float randomangle = distrib(gen);
    float x = std::cos(randomangle);
    float y = std::sin(randomangle);
    sf::Vector2f enemyDirection(x, y);
    enemyDirection = enemyDirection.normalized();
    
    
    float playerSpeed = 150.0f;
    float enemySpeed = 500.0f;

    while (window.isOpen())
    {        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
       
        float sprint = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            break;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
            sprint = 100;

        // get time since last frame
        sf::Time timeSinceLastFrame = clock.restart();
        
        // move player based on time and speed
        player.move(PlayerMovement(player, minPlayableArea_player, maxPlayableArea_player) * timeSinceLastFrame.asSeconds() * (playerSpeed + sprint));
        // rotate chevron
        chevronSprite.setRotation(sf::radians(ChevRotation(window, player, chevronSprite, chevRadius)));
        // move enemy
        enemyDirection = EnemyMovement(enemy.getPosition(), enemyDirection, minPlayableArea_enemy, maxPlayableArea_enemy);
        enemy.move(enemyDirection * timeSinceLastFrame.asSeconds() * enemySpeed);

        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.draw(chevronSprite);
        window.display();

    }
}

sf::Sprite& LoadPlayer(sf::Texture& playerTexture, sf::Vector2f scale)
{    
    // create player sprite 
    sf::Sprite player(playerTexture);
    // get position (top left corner)
    sf::Vector2f playerPosition(sf::Vector2f((player.getTexture().getSize().x * scale.x) / 2, (player.getTexture().getSize().y * scale.y) / 2));
    // set position, scale, and origin
    scalePosOrig(player, playerPosition, scale);

    return player;
}

sf::Sprite& LoadChevron(sf::Texture& chevronTexture, sf::Vector2f scale, sf::Sprite& player)
{
    // create chevron sprite
    sf::Sprite chevronSprite(chevronTexture);
    sf::Vector2f chevPosition(player.getPosition().x, player.getPosition().y + 50);
    
    chevronSprite.setScale(scale);
    chevronSprite.setOrigin(sf::Vector2f(chevronSprite.getTexture().getSize().x / 2, chevronSprite.getTexture().getSize().y / 2));
    chevronSprite.setColor(sf::Color::Green);

    return chevronSprite;
}

sf::Sprite& LoadEnemy(sf::Texture& enemyTexture, sf::Vector2f windowDimensions, sf::Vector2f scale)
{
    // create enemy sprite
    sf::Sprite enemy(enemyTexture);
    // get position (center of screen)
    sf::Vector2f enemyPosition(windowDimensions.x / 2, windowDimensions.y / 2);
    // set position, scale, and origin
    scalePosOrig(enemy, enemyPosition, scale);

    return enemy;
}

void scalePosOrig(sf::Sprite& sprite, sf::Vector2f position, sf::Vector2f scale)
{
    sprite.setPosition(position);
    sprite.setScale(scale);
    sprite.setOrigin(sf::Vector2f(sprite.getTexture().getSize().x / 2, sprite.getTexture().getSize().y / 2));
}

sf::Vector2f PlayerMovement(sf::Sprite& player, sf::Vector2f& minPlayableArea_player, sf::Vector2f& maxPlayableArea_player)
{
    // get player movement
    sf::Vector2f vRequestedPlayerMovement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        if (player.getPosition().y > minPlayableArea_player.y)
            vRequestedPlayerMovement += sf::Vector2f(0.0f, -1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        if (player.getPosition().x > minPlayableArea_player.x)
            vRequestedPlayerMovement += sf::Vector2f(-1.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        if (player.getPosition().y < maxPlayableArea_player.y)
            vRequestedPlayerMovement += sf::Vector2f(0.0f, 1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (player.getPosition().x < maxPlayableArea_player.x)
            vRequestedPlayerMovement += sf::Vector2f(1.0f, 0.0f);
    }
    return vRequestedPlayerMovement;
}

float ChevRotation(sf::RenderWindow& window, sf::Sprite& player, sf::Sprite& chevronSprite, sf::Vector2f chevRadius)
{
    // get mouse position
    sf::Vector2f vMousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
    // get vector from sprite to cursor
    sf::Vector2f vPlayerToChev = vMousePosition - player.getPosition();
    // restrict chevron movement to orbit player
    chevronSprite.setPosition(player.getPosition() + vPlayerToChev.normalized().componentWiseMul(chevRadius));
    // get angle from player to mouse and rotate chevron
    return std::atan2(vPlayerToChev.y, vPlayerToChev.x) + M_PI_2;  
    
}

sf::Vector2f EnemyMovement(sf::Vector2f position, sf::Vector2f direction, sf::Vector2f& minPlayableArea_enemy, sf::Vector2f& maxPlayableArea_enemy)
{
    if (position.x <= minPlayableArea_enemy.x || position.x >= maxPlayableArea_enemy.x)
        direction.x *= -1.0f;

    if (position.y <= minPlayableArea_enemy.y || position.y >= maxPlayableArea_enemy.y)
        direction.y *= -1.0f;

    return direction;
}