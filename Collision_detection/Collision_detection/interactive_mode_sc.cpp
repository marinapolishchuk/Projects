#include "interactive_mode_sc.hpp"

IntModeSc::IntModeSc() { }

int IntModeSc::Run(sf::RenderWindow &App) {
    
    sf::Event event;
    bool running = true;
    
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) { std::cout << "Can't find the font file." << std::endl; }
    
    sf::Text help_button("?", font, 30);
    help_button.setFillColor(sf::Color::White);
    help_button.setOrigin(help_button.getLocalBounds().width, 0);
    help_button.setPosition(WINDOW_WIDTH - 15, 5);
    
    sf::Text c_tip("Press C to draw a circle.", font, 15);
    c_tip.setFillColor(sf::Color::White);
    c_tip.setOrigin(c_tip.getLocalBounds().width, 0);
    c_tip.setPosition(WINDOW_WIDTH - 15, 40);
    
    sf::Text r_tip("Press R to draw a rectangle.", font, 15);
    r_tip.setFillColor(sf::Color::White);
    r_tip.setOrigin(r_tip.getLocalBounds().width, 0);
    r_tip.setPosition(WINDOW_WIDTH - 15, 65);
    
    sf::Text t_tip("Press T to draw a triangle.", font, 15);
    t_tip.setFillColor(sf::Color::White);
    t_tip.setOrigin(t_tip.getLocalBounds().width, 0);
    t_tip.setPosition(WINDOW_WIDTH - 15, 90);
    
    int tip_clicks = 0;

    std::vector<sf::CircleShape> circles;
    int indx_of_clicked = -1;
    std::vector<sf::RectangleShape> rectangles;

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
                    if(help_button.getGlobalBounds().contains(vecf)) {
                        help_button.setScale(0.9, 0.9);
                    }
                    if(!help_button.getGlobalBounds().contains(vecf)) {
                        help_button.setScale(1, 1);
                    }
                    
                    for (int i = 0; i < circles.size(); ++i) {
                        if(circles[i].getGlobalBounds().contains(vecf) && indx_of_clicked == i) {
                            circles[i].setPosition(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
                        }

                    }

                    break;
                }
                
                case sf::Event::MouseButtonPressed: {
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        if(help_button.getGlobalBounds().contains(vecf)) {
                            tip_clicks++;
                        }
                        for (int i = 0; i < circles.size(); ++i) {
                            if(circles[i].getGlobalBounds().contains(vecf)) {
                                indx_of_clicked = i;
                            }
                        }
                    }
                    break;
                }
                    
                case sf::Event::MouseButtonReleased: {
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        for (int i = 0; i < circles.size(); ++i) {
                            indx_of_clicked = -1;
                        }
                    }
                    break;
                }
                    
                case sf::Event::KeyPressed: {
                    if(event.key.code == sf::Keyboard::C) {
                        sf::CircleShape circle(rand() % 60 + 30);
                        circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
                        circle.setOrigin(circle.getRadius(), circle.getRadius());
                        circles.push_back(circle);
                    }
                    break;
                }
                    
            }
        }        
        
        App.clear(sf::Color::Black);
        App.draw(help_button);
        if (tip_clicks % 2 == 1) {
            App.draw(c_tip);
            App.draw(r_tip);
            App.draw(t_tip);
        }
        for (auto &a : circles) {
            App.draw(a);
        }
        App.display();
    }
}
