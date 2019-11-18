#include "demo_mode_sc.hpp"

float rand_FloatRange(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

class Ball : public sf::Drawable {
private:
    sf::CircleShape* c;
    float px, py;
    float vx, vy;
    
    void init() {
        c->setRadius(rand() % 40 + 20);
        c->setFillColor(sf::Color::White);
        c->setOrigin(c->getPosition().x + c->getRadius(), c->getPosition().y + c->getRadius());
        c->setPosition(rand() % (int)(WINDOW_WIDTH - 2 * c->getRadius()) + c->getRadius(), rand() % (int)(WINDOW_HEIGHT - 2 * c->getRadius()) + c->getRadius());
        vx = rand_FloatRange(-0.1f, 0.1f);
        vy = rand_FloatRange(-0.1f, 0.1f);
        px = c->getPosition().x;
        py = c->getPosition().y;
        
    }
public:
    //constructor, destructor
    Ball() : c(new sf::CircleShape) { init(); }
    Ball(const Ball& other)
    {
        c = new sf::CircleShape(*(other.c));
        px = other.px;
        py = other.py;
        vx = other.vx;
        vy = other.vy;
    }
    ~Ball() { delete c; }
    
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override {
        window.draw(*c, states);
    }
    
    //getters
    sf::CircleShape* getCircle() { return c; }
    float getRadius() { return c->getRadius(); }
    
    //update
    void update() {
        px += vx;
        py += vy;
        c->setPosition(px, py);
        
        // no colliding with window borders
//        if (px < 0) { px += WINDOW_WIDTH; }
//        if (px >= WINDOW_WIDTH) { px -= WINDOW_WIDTH; }
//        if (py < 0) { py += WINDOW_HEIGHT; }
//        if (py >= WINDOW_HEIGHT) { py -= WINDOW_HEIGHT; }
        
        
        // collision with window borders
        if ((px - c->getRadius() - 1) < 0) { px += 1; vx = -vx; }
        if ((px + c->getRadius() + 1) > WINDOW_WIDTH) { px -= 1; vx = -vx;}
        if ((py - c->getRadius() - 1) < 0) { py += 1; vy = -vy; }
        if ((py + c->getRadius() + 1) > WINDOW_HEIGHT) { py -= 1; vy = -vy;}
    }
    
};

DemoModeSc::DemoModeSc() { }

int DemoModeSc::Run(sf::RenderWindow &App) {
    
    sf::Event event;
    bool running = true;
    
    std::vector<Ball> circles;

    int amount_of_circles = 10;
    circles.reserve(amount_of_circles);

    for (int i = 0; i < amount_of_circles; ++i) {
        Ball b;
        circles.push_back(b);
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
        for (int i = 0; i < amount_of_circles; ++i) {
            circles[i].update();
        }
        for (int i = 0; i < amount_of_circles; ++i) {
            App.draw(circles[i]);
        }
        App.display();
        
    }
    return (-1);
    
}
