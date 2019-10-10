#include "start_menu_sc.hpp"

StartMenuSc::StartMenuSc() { }

int StartMenuSc::Run(sf::RenderWindow &App) {
    
    sf::Event event;
    bool running = true;
    
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
    
    while(running) {
        
        while(App.pollEvent(event)) {
            
            auto vec = sf::Mouse::getPosition(App);
            sf::Vector2f vecf{static_cast<float>(vec.x), static_cast<float>(vec.y)};
            
            switch (event.type) {
                    
                case sf::Event::Closed: {
                    return (-1);
                    break;
                }
                    
                case sf::Event::MouseMoved: {
                    
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
                    
                case sf::Event::MouseButtonPressed: {
                    
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        
                        if(exit_button.getGlobalBounds().contains(vecf)) {
                            return (-1);
                        }
                        
                        if(start_button.getGlobalBounds().contains(vecf)) {
                            return 1;
                        }
                        
                    }
                    break;
                }
                    
            }
        
        }
        
        App.clear(sf::Color::Black);
        App.draw(heading);
        App.draw(start_button);
        App.draw(exit_button);
        App.display();
        
    }
    return (-1);
}
