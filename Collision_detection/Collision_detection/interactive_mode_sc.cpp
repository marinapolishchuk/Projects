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
    
    std::vector<Figure*> figures;
    int figure_clicked_indx = -1;
    
    while(running) {
        
        while(App.pollEvent(event)) {
            
            auto vec = sf::Mouse::getPosition(App);
            sf::Vector2f vecf{static_cast<float>(vec.x), static_cast<float>(vec.y)};
            
            switch (event.type) {
                    
                case sf::Event::Closed: {
                    for (int i = 0; i < figures.size(); ++i) {
                        delete figures[i];
                    }
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
                    
                    for (int i = 0; i < figures.size(); ++i) {
                        
                        if(figures[i]->getType() == Figure::FigureType::Circle) {
                            Circle* c = dynamic_cast<Circle*>(figures[i]);
                            if(c != nullptr && c->getCircle().getGlobalBounds().contains(vecf) && figure_clicked_indx == i) {
                                c->getCircle().setPosition(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
                            }
                        }
                    
                        if(figures[i]->getType() == Figure::FigureType::Rectangle) {
                            Rectangle* r = dynamic_cast<Rectangle*>(figures[i]);
                            if(r != nullptr && r->getRect().getGlobalBounds().contains(vecf) && figure_clicked_indx == i) {
                                r->getRect().setPosition(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
                            }
                        }
                    }

                    break;
                }
                
                case sf::Event::MouseButtonPressed: {
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        
                        if(help_button.getGlobalBounds().contains(vecf)) {
                            tip_clicks++;
                        }
                        
                        for (int i = 0; i < figures.size(); ++i) {
                             if(figures[i]->getType() == Figure::FigureType::Circle) {
                                 Circle* c = dynamic_cast<Circle*>(figures[i]);
                                 if(c != nullptr && c->getCircle().getGlobalBounds().contains(vecf)) {
                                     figure_clicked_indx = i;
                                 }
                             }
                            if(figures[i]->getType() == Figure::FigureType::Rectangle) {
                                Rectangle* r = dynamic_cast<Rectangle*>(figures[i]);
                                if(r != nullptr && r->getRect().getGlobalBounds().contains(vecf)) {
                                    figure_clicked_indx = i;
                                }
                            }
                        }
                    }
                    break;
                }
                    
                case sf::Event::MouseButtonReleased: {
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        for (int i = 0; i < figures.size(); ++i) {
                            figure_clicked_indx = -1;
                        }
                    }
                    break;
                }
                    
                case sf::Event::KeyPressed: {
                    if(event.key.code == sf::Keyboard::C) {
                        sf::CircleShape circle(rand() % 60 + 30);
                        circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
                        circle.setOrigin(circle.getRadius(), circle.getRadius());
                        Circle* c = new Circle;
                        c->setCircle(circle);
                        figures.push_back(c);
                    }
                    if(event.key.code == sf::Keyboard::R) {
                        sf::RectangleShape rect({static_cast<float>(rand() % 40 + 60), static_cast<float>(rand() % 40 + 60)});
                        rect.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
                        rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
                        Rectangle* r = new Rectangle;
                        r->setRect(rect);
                        figures.push_back(r);
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
        for (int i = 0; i < figures.size(); ++i) {
            if(figures[i]->getType() == Figure::FigureType::Circle) {
                Circle* c = dynamic_cast<Circle*>(figures[i]);
                if(c != nullptr) { App.draw(c->getCircle()); }
            }
            if(figures[i]->getType() == Figure::FigureType::Rectangle) {
                Rectangle* r = dynamic_cast<Rectangle*>(figures[i]);
                if(r != nullptr) { App.draw(r->getRect()); }
            }
        }
        App.display();
    }
}
