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
    virtual void uart_Data (unsigned char *data);

    virtual void decodeJPG_();
    virtual void setJpegImg_(BitmapId bmpID);
    virtual void setFPS_(uint8_t fps);

protected:
};

#endif // SCREEN1VIEW_HPP
