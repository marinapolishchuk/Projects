#ifndef second_menu_sc_hpp
#define second_menu_sc_hpp

#include <iostream>
#include "cScene.hpp"
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500
#define FONT_PATH "Resourses/novem___.ttf"
#define EXIT_TEXTURE_PATH "Resourses/exit_button.png"

class SecondMenuSc : public cScene {
public:
    SecondMenuSc(void);
    virtual int Run(sf::RenderWindow &App);
};

#endif /* second_menu_sc_hpp */
