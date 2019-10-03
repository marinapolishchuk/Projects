#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#define FONT_PATH "/Users/marina/Desktop/Projects/Collision_detection/Resourses/novem___.ttf"
#define EXIT_TEXTURE_PATH "/Users/marina/Desktop/Projects/Collision_detection/Resourses/exit_button.png"

int main(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(700, 500), "Collision detection", sf::Style::Default);
    
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) { std::cout << "Can't find the font file." << std::endl; }
    
    sf::Text heading("Collision detection", font, 50);
    heading.setColor(sf::Color::White);
    heading.setPosition(109, 100);
    
    sf::Texture exit_texture;
    if (!exit_texture.loadFromFile(EXIT_TEXTURE_PATH)) { std::cout << "Can't find an exit texture image." << std::endl; }
    
    sf::Sprite exit_button(exit_texture);
    exit_button.setPosition(205, 280);
    
    while (window.isOpen()) {
        
        sf::Event event;
        
        while (window.pollEvent(event)) {
            
            switch (event.type) {
                    
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
                    
                default:
                    break;
            }
            
            window.clear(sf::Color::Black);
            window.draw(heading);
            window.draw(exit_button);
            //draw
            window.display();
        }
    }
    
    return EXIT_SUCCESS;
}


