#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/Utils.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


uint8_t first = 1;
//uint32_t index = 0;
extern BitmapId bmpId;
const int width = 480;
const int height = 272;
extern DMA_HandleTypeDef hdma_memtomem_dma1_stream2;
int offset;


Screen1View::Screen1View()
{
	

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::decodeJPG_(){
}

void Screen1View::setJpegImg_(BitmapId bmpID)
{
    image2.setBitmap(Bitmap(bmpID));
//    image2.setXY(0,0);
    image2.invalidate();
}
void Screen1View::drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t  height)
{							//(163,5, 312, 375)
//https://github.com/junkluis/SmartScaleIOT/blob/master/SmartScale/touchgfx/framework/source/touchgfx/widgets/canvas/Line.cpp
	lineLeft.setPosition(x-5,y,10,height);
	lineLeft.setStart(5, 0);
	lineLeft.setEnd(CWRUtil::toQ5<uint16_t>(5), (CWRUtil::toQ5<uint16_t>(height)));


	lineTop.setPosition(x,
						y,
						width,
						10);
	lineTop.setStart(0, 5);
	lineTop.setEnd(CWRUtil::toQ5<uint16_t>(x+width),CWRUtil::toQ5<uint16_t>(5));

	lineRight.setPosition(x+width-5,
					      y,
						  10,
						  height);
	lineRight.setStart(5, 0);
	lineRight.setEnd(CWRUtil::toQ5<uint16_t>(5),CWRUtil::toQ5<uint16_t>(height));

	lineBottom.setPosition(x,y+height-5,width,10);
	lineBottom.setStart(0, 5);
	lineBottom.setEnd(CWRUtil::toQ5<uint16_t>(x+width),CWRUtil::toQ5<uint16_t>(5));

	lineBottom.invalidate();
	lineRight.invalidate();
	lineTop.invalidate();
	lineLeft.invalidate();
}


void Screen1View::setFPS_(uint8_t fps)
{
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", fps);
	textArea1.invalidate();
}

