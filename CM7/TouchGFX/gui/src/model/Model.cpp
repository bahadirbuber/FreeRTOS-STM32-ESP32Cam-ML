#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <HardwareMJPEGDecoder.hpp>

#ifndef SIMULATOR
#include "main.h"
#include "cmsis_os2.h"
#include <string.h>
extern "C" {
	extern osMessageQueueId_t spiQueueHandle;
	extern  osMessageQueueId_t afterJPGDecodeHandle;
	extern  osMessageQueueId_t jpgDecodeHandle;
	extern osMessageQueueId_t FPSQueueHandle;
//	uartData_t *uartData_r;
	//uartData_t *uartData_r;
	extern uint8_t RX_Buffer[256];
}
#endif
uint8_t semaphNVal=0;
uint8_t fps = 0;
int totalLength_;


Model::Model() : modelListener(0)
{

}

void Model::tick()
{
#ifndef SIMULATOR
	if(osMessageQueueGet(FPSQueueHandle, &fps,NULL, 0U)==osOK)
		setFPS(fps);
	if(osMessageQueueGet(afterJPGDecodeHandle, &semaphNVal,NULL, 0U)==osOK)
		setJpegImg();
#endif
}

void Model::decodeJPG(int totalLength){
	modelListener->_decodeJPG(totalLength);
}

void Model::setJpegImg()
{
	modelListener->_setJpegImg();
}

void Model::setFPS(uint8_t fps){
	modelListener->_setFPS(fps);
}
