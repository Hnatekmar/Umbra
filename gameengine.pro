TEMPLATE = lib
TARGET = $$qtLibraryTarget(umbraplugin)
QT += qml quick
CONFIG += qt plugin c++11
URI = Umbra

DESTDIR = Umbra
uri = Umbra

# Input
SOURCES += \
    Engine.cpp \
    Entity.cpp \
    EntityManager.cpp \
    Layer.cpp \
    Scene.cpp \
    Physics/PhysicEntity.cpp \
    Physics/Fixture.cpp \
    QUmbra.cpp \
    Physics/WorldWrapper.cpp \
    Physics/Joint.cpp \
    Physics/DistanceJoint.cpp \
    Physics/RevoluteJoint.cpp \
    Physics/PrismaticJoint.cpp \
    Physics/PulleyJoint.cpp \
    Physics/GearJoint.cpp \
    Physics/WheelJoint.cpp \
    Physics/WeldJoint.cpp \
    Physics/FrictionJoint.cpp \
    Physics/RopeJoint.cpp \
    Physics/CircleFixture.cpp \
    Physics/RectangleFixture.cpp \
    Physics/ParticleDefinition.cpp \
    Physics/PolygonFixture.cpp

HEADERS += \
    Engine.h \
    Entity.h \
    EntityManager.h \
    Layer.h \
    Scene.h \
    Physics/PhysicEntity.h \
    Physics/Fixture.h \
    QUmbra.h \
    Physics/WorldWrapper.h \
    Physics/Joint.h \
    Physics/DistanceJoint.h \
    Physics/RevoluteJoint.h \
    Physics/PrismaticJoint.h \
    Physics/PulleyJoint.h \
    Physics/GearJoint.h \
    Physics/WheelJoint.h \
    Physics/WeldJoint.h \
    Physics/FrictionJoint.h \
    Physics/RopeJoint.h \
    Physics/CircleFixture.h \
    Physics/RectangleFixture.h \
    Physics/ParticleDefinition.h \
    Physics/PolygonFixture.h

DISTFILES = \
    Umbra/qmldir \
    Umbra/metadata.json \
    Umbra/particleVertexShader.vsh \
    Umbra/particlefragmentshader.fsh

# liquidfun

LIBS += -L $$PWD/Box2D_Build/Box2D/ -lliquidfun
INCLUDEPATH += $$PWD/liquidfun/liquidfun/Box2D

CONFIG(release, debug|release){
        DEFINES += QT_NO_DEBUG_OUTPUT
#        QMAKE_CXXFLAGS_RELEASE += -gstrict-dwarf -gdwarf-2 -fno-omit-frame-pointer
#        QMAKE_CFLAGS_RELEASE += -gstrict-dwarf -gdwarf-2 -fno-omit-frame-pointer
}
