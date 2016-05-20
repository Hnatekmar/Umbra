#ifndef UMBRA_H
#define UMBRA_H

#include <QQmlExtensionPlugin>
#include "Engine.h"
#include "Entity.h"
#include "Layer.h"
#include "Scene.h"
#include "Physics/PhysicEntity.h"
#include "Physics/RectangleFixture.h"
#include "Physics/ParticleDefinition.h"
#include "Physics/CircleFixture.h"
#include "Physics/PolygonFixture.h"
#include "Physics/DistanceJoint.h"
#include "Physics/RevoluteJoint.h"
#include "Physics/PrismaticJoint.h"
#include "Physics/PulleyJoint.h"
#include "Physics/WheelJoint.h"
#include "Physics/FrictionJoint.h"
#include "Physics/WheelJoint.h"

class QUmbra : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Umbra")

    void registerTypes(const char *uri) override;
};

#endif // GAMEENGINE_PLUGIN_H

