#include "demo_mode_sc.hpp"

DemoModeSc::DemoModeSc() { }

int DemoModeSc::Run(sf::RenderWindow &App) {
    
    sf::Event event;
    bool running = true;
    
    std::vector<sf::CircleShape> circles;
    
    int amount_of_circles = 10;
    
    for (int i = 0; i < amount_of_circles; ++i) {
        sf::CircleShape c;
        c.setFillColor(sf::Color::White);
        c.setRadius(rand() % 40 + 10);
        c.setOrigin(c.getPosition().x + c.getRadius(), c.getPosition().y + c.getRadius());
        c.setPosition(rand() % (int)(WINDOW_WIDTH - 2 * c.getRadius()) + c.getRadius(), rand() % (int)(WINDOW_HEIGHT - 2 * c.getRadius()) + c.getRadius());
        circles.push_back(c);
    }
    
    
    
    while(running) {
        
        while(App.pollEvent(event)) {
            
            auto vec = sf::Mouse::getPosition(App);
            sf::Vector2f vecf{static_cast<float>(vec.x), static_cast<float>(vec.y)};
            
            switch (event.type) {
                case sf::Event::Closed: {
                    return (-1);
                    break;
                }
                    
                    
            }
            
        }
        
        App.clear(sf::Color::Black);
        for (auto &a : circles) {
            App.draw(a);
        }
        App.display();
        
    }
    return (-1);
    
}
