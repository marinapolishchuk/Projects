#ifndef cScene_hpp
#define cScene_hpp

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class cScene {
public:
    virtual int Run(sf::RenderWindow &App) = 0;
};

#endif /* cScene_hpp */
