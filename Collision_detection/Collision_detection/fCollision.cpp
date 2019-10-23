#include "cFigure.hpp"
#include <cmath>

static bool isCollision(Figure* figure1, Figure* figure2) {
    
    //both figures are circles
    if(figure1->getType() == Figure::FigureType::Circle && figure2->getType() == Figure::FigureType::Circle) {
        Circle* c1 = dynamic_cast<Circle*>(figure1);
        Circle* c2 = dynamic_cast<Circle*>(figure2);
        
        float dx = std::abs(c1->getCircle().getPosition().x - c2->getCircle().getPosition().x);
        float dy = std::abs(c1->getCircle().getPosition().y - c2->getCircle().getPosition().y);
        
        float dist = sqrt(dx*dx + dy*dy);
        
        float rad_dist = c1->getCircle().getRadius() + c2->getCircle().getRadius();
        
        if(dist <= rad_dist) { return true; }
    }
    
    //both figures are rectangles
    if(figure1->getType() == Figure::FigureType::Rectangle && figure2->getType() == Figure::FigureType::Rectangle) {
        Rectangle* r1 = dynamic_cast<Rectangle*>(figure1);
        Rectangle* r2 = dynamic_cast<Rectangle*>(figure2);
        
        sf::RectangleShape rect1 = r1->getRect();
        sf::RectangleShape rect2 = r2->getRect();
        
        bool c1 = (rect1.getPosition().x - rect1.getSize().x / 2 <= rect2.getPosition().x + rect2.getSize().x / 2);
        bool c2 = (rect1.getPosition().x + rect1.getSize().x / 2 >= rect2.getPosition().x - rect2.getSize().x / 2);
        bool c3 = (rect1.getPosition().y - rect1.getSize().y / 2 <= rect2.getPosition().y + rect2.getSize().y / 2);
        bool c4 = (rect1.getPosition().y + rect1.getSize().y / 2 >= rect2.getPosition().y - rect2.getSize().y / 2);
        
        if (c1 && c2 && c3 && c4) { return true; }
    }
    
    //circle and rectangle
    if(figure1->getType() == Figure::FigureType::Circle && figure2->getType() == Figure::FigureType::Rectangle) {
        Circle* c = dynamic_cast<Circle*>(figure1);
        Rectangle* r = dynamic_cast<Rectangle*>(figure2);
        
        sf::CircleShape circle = c->getCircle();
        sf::RectangleShape rect = r->getRect();
        
        float nearest_x = std::max(rect.getPosition().x - rect.getSize().x / 2, std::min(circle.getPosition().x, rect.getPosition().x + rect.getSize().x / 2));
        float nearest_y = std::max(rect.getPosition().y - rect.getSize().y / 2, std::min(circle.getPosition().y, rect.getPosition().y + rect.getSize().y / 2));
        
        float dist_x = circle.getPosition().x - nearest_x;
        float dist_y = circle.getPosition().y - nearest_y;
        bool condition = (dist_x * dist_x + dist_y * dist_y) < (circle.getRadius() * circle.getRadius());
        
        if (condition) { return true; }
        
    }
    
    //rectangle and circle
    if(figure1->getType() == Figure::FigureType::Rectangle && figure2->getType() == Figure::FigureType::Circle) {
        Circle* c = dynamic_cast<Circle*>(figure2);
        Rectangle* r = dynamic_cast<Rectangle*>(figure1);
        
        sf::CircleShape circle = c->getCircle();
        sf::RectangleShape rect = r->getRect();
        
        float nearest_x = std::max(rect.getPosition().x - rect.getSize().x / 2, std::min(circle.getPosition().x, rect.getPosition().x + rect.getSize().x / 2));
        float nearest_y = std::max(rect.getPosition().y - rect.getSize().y / 2, std::min(circle.getPosition().y, rect.getPosition().y + rect.getSize().y / 2));
        
        float dist_x = circle.getPosition().x - nearest_x;
        float dist_y = circle.getPosition().y - nearest_y;
        bool condition = (dist_x * dist_x + dist_y * dist_y) < (circle.getRadius() * circle.getRadius());
        
        if (condition) { return true; }
    }
    
    return false;
}
