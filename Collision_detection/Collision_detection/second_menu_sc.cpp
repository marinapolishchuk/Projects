#include "second_menu_sc.hpp"

SecondMenuSc::SecondMenuSc() {}

int SecondMenuSc::Run(sf::RenderWindow &App) {
    
    sf::Event event;
    bool running = true;
    
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) { std::cout << "Can't find the font file." << std::endl; }
    
    sf::Text heading("Collision detection", font, 55);
    heading.setFillColor(sf::Color::White);
    heading.setOrigin(heading.getLocalBounds().width / 2, heading.getLocalBounds().height / 2);
    heading.setPosition(WINDOW_WIDTH / 2, 140);
    
    sf::Text interactive_mode_button("Interactive mode", font, 45);
    interactive_mode_button.setFillColor(sf::Color::White);
    interactive_mode_button.setOrigin(interactive_mode_button.getLocalBounds().width / 2, interactive_mode_button.getLocalBounds().height / 2);
    interactive_mode_button.setPosition(WINDOW_WIDTH / 2, 260);
    
    sf::Text demo_mode_button("Demonstrative mode", font, 45);
    demo_mode_button.setFillColor(sf::Color::White);
    demo_mode_button.setOrigin(demo_mode_button.getLocalBounds().width / 2, demo_mode_button.getLocalBounds().height / 2);
    demo_mode_button.setPosition(WINDOW_WIDTH / 2, 330);
    
    sf::Text back_button("Back", font, 45);
    back_button.setFillColor(sf::Color::White);
    back_button.setOrigin(back_button.getLocalBounds().width / 2, back_button.getLocalBounds().height / 2);
    back_button.setPosition(WINDOW_WIDTH / 2, 400);

    
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
                    
                    if (interactive_mode_button.getGlobalBounds().contains(vecf)) {
                        interactive_mode_button.setScale(0.9, 0.9);
                    }
                    if (demo_mode_button.getGlobalBounds().contains(vecf)) {
                        demo_mode_button.setScale(0.9, 0.9);
                    }
                    if (back_button.getGlobalBounds().contains(vecf)) {
                        back_button.setScale(0.9, 0.9);
                    }
                    if (!interactive_mode_button.getGlobalBounds().contains(vecf)) {
                        interactive_mode_button.setScale(1, 1);
                    }
                    if (!demo_mode_button.getGlobalBounds().contains(vecf)) {
                        demo_mode_button.setScale(1, 1);
                    }
                    if (!back_button.getGlobalBounds().contains(vecf)) {
                        back_button.setScale(1, 1);
                    }
                    break;
                }
                    
                case sf::Event::MouseButtonPressed: {
                    
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        
                        if(interactive_mode_button.getGlobalBounds().contains(vecf)) {
                            return 2; 
                        }
                        
                        if(demo_mode_button.getGlobalBounds().contains(vecf)) {
                            return (-1); //temporarily
                        }
                        
                        if(back_button.getGlobalBounds().contains(vecf)) {
                            return 0;
                        }
                    }
                    break;
                }
                    
            }
            
        }
        
        App.clear(sf::Color::Black);
        App.draw(heading);
        App.draw(interactive_mode_button);
        App.draw(demo_mode_button);
        App.draw(back_button);
        App.display();

    }
    return (-1);
}
