#ifndef WORLDWRAPPER_H
#define WORLDWRAPPER_H

#include <Box2D/Box2D.h>

class WorldWrapper
{
private:
    b2World* m_world;
    float m_pixelsPerMeter;
public:
    WorldWrapper(b2World* world);
    b2World* getWorld() const;
    float getPixelsPerMeter() const;
};

#endif // WORLDWRAPPER_H
