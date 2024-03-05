#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/Utils.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 256;

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

void Screen1View::uart_Data (unsigned char *data){


}
void Screen1View::decodeJPG_(){
}

void Screen1View::setJpegImg_(BitmapId bmpID)
{
    image2.setBitmap(Bitmap(bmpID));
//    image2.setXY(0,0);
    image2.invalidate();
}

void Screen1View::setFPS_(uint8_t fps)
{
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", fps);
	textArea1.invalidate();
}
