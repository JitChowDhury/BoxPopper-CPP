#include "Game.h"

// Constructor and Destructor
Game::Game()
{
    // Initialize all game components
    initVariables();
    initWindow();
    initFonts();
    initText();
    initEnemies();
}

Game::~Game()
{
    // Clean up dynamically allocated window to prevent memory leaks
    delete window;
}

// Private Initialization Functions
void Game::initVariables()
{
    // Set initial game state
    window = nullptr;           // Window pointer starts as null
    endGame = false;           // Game is not over at start
    points = 0;                // Initial score
    health = 20;               // Initial player health
    enemySpawnTimerMax = 20.f; // Frames between enemy spawns
    enemySpawnTimer = enemySpawnTimerMax; // Reset spawn timer
    maxEnemies = 5;            // Maximum enemies on screen
    mouseHeld = false;         // Mouse button not held initially
}

void Game::initWindow()
{
    // Configure and create the game window
    videoMode.width = 800;
    videoMode.height = 600;
    // Dynamic allocation for sf::RenderWindow to control lifetime
    window = new sf::RenderWindow(videoMode, "Box-Popper", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60); // Cap at 60 FPS for consistent performance
}

void Game::initFonts()
{
    // Load font for UI text
    font.loadFromFile("Fonts/VarelaRound-Regular.ttf");
}

void Game::initText()
{
    // Set up UI text for displaying points and health
    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::White);
    uiText.setString("None"); // Placeholder text
}

void Game::initEnemies()
{
    // Initialize prototype enemy (template for spawning)
    enemy.setPosition(10.f, 10.f); // Top-left corner
    enemy.setSize(sf::Vector2f(100.f, 100.f)); // Default size
    enemy.setFillColor(sf::Color::Cyan); // Default color
    // Optional: Uncomment to add outline
    // enemy.setOutlineColor(sf::Color::Green);
    // enemy.setOutlineThickness(1.f);
}

// Accessors
const bool Game::running() const
{
    // Check if the game window is open
    return window->isOpen();
}

const bool Game::getEndGame() const
{
    // Check if the game has ended (health <= 0)
    return endGame;
}

// Game Logic Functions
void Game::spawnEnemy()
{
    /*
     * Spawns a new enemy with random position, size, and color.
     * - Sets random x-position within window bounds.
     * - Randomizes enemy type (size and color).
     * - Adds enemy to the enemies vector.
     */
     // Set random x-position to keep enemy fully on-screen
    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
        0.f // Spawn at top
    );

    // Randomize enemy type (0-4)
    int type = rand() % 5;
    switch (type)
    {
    case 0: // Smallest enemy, highest points
        enemy.setSize(sf::Vector2f(10.f, 10.f));
        enemy.setFillColor(sf::Color::Red);
        break;
    case 1:
        enemy.setSize(sf::Vector2f(30.f, 30.f));
        enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        enemy.setSize(sf::Vector2f(50.f, 50.f));
        enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        enemy.setSize(sf::Vector2f(70.f, 70.f));
        enemy.setFillColor(sf::Color::Green);
        break;
    case 4: // Largest enemy, lowest points
        enemy.setSize(sf::Vector2f(100.f, 100.f));
        enemy.setFillColor(sf::Color::Magenta);
        break;
    default: // Fallback (should not occur)
        enemy.setSize(sf::Vector2f(100.f, 100.f));
        enemy.setFillColor(sf::Color::Yellow);
        break;
    }

    // Add the configured enemy to the vector
    enemies.push_back(enemy);
}

void Game::updateEnemy()
{
    /*
     * Updates enemy spawning, movement, and player interaction.
     * - Spawns new enemies if below maxEnemies and timer is ready.
     * - Moves enemies downward.
     * - Removes enemies that reach the bottom (reduces health).
     * - Handles mouse clicks to remove enemies and award points.
     */

     // Update spawn timer and spawn enemies
    if (enemies.size() < maxEnemies)
    {
        if (enemySpawnTimer >= enemySpawnTimerMax)
        {
            spawnEnemy();
            enemySpawnTimer = 0.f; // Reset timer
        }
        else
        {
            enemySpawnTimer += 1.f; // Increment timer per frame
        }
    }

    // Move enemies and check for bottom of screen
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        enemies[i].move(0.f, 3.f); // Move down 3 pixels per frame

        // Remove enemy if it passes the bottom of the window
        if (enemies[i].getPosition().y > window->getSize().y)
        {
            enemies.erase(enemies.begin() + i);
            health -= 1; // Decrease health
            std::cout << "Health: " << health << std::endl;
            --i; // Adjust index after erasure
        }
    }

    // Handle mouse clicks
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!mouseHeld) // Process only new clicks
        {
            mouseHeld = true;
            for (size_t i = 0; i < enemies.size(); ++i)
            {
                // Check if mouse click is within enemy bounds
                if (enemies[i].getGlobalBounds().contains(mousePosView))
                {
                    // Award points based on enemy color
                    if (enemies[i].getFillColor() == sf::Color::Magenta)
                        points += 1;
                    else if (enemies[i].getFillColor() == sf::Color::Green)
                        points += 3;
                    else if (enemies[i].getFillColor() == sf::Color::Cyan)
                        points += 5;
                    else if (enemies[i].getFillColor() == sf::Color::Blue)
                        points += 7;
                    else if (enemies[i].getFillColor() == sf::Color::Red)
                        points += 10;

                    std::cout << "Points: " << points << std::endl;
                    enemies.erase(enemies.begin() + i); // Remove clicked enemy
                    break; // Exit loop after removing one enemy
                }
            }
        }
    }
    else
    {
        mouseHeld = false; // Reset when mouse is released
    }
}

void Game::updateMousePositions()
{
    /*
     * Updates mouse position for accurate click detection.
     * - Stores window-relative position (pixels).
     * - Converts to view coordinates for game logic.
     */
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game::updateText()
{
    // Update UI text with current points and health
    std::stringstream ss;
    ss << "Points: " << points << "\n"
        << "Health: " << health << "\n";
    uiText.setString(ss.str());
}

void Game::pollEvents()
{
    // Process window and input events
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close(); // Close window on close button
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window->close(); // Close on Escape key
            break;
        }
    }
}

// Update and Render Functions
void Game::update()
{
    // Main update function: handles events, game logic, and state
    pollEvents();

    if (!endGame)
    {
        updateMousePositions();
        updateText();
        updateEnemy();
    }

    // End game if health reaches zero
    if (health <= 0)
    {
        endGame = true;
    }
}

void Game::render()
{
    /*
     * Renders the game:
     * - Clears previous frame.
     * - Draws enemies and UI text.
     * - Displays the new frame.
     */
    window->clear(); // Clear to black

    // Draw game objects
    renderEnemy(*window);
    renderText(*window);

    window->display(); // Show the rendered frame
}

void Game::renderEnemy(sf::RenderTarget& target)
{
    // Draw all enemies to the render target
    for (auto& e : enemies)
    {
        target.draw(e); // Reference avoids copying sf::RectangleShape
    }
}

void Game::renderText(sf::RenderTarget& target)
{
    // Draw UI text to the render target
    target.draw(uiText);
}