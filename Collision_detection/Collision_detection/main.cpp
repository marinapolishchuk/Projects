#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#define FONT_PATH "Resourses/novem___.ttf"
#define EXIT_TEXTURE_PATH "Resourses/exit_button.png"
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500


int main(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Collision detection", sf::Style::Default);
    
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) { std::cout << "Can't find the font file." << std::endl; }
    
    sf::Text heading("Collision detection", font, 55);
    heading.setFillColor(sf::Color::White);
    heading.setOrigin(heading.getLocalBounds().width / 2, heading.getLocalBounds().height / 2);
    heading.setPosition(WINDOW_WIDTH / 2, 140);
    
    sf::Text start_button("Start", font, 45);
    start_button.setFillColor(sf::Color::White);
    start_button.setOrigin(start_button.getLocalBounds().width / 2, start_button.getLocalBounds().height / 2);
    start_button.setPosition(WINDOW_WIDTH / 2, 280);
    
    sf::Text exit_button("Exit", font, 45);
    exit_button.setFillColor(sf::Color::White);
    exit_button.setOrigin(exit_button.getLocalBounds().width / 2, exit_button.getLocalBounds().height / 2);
    exit_button.setPosition(WINDOW_WIDTH / 2, 350);
    
    while (window.isOpen()) {
        
        sf::Event event;
        
        while (window.pollEvent(event)) {
            
            switch (event.type) {
                    
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
                    
                case sf::Event::MouseMoved: {
                    auto vec = sf::Mouse::getPosition(window);
                    sf::Vector2f vecf{static_cast<float>(vec.x), static_cast<float>(vec.y)};
                    if (exit_button.getGlobalBounds().contains(vecf)) {
                        exit_button.setScale(0.9, 0.9);
                    }
                    if (start_button.getGlobalBounds().contains(vecf)) {
                        start_button.setScale(0.9, 0.9);
                    }
                    if (!exit_button.getGlobalBounds().contains(vecf)) {
                        exit_button.setScale(1, 1);
                    }
                    if (!start_button.getGlobalBounds().contains(vecf)) {
                        start_button.setScale(1, 1);
                    }
                    break;
                }
                    
                default:
                    break;
            }
            
            window.clear(sf::Color::Black);
            window.draw(heading);
            window.draw(start_button);
            window.draw(exit_button);
            window.display();
        }
    }
    
    return EXIT_SUCCESS;
}


