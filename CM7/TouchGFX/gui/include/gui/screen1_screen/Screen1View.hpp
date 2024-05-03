#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include "stm32h7xx_hal.h"

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void decodeJPG_();
    virtual void setJpegImg_(BitmapId bmpID);
    virtual void setFPS_(uint8_t fps);
    virtual void drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

protected:
};

#endif // SCREEN1VIEW_HPP
