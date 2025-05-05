#include <SFML/Graphics.hpp>



int main()
{
    //Window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Box-Popper", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;

//Game Loop

    while (window.isOpen())//check if open
    {
        //event polling
        while (window.pollEvent(ev)) // whenever the window gets an event its gonna save it to ev
        {
            switch (ev.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (ev.key.code == sf::Keyboard::Escape)
                     window.close();
                     break;
            }

        }

        //update

        //Render
        window.clear(sf::Color::Red);//clear old frame

        //Draw your game

        window.display();//tell app that window is done drawing
    }
    return 0;
}