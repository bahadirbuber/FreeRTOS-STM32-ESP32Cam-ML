#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include "image_320_240_jpg.h"
#include "cmsis_os2.h"
extern uint8_t* buffer8;
BitmapId bmpId;
const uint16_t imgwidth=480, imgheight=272;
//#define RAMbufferJPG (0xD0200000+480*(272+1)*3+100)


//extern HardwareMJPEGDecoder mjpegdecoder1;

extern "C" {
	extern osMessageQueueId_t afterJPGDecodeHandle;
	extern osMessageQueueId_t jpgDecodeHandle;
}


Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{
    bmpId = Bitmap::dynamicBitmapCreate(imgwidth, imgheight, Bitmap::ARGB8888);
	buffer8 = Bitmap::dynamicBitmapGetAddress(bmpId);
}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}
void Screen1Presenter::uart_Data (unsigned char *data){
	view.uart_Data (data);
}

void Screen1Presenter::_decodeJPG(int totalLength)
{
	uint8_t semaphNullVal=1;

	osMessageQueuePut(afterJPGDecodeHandle, &semaphNullVal, 0U, 0U);
//		decodeMJPEGFrame(const uint8_t* const mjpgdata, const uint32_t length, uint8_t* outputBuffer, uint16_t bufferWidth, uint16_t bufferHeight, uint32_t bufferStride)
}


void Screen1Presenter::_setJpegImg()
{
	view.setJpegImg_(bmpId);
}
void Screen1Presenter::_setFPS(uint8_t fps)
{
	view.setFPS_(fps);
}
