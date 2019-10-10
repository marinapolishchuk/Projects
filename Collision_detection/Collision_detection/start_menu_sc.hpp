#ifndef start_menu_sc_hpp
#define start_menu_sc_hpp

#include <iostream>
#include "cScene.hpp"
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500
#define FONT_PATH "Resourses/novem___.ttf"

class StartMenuSc : public cScene {
public:
    StartMenuSc();
    virtual int Run(sf::RenderWindow &App);
};

#endif /* start_menu_sc_hpp */
