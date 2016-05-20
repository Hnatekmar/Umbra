#include "WorldWrapper.h"

WorldWrapper::WorldWrapper(b2World *world) : m_world(world),
                                             m_pixelsPerMeter(32.0f)
{
}

b2World *WorldWrapper::getWorld() const
{
    return m_world;
}

float WorldWrapper::getPixelsPerMeter() const
{
    return m_pixelsPerMeter;
}
