#ifndef LAYER_H
#define LAYER_H

class Layer
{
public:
    virtual void Render() = 0;
    virtual void Update() = 0;
    virtual void Clean()  = 0;
};

#endif
