#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

// Game class: Acts as the core game engine, managing window, input, game logic, and rendering
class Game
{
private:
    // Window and Events
    sf::RenderWindow* window;       // Pointer to the game window (dynamically allocated)
    sf::VideoMode videoMode;        // Window resolution and settings
    sf::Event ev;                   // Event object for handling input and window events

    // Mouse Positions
    sf::Vector2i mousePosWindow;    // Mouse position relative to the window (pixels)
    sf::Vector2f mousePosView;      // Mouse position in view coordinates (for game logic)

    // Resources
    sf::Font font;                  // Font for UI text
    sf::Text uiText;                // Text object for displaying points and health

    // Game Logic
    bool endGame;                   // True when game ends (health <= 0)
    int health;                     // Player health, decreases when enemies reach bottom
    unsigned points;                // Player score, increases when clicking enemies
    float enemySpawnTimer;          // Timer for spawning new enemies
    float enemySpawnTimerMax;       // Max timer value before spawning an enemy
    int maxEnemies;                 // Maximum number of enemies on screen
    bool mouseHeld;                 // Tracks if left mouse button is held (prevents multi-clicks)

    // Game Objects
    std::vector<sf::RectangleShape> enemies; // Container for all active enemy rectangles
    sf::RectangleShape enemy;                // Prototype enemy (template for spawning)

    // Private Initialization Functions
    void initVariables();       // Initialize game variables (health, points, timers, etc.)
    void initWindow();          // Set up the game window
    void initFonts();           // Load font for UI text
    void initText();            // Configure UI text properties
    void initEnemies();         // Initialize prototype enemy

public:
    // Constructors and Destructor
    Game();                     // Constructor: Initializes game components
    virtual ~Game();            // Destructor: Cleans up dynamic memory (window)

    // Accessors
    const bool running() const; // Check if the game window is open
    const bool getEndGame() const; // Check if the game has ended

    // Game Logic Functions
    void spawnEnemy();          // Spawn a new enemy with random position and type
    void pollEvents();          // Handle window and input events (close, Escape key)
    void update();              // Update game state (input, enemies, text)
    void updateEnemy();         // Update enemy spawning, movement, and clicks
    void updateMousePositions(); // Update mouse position for click detection
    void updateText();          // Update UI text with points and health

    // Rendering Functions
    void render();              // Render all game objects to the window
    void renderEnemy(sf::RenderTarget& target); // Draw all enemies
    void renderText(sf::RenderTarget& target);  // Draw UI text
};