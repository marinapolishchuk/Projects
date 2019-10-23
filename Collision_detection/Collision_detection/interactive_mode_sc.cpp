#include "interactive_mode_sc.hpp"
#include <cmath>
//#include "ImGui/imgui.h"
//#include "ImGui/imgui-SFML.h"

IntModeSc::IntModeSc() { }

void createButton(sf::Text &text, sf::Color color, sf::Vector2f origin, sf::Vector2f pos) {
    text.setFillColor(color);
    text.setOrigin(origin);
    text.setPosition(pos);
}

void changeScaleIfMouseOnButton(sf::Text& button, const sf::Vector2f& mouse_pos) {
    if(button.getGlobalBounds().contains(mouse_pos)) {
        button.setScale(0.9, 0.9);
    }
    if(!button.getGlobalBounds().contains(mouse_pos)) {
        button.setScale(1, 1);
    }
}

int IntModeSc::Run(sf::RenderWindow &App) {
    
    sf::Event event;
    bool running = true;
    
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) { std::cout << "Can't find the font file." << std::endl; }
    
    sf::Text help_button("?", font, 30);
    createButton(help_button, sf::Color::White, {help_button.getLocalBounds().width, 0}, {WINDOW_WIDTH - 15, 5});
    
    sf::Text c_tip("Press C to draw a circle.", font, 15);
    createButton(c_tip, sf::Color::White, {c_tip.getLocalBounds().width, 0}, {WINDOW_WIDTH - 15, 40});
    
    sf::Text r_tip("Press R to draw a rectangle.", font, 15);
    createButton(r_tip, sf::Color::White, {r_tip.getLocalBounds().width, 0}, {WINDOW_WIDTH - 15, 65});
    
    sf::Text t_tip("Press T to draw a triangle.", font, 15);
    createButton(t_tip, sf::Color::White, {t_tip.getLocalBounds().width, 0}, {WINDOW_WIDTH - 15, 90});

    sf::Text window_clear("Clear", font, 25);
    createButton(window_clear, sf::Color::White, {window_clear.getLocalBounds().width / 2, window_clear.getLocalBounds().height / 2}, {WINDOW_WIDTH - 40, WINDOW_HEIGHT - 23});

    sf::Text back_button("Back", font, 25);
    createButton(back_button, sf::Color::White, {back_button.getLocalBounds().width / 2, back_button.getLocalBounds().height / 2}, {WINDOW_WIDTH - 45, WINDOW_HEIGHT - 53});

    int tip_clicks = 0;
    
    std::vector<Figure*> figures;
    int figure_clicked_indx = -1;
    
    const int FIGURES_LIM = 2;
    int figures_count = 0;
    
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
                    changeScaleIfMouseOnButton(help_button, vecf);
                    changeScaleIfMouseOnButton(window_clear, vecf);
                    changeScaleIfMouseOnButton(back_button, vecf);

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
                        
                        if(window_clear.getGlobalBounds().contains(vecf)) {
                            for (int i = 0; i < figures.size(); ++i) {
                                delete figures[i];
                            }
                            figures.clear();
                            figures_count = 0;
                        }
                        
                        if(back_button.getGlobalBounds().contains(vecf)) {
                            return 1;
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
                        if(figures_count < FIGURES_LIM) {
                            sf::CircleShape circle(rand() % 70 + 10);
                            circle.setFillColor(sf::Color::White);
                            circle.setOrigin(circle.getRadius(), circle.getRadius());
                            circle.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                            Circle* c = new Circle;
                            c->setCircle(circle);
                            figures.push_back(c);
                            figures_count++;
                        }
                    }
                    if(event.key.code == sf::Keyboard::R) {
                        if(figures_count < FIGURES_LIM) {
                            sf::RectangleShape rect({static_cast<float>(rand() % 120 + 60), static_cast<float>(rand() % 120 + 60)});
                            rect.setFillColor(sf::Color::White);
                            rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
                            rect.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                            Rectangle* r = new Rectangle;
                            r->setRect(rect);
                            figures.push_back(r);
                            figures_count++;
                        }
                    }
                    break;
                }
            }
        }
        
        if(figures_count == FIGURES_LIM) {
            if(isCollision(figures[0], figures[1])) {
                if(figures[0]->getType() == Figure::FigureType::Circle && figures[1]->getType() == Figure::FigureType::Circle) {
                    Circle* c = dynamic_cast<Circle*>(figures[0]);
                    Circle* d = dynamic_cast<Circle*>(figures[1]);
                    c->getCircle().setFillColor(sf::Color(255, 0, 0, 160));
                    d->getCircle().setFillColor(sf::Color(255, 0, 0, 160));
                }
                if(figures[0]->getType() == Figure::FigureType::Rectangle && figures[1]->getType() == Figure::FigureType::Rectangle) {
                    Rectangle* c = dynamic_cast<Rectangle*>(figures[0]);
                    Rectangle* d = dynamic_cast<Rectangle*>(figures[1]);
                    c->getRect().setFillColor(sf::Color(0, 255, 0, 160));
                    d->getRect().setFillColor(sf::Color(0, 255, 0, 160));
                }
                if(figures[0]->getType() == Figure::FigureType::Circle && figures[1]->getType() == Figure::FigureType::Rectangle) {
                    Circle* c = dynamic_cast<Circle*>(figures[0]);
                    Rectangle* d = dynamic_cast<Rectangle*>(figures[1]);
                    c->getCircle().setFillColor(sf::Color(0, 0, 255, 160));
                    d->getRect().setFillColor(sf::Color(0, 0, 255, 160));
                }
                if(figures[0]->getType() == Figure::FigureType::Rectangle && figures[1]->getType() == Figure::FigureType::Circle) {
                    Rectangle* c = dynamic_cast<Rectangle*>(figures[0]);
                    Circle* d = dynamic_cast<Circle*>(figures[1]);
                    c->getRect().setFillColor(sf::Color(0, 0, 255, 160));
                    d->getCircle().setFillColor(sf::Color(0, 0, 255, 160));
                }
                
            } else {
                if(figures[0]->getType() == Figure::FigureType::Circle && figures[1]->getType() == Figure::FigureType::Circle) {
                    Circle* c = dynamic_cast<Circle*>(figures[0]);
                    Circle* d = dynamic_cast<Circle*>(figures[1]);
                    c->getCircle().setFillColor(sf::Color::White);
                    d->getCircle().setFillColor(sf::Color::White);
                }
                if(figures[0]->getType() == Figure::FigureType::Rectangle && figures[1]->getType() == Figure::FigureType::Rectangle) {
                    Rectangle* c = dynamic_cast<Rectangle*>(figures[0]);
                    Rectangle* d = dynamic_cast<Rectangle*>(figures[1]);
                    c->getRect().setFillColor(sf::Color::White);
                    d->getRect().setFillColor(sf::Color::White);
                }
                if(figures[0]->getType() == Figure::FigureType::Circle && figures[1]->getType() == Figure::FigureType::Rectangle) {
                    Circle* c = dynamic_cast<Circle*>(figures[0]);
                    Rectangle* d = dynamic_cast<Rectangle*>(figures[1]);
                    c->getCircle().setFillColor(sf::Color::White);
                    d->getRect().setFillColor(sf::Color::White);
                }
                if(figures[0]->getType() == Figure::FigureType::Rectangle && figures[1]->getType() == Figure::FigureType::Circle) {
                    Rectangle* c = dynamic_cast<Rectangle*>(figures[0]);
                    Circle* d = dynamic_cast<Circle*>(figures[1]);
                    c->getRect().setFillColor(sf::Color::White);
                    d->getCircle().setFillColor(sf::Color::White);
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
        
        App.draw(window_clear);
        App.draw(back_button);
        
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
