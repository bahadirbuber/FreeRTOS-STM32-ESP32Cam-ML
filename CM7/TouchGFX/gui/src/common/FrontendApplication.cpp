#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/Bitmap.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{
	 uint16_t* const cacheStartAddr = (uint16_t*)0xD0200000;
	 const uint32_t cacheSize = 0x300000; //3 MB, as example
	 Bitmap::setCache(cacheStartAddr, cacheSize,1);
}
