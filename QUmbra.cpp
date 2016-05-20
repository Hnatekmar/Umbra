#include "QUmbra.h"

#include <qqml.h>

void QUmbra::registerTypes(const char *uri)
{
    qmlRegisterType<Engine>(uri, 1, 0, "Game");
    qmlRegisterType<Entity>(uri, 1, 0, "Entity");
    qmlRegisterType<Layer>(uri, 1, 0, "Layer");
    qmlRegisterType<Scene>(uri, 1, 0, "Scene");
    qmlRegisterType<PhysicEntity>(uri, 1, 0, "PhysicEntity");
    qmlRegisterType<RectangleFixture>(uri, 1, 0, "RectangleFixture");
    qmlRegisterType<ParticleDefinition>(uri, 1, 0, "ParticleDefinition");
    qmlRegisterUncreatableType<Fixture>(uri, 1, 0, "Fixture", "Base class");
    qmlRegisterType<CircleFixture>(uri, 1, 0, "CircleFixture");
    qmlRegisterType<PolygonFixture>(uri, 1, 0, "PolygonFixture");
    qmlRegisterType<ParticleFlag>(uri, 1, 0, "ParticleFlag");
    qmlRegisterType<DistanceJoint>(uri, 1, 0, "DistanceJoint");
    qmlRegisterType<RevoluteJoint>(uri, 1, 0, "RevoluteJoint");
    qmlRegisterType<PrismaticJoint>(uri, 1, 0, "PrismaticJoint");
    qmlRegisterType<PulleyJoint>(uri, 1, 0, "PulleyJoint");
    qmlRegisterType<FrictionJoint>(uri, 1, 0, "FrictionJoint");
    qmlRegisterType<WheelJoint>(uri, 1, 0, "WheelJoint");
    qmlRegisterType<RaycastResult>(uri, 1, 0, "RaycastResult");
}

