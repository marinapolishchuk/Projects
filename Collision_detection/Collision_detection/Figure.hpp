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
    virtual FigureType getType();
};

class Circle : public Figure {
private:
    sf::CircleShape circle;
public:
    Circle();
    void setCircle(sf::CircleShape&);
    virtual FigureType getType() override;
    sf::CircleShape& getCircle();
};

class Rectangle : public Figure {
private:
    sf::RectangleShape rect;
public:
    Rectangle();
    void setRect(sf::RectangleShape&);
    virtual FigureType getType() override;
    sf::RectangleShape& getRect();
};

//class Triangle : public Figure {
//private:
//    Figure::FigureType type;
//public:
//    Triangle() : type(Figure::FigureType::Triangle) {}
//};

#endif /* Figure_hpp */
