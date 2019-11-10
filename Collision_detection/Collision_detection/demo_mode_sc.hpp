#ifndef demo_mode_sc_hpp
#define demo_mode_sc_hpp

#include "cScene.hpp"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500
#define FONT_PATH "Resourses/novem___.ttf"

class DemoModeSc : public cScene {
public:
    DemoModeSc();
    virtual int Run(sf::RenderWindow &App);
};

#endif /* demo_mode_sc_hpp */
