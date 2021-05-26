#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "lab08");

    sf::Clock clock;


    window.setFramerateLimit(60);
    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        std::cout<<elapsed.asMicroseconds()<<"fps: "<<1/elapsed.asSeconds()<<std::endl;



        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }


        // clear the window with black color
        window.clear(sf::Color::Black);
        // draw everything here...

        // end the current frame
        window.display();
    }

    return 0;
}
