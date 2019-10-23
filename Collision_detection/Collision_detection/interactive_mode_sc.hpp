#ifndef interactive_mode_sc_hpp
#define interactive_mode_sc_hpp

#include "cScene.hpp"
#include "cFigure.hpp"
#include "fCollision.cpp"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500
#define FONT_PATH "Resourses/novem___.ttf"


class IntModeSc : public cScene {
public:
    IntModeSc();
    virtual int Run(sf::RenderWindow &App);
};

#endif /* interactive_mode_sc_hpp */
