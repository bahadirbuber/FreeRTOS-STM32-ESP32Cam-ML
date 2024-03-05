#ifndef MODEL_HPP
#define MODEL_HPP
#include <stdint.h>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void decodeJPG(int totalLength);
    void setJpegImg();
    void setFPS(uint8_t fps);
protected:
    ModelListener* modelListener;
    unsigned char RData[256];
};

#endif // MODEL_HPP
