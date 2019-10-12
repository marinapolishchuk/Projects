//
//  Figure.hpp
//  Collision_detection
//
//  Created by  Марина on 10/12/19.
//  Copyright © 2019 Marina Polishchuk. All rights reserved.
//

#ifndef Figure_hpp
#define Figure_hpp

#include <SFML/Graphics.hpp>


class Figure {
public:
    virtual ~Figure();
    enum class FigureType : int {
        Circle,
        Rectangle,
        Triangle
    } type;
};

class Circle : public Figure {
private:
    sf::CircleShape circle;
    Figure::FigureType type;
public:
    Circle();
    void setCircle(sf::CircleShape&);
    sf::CircleShape& getCircle();
};

class Rectangle : public Figure {
private:
    sf::RectangleShape rect;
    Figure::FigureType type;
public:
    Rectangle();
    void setRect(sf::RectangleShape&);
    sf::RectangleShape& getRect();
};

//class Triangle : public Figure {
//private:
//    Figure::FigureType type;
//public:
//    Triangle() : type(Figure::FigureType::Triangle) {}
//};

#endif /* Figure_hpp */
