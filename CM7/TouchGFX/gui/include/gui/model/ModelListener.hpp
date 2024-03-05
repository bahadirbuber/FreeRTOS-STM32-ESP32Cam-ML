#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    virtual void uart_Data (unsigned char *data){}

    virtual void _decodeJPG(int totalLength){}
    virtual void _setJpegImg(){}
    virtual void _setFPS(uint8_t fps){}
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
