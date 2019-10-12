//
//  Figure.cpp
//  Collision_detection
//
//  Created by  Марина on 10/12/19.
//  Copyright © 2019 Marina Polishchuk. All rights reserved.
//

#include "Figure.hpp"

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
