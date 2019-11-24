#include "demo_mode_sc.hpp"
#include <cmath>

float rand_FloatRange(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

class Ball : public sf::Drawable {
private:
    sf::CircleShape* c;
    float px, py;
    float vx, vy;
    float mass;
    
    void init() {
        c->setRadius(rand() % 40 + 20);
        c->setFillColor(sf::Color::White);
        c->setOrigin(c->getPosition().x + c->getRadius(), c->getPosition().y + c->getRadius());
        c->setPosition(rand() % (int)(WINDOW_WIDTH - 2 * c->getRadius()) + c->getRadius(), rand() % (int)(WINDOW_HEIGHT - 2 * c->getRadius()) + c->getRadius());
        vx = rand_FloatRange(-0.08f, 0.08f);
        vy = rand_FloatRange(-0.08f, 0.08f);
        px = c->getPosition().x;
        py = c->getPosition().y;
        mass = c->getRadius() * 10.0f;
        
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
        mass = other.mass;
    }
    ~Ball() { delete c; }
    
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override {
        window.draw(*c, states);
    }
    
    //update
    void update(std::vector<Ball> &circles, sf::Int32 dt) {
        px += vx;
        py += vy;
        c->setPosition(px, py);
        
        // collision with window borders
        if ((px - c->getRadius() - 1) < 0) { px += 1; vx = -vx; }
        if ((px + c->getRadius() + 1) > WINDOW_WIDTH) { px -= 1; vx = -vx;}
        if ((py - c->getRadius() - 1) < 0) { py += 1; vy = -vy; }
        if ((py + c->getRadius() + 1) > WINDOW_HEIGHT) { py -= 1; vy = -vy;}
        
        
        auto isCollision = [](float x1, float y1, float r1, float x2, float y2, float r2) {
            float dx = x1 - x2;
            float dy = y1 - y2;
            float dist = sqrt(dx * dx + dy * dy);
            float rad_dist = r1 + r2;
            return (dist <= rad_dist);
        };
        std::vector<std::pair<Ball*, Ball*>> collisions;
        for (int i = 0; i < circles.size(); ++i) {
            if (&circles[i] != this) {
                if (isCollision(circles[i].px, circles[i].py, circles[i].c->getRadius(), px, py, c->getRadius())) {
                    
                    collisions.push_back({&circles[i], this});
                    
                    float fDist = sqrtf((circles[i].px - px)*(circles[i].px - px) + (circles[i].py - py)*(circles[i].py - py));
                    float fOverlap = 0.5f * (fDist - circles[i].c->getRadius() - c->getRadius());
                    
                    circles[i].px -= fOverlap * (circles[i].px - px) / fDist;
                    circles[i].py -= fOverlap * (circles[i].py - py) / fDist;
                    px += fOverlap * (circles[i].px - px) / fDist;
                    py += fOverlap * (circles[i].py - py) / fDist;
                }
            }
        }
        //collision detection between circles
        for (auto &collision : collisions) {
            auto& a = *(collision.first);
            auto& b = *(collision.second);
            if (&(a.c) != &(b.c)) {
                    float fDist = sqrtf((a.px - b.px)*(a.px - b.px) + (a.py - b.py)*(a.py - b.py));
                
                    float nx = (b.px - a.px) / fDist;
                    float ny = (b.py - a.py) / fDist;
                
                    float tx = -ny;
                    float ty = nx;
                
                    float dpTan1 = a.vx * tx + a.vy * ty;
                    float dpTan2 = b.vx * tx + b.vy * ty;
                
                    float dpNorm1 = a.vx * nx + a.vy * ny;
                    float dpNorm2 = b.vx * nx + b.vy * ny;
                
                    float m1 = (dpNorm1 * (a.mass - b.mass) + 2.0f * b.mass * dpNorm2) / (a.mass + b.mass);
                    float m2 = (dpNorm2 * (b.mass - a.mass) + 2.0f * a.mass * dpNorm1) / (a.mass + b.mass);
                
                    a.vx = tx * dpTan1 + nx * m1;
                    a.vy = ty * dpTan1 + ny * m1;
                    b.vx = tx * dpTan2 + nx * m2;
                    b.vy = ty * dpTan2 + ny * m2;
                }
            }
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
    sf::Clock clock;
    while(running) {
        
        while(App.pollEvent(event)) {
            
            auto vec = sf::Mouse::getPosition(App);
            sf::Vector2f vecf{static_cast<float>(vec.x), static_cast<float>(vec.y)};
            
            switch (event.type) {
                case sf::Event::Closed: {
                    return (-1);
                    break;
                default: break;
                }
                    
            }
            
        }
       
        App.clear(sf::Color::Black);
        for (int i = 0; i < amount_of_circles; ++i) {
            circles[i].update(circles, clock.restart().asMilliseconds());
        }
        for (int i = 0; i < amount_of_circles; ++i) {
            App.draw(circles[i]);
        }
        App.display();
        
    }
    return (-1);
    
}
