// 4.23.0 0x8c4dad14
// Generated by imageconverter. Please, do not edit!

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_alternate_theme_images_backgrounds_320x240_gradient_light[]; // BITMAP_ALTERNATE_THEME_IMAGES_BACKGROUNDS_320X240_GRADIENT_LIGHT_ID = 0, Size: 320x240 pixels
extern const unsigned char image_glass_theme_images_backgrounds_480x272_burly_layers[]; // BITMAP_GLASS_THEME_IMAGES_BACKGROUNDS_480X272_BURLY_LAYERS_ID = 1, Size: 480x272 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_alternate_theme_images_backgrounds_320x240_gradient_light, 0, 320, 240, 0, 0, 320, ((uint8_t)touchgfx::Bitmap::RGB888) >> 3, 240, ((uint8_t)touchgfx::Bitmap::RGB888) & 0x7 },
    { image_glass_theme_images_backgrounds_480x272_burly_layers, 0, 480, 272, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 272, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
