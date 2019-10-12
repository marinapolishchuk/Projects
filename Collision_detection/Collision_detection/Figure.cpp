//
//  Figure.cpp
//  Collision_detection
//
//  Created by  Марина on 10/12/19.
//  Copyright © 2019 Marina Polishchuk. All rights reserved.
//

#include "Figure.hpp"

Figure::~Figure() {}

Circle::Circle() : type(Figure::FigureType::Circle) {}

void Circle::setCircle(sf::CircleShape& c) {
    this->circle = c;
}

sf::CircleShape& Circle::getCircle() { return circle; }

Rectangle::Rectangle() : type(Figure::FigureType::Rectangle) {}

void Rectangle::setRect(sf::RectangleShape& r) {
    this->rect = r;
}

sf::RectangleShape& Rectangle::getRect() { return rect; }
