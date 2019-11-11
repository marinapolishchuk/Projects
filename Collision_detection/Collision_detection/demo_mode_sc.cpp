#include "demo_mode_sc.hpp"

class Ball {
private:
    sf::CircleShape* c;
    float px, py;
    float vx, vy;
public:
    Ball(sf::Color col, float r) : c(new sf::CircleShape) {
        c->setRadius(r);
        c->setFillColor(col);
        c->setOrigin(c->getPosition().x + c->getRadius(), c->getPosition().y + c->getRadius());
        px = c->getPosition().x;
        py = c->getPosition().y;
    }
    ~Ball() {}
    sf::CircleShape getCircle() { return *c; }
    sf::CircleShape* getACircle() { return c; }
    void setPos(float x, float y) {
        px = x; py = y;
        c->setPosition(px, py);
    }
    void setVelocity(float x, float y) { vx = x; vy = y; }
    void update() {
        px = c->getPosition().x;
        py = c->getPosition().y;
        px += vx;
        py += vy;
        c->setPosition(px, py);
    }
    float getRadius() {
        return c->getRadius();
    }
};

float rand_FloatRange(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

DemoModeSc::DemoModeSc() { }

int DemoModeSc::Run(sf::RenderWindow &App) {
    
    sf::Event event;
    bool running = true;
    
    std::vector<Ball> circles;

    int amount_of_circles = 10;

    for (int i = 0; i < amount_of_circles; ++i) {
        Ball c(sf::Color::White, rand() % 40 + 20);
        c.setPos(rand() % (int)(WINDOW_WIDTH - 2 * c.getRadius()) + c.getRadius(), rand() % (int)(WINDOW_HEIGHT - 2 * c.getRadius()) + c.getRadius());
        c.setVelocity(rand_FloatRange(-0.1f, 0.1f), rand_FloatRange(-0.1f, 0.1f));
        circles.push_back(c);
    }
    
    while(running) {
        
        while(App.pollEvent(event)) {
            
            auto vec = sf::Mouse::getPosition(App);
            sf::Vector2f vecf{static_cast<float>(vec.x), static_cast<float>(vec.y)};
            
            switch (event.type) {
                case sf::Event::Closed: {
                    for (int i = 0; i < amount_of_circles; ++i) {
                        delete circles[i].getACircle();
                    }
                    return (-1);
                    break;
                }
                    
            }
            
        }
       
        App.clear(sf::Color::Black);
        for (int i = 0; i < amount_of_circles; ++i) {
            circles[i].update();
        }
        for (int i = 0; i < amount_of_circles; ++i) {
            App.draw(circles[i].getCircle());
        }
        App.display();
        
    }
    return (-1);
    
}
