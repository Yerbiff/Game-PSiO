#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "lab08");

    sf::Clock clock;

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    int rectangle_velocity_x = 200;
    int rectangle_velocity_y = 150;
    int rectangle_angular_velocity = 10;

    window.setFramerateLimit(60);
    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        std::cout<<elapsed.asMicroseconds()<<"fps: "<<1/elapsed.asSeconds()<<std::endl;

        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

                rectangle.move(rectangle_velocity_x * elapsed.asSeconds(), rectangle_velocity_y * elapsed.asSeconds());
                rectangle.rotate(rectangle_angular_velocity* elapsed.asSeconds());
                srand(time(NULL));

                int r = rand()%256;
                int g = rand()%256;
                int b = rand()%256;
                //std::cout<<"r: "<<r<<"g: "<<g<<"b: "<<b<<std::endl;
                if(rectangle_bounds.left + rectangle_bounds.width >= window.getSize().x){
                    rectangle.setFillColor(sf::Color(r,g,b));
                    rectangle_velocity_x = -abs(rectangle_velocity_x);
                }
                else if (rectangle_bounds.left <= 0){
                    rectangle.setFillColor(sf::Color(r,g,b));
                    rectangle_velocity_x = abs(rectangle_velocity_x);
                }
                if(rectangle_bounds.top + rectangle_bounds.height >= window.getSize().y){
                    rectangle.setFillColor(sf::Color(r,g,b));
                    rectangle_velocity_y = -abs(rectangle_velocity_y);
                }
                else if (rectangle_bounds.top <= 0){
                    rectangle.setFillColor(sf::Color(r,g,b));
                    rectangle_velocity_y = abs(rectangle_velocity_y);
                }

        // clear the window with black color
        window.clear(sf::Color::Black);
        // draw everything here...

        window.draw(rectangle);

        // end the current frame
        window.display();
    }

    return 0;
}
