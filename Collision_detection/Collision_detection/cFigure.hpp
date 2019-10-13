#ifndef cFigure_hpp
#define cFigure_hpp

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

#endif /* cFigure_hpp */
