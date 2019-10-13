#include "cFigure.hpp"

Figure::~Figure() {}

Figure::FigureType Figure::getType() {}

Circle::Circle() {}

void Circle::setCircle(sf::CircleShape& c) {
    this->circle = c;
}

Figure::FigureType Circle::getType() { return FigureType::Circle; }

sf::CircleShape& Circle::getCircle() { return circle; }

Rectangle::Rectangle() {}

void Rectangle::setRect(sf::RectangleShape& r) {
    this->rect = r;
}

Figure::FigureType Rectangle::getType() { return FigureType::Rectangle; }

sf::RectangleShape& Rectangle::getRect() { return rect; }
