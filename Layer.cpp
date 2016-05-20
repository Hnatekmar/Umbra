#include "Layer.h"

#include <QSGSimpleMaterialShader>
#include <QSGSimpleRectNode>
#include <QSGVertexColorMaterial>

Layer::Layer(QQuickItem* parent):QQuickItem(parent),
                                 m_started(false),
                                 m_entityManager(),
                                 m_paused(false),
                                 m_particleSystem(nullptr)
{
    setFlag(ItemHasContents);
    m_particleSystem = m_entityManager.getWorld()->getWorld()->CreateParticleSystem(new b2ParticleSystemDef());
    m_particleSystem->SetRadius(2.0f/m_entityManager.getWorld()->getPixelsPerMeter());
}

void Layer::pause()
{
    m_paused = true;
}

void Layer::unPause()
{
    m_paused = false;
}

void Layer::createParticleBox(const QRect &box, ParticleDefinition* definition)
{
    auto def = definition->getParticleGroupDef();
    auto pixelsPerMeter = m_entityManager.getWorld()->getPixelsPerMeter();
    def.position.Set(box.x() / pixelsPerMeter, -box.y() / pixelsPerMeter);
    b2PolygonShape* boxShape = new b2PolygonShape();
    m_particleSystem->SetDestructionByAge(def.lifetime > 0.0);
    boxShape->SetAsBox(box.width() / (pixelsPerMeter * 2.0), box.height() / (pixelsPerMeter * 2.0));
    def.shape = boxShape;
    m_particleSystem->CreateParticleGroup(def);
}

void Layer::createParticleBox(const QRect &box, ParticleDefinition *definition, qreal angle)
{
    auto def = definition->getParticleGroupDef();
    auto pixelsPerMeter = m_entityManager.getWorld()->getPixelsPerMeter();
    def.position.Set(box.x() / pixelsPerMeter, -box.y() / pixelsPerMeter);
    b2PolygonShape* boxShape = new b2PolygonShape();
    m_particleSystem->SetDestructionByAge(def.lifetime > 0.0);
    def.angle = -qDegreesToRadians(angle);
    boxShape->SetAsBox(box.width() / (pixelsPerMeter * 2.0), box.height() / (pixelsPerMeter * 2.0));
    def.shape = boxShape;
    m_particleSystem->CreateParticleGroup(def);
}

void Layer::createParticleCircle(const QPoint &position, qreal radius, ParticleDefinition *definition)
{
    auto def = definition->getParticleGroupDef();
    auto pixelsPerMeter = m_entityManager.getWorld()->getPixelsPerMeter();
    def.position.Set(position.x() / pixelsPerMeter, -position.y() / pixelsPerMeter);
    b2CircleShape* circleShape = new b2CircleShape();
    m_particleSystem->SetDestructionByAge(def.lifetime > 0.0);
    circleShape->m_radius = radius / pixelsPerMeter;
    def.shape = circleShape;
    m_particleSystem->CreateParticleGroup(def);
}

QList<QObject *> Layer::getEntitiesInRect(const QRectF &rect)
{
    return m_entityManager.getEntitiesInRect(rect);
}


RaycastResult* Layer::raycast(QPointF start, QPointF end)
{
    auto world = m_entityManager.getWorld();
    b2Vec2 startPoint;
    startPoint.x = start.x() / m_entityManager.getWorld()->getPixelsPerMeter();
    startPoint.y = -start.y() / m_entityManager.getWorld()->getPixelsPerMeter();
    b2Vec2 endPoint;
    endPoint.x = end.x() / m_entityManager.getWorld()->getPixelsPerMeter();
    endPoint.y = -end.y() / m_entityManager.getWorld()->getPixelsPerMeter();
    NearestCallback callback;
    world->getWorld()->RayCast(&callback, startPoint, endPoint);
    RaycastResult* result = new RaycastResult();
    result->setHitPoint(QPointF(callback.m_point.x * m_entityManager.getWorld()->getPixelsPerMeter(),
                                -callback.m_point.y * m_entityManager.getWorld()->getPixelsPerMeter()));
    if(callback.m_fixture != nullptr)
    {
        if(callback.m_fixture->GetBody() != nullptr)
        {
            PhysicEntity* entity = static_cast<PhysicEntity*>(callback.m_fixture->GetBody()->GetUserData());
            result->setEntity(entity);
        }
    }
    return result;
}

void Layer::handleAddedItem(QQuickItem* item)
{
    Entity* entity = dynamic_cast<Entity*>(item);
    if(entity != nullptr)
    {
        qDebug() << "Pridavam novou entitu" << entity->getID();
        m_entityManager.add(entity);
        PhysicEntity* pEntity = dynamic_cast<PhysicEntity*>(entity);
        if(pEntity != nullptr)
        {
            pEntity->setWorld(m_entityManager.getWorld());
        }
    }
    auto subEntities = item->findChildren<Entity*>();
    for(auto subEntity : subEntities)
    {
        handleAddedItem(subEntity);
    }
}

void Layer::itemChange(ItemChange change, const ItemChangeData& data)
{
    if(change == QQuickItem::ItemChildAddedChange)
    {
        handleAddedItem(data.item);
    }
    QQuickItem::itemChange(change, data);
}

QSGNode *Layer::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData)
{
    Q_UNUSED(updatePaintNodeData)
    QSGGeometryNode* node = nullptr;
    QSGGeometry* geometry = nullptr;
    auto pixelsPerMeter = m_entityManager.getWorld()->getPixelsPerMeter();
    if (!oldNode)
    {
        node = new QSGGeometryNode();
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), m_particleSystem->GetParticleCount());
        geometry->setLineWidth(m_particleSystem->GetRadius() * pixelsPerMeter);
        geometry->setDrawingMode(GL_POINTS);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        QSGVertexColorMaterial *material = new QSGVertexColorMaterial();
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    }
    else
    {
        node = static_cast<QSGGeometryNode*>(oldNode);
        geometry = node->geometry();
        geometry->allocate(m_particleSystem->GetParticleCount());
        geometry->setLineWidth(m_particleSystem->GetRadius() * pixelsPerMeter * 2.0);
    }
    QSGGeometry::ColoredPoint2D* vertices = geometry->vertexDataAsColoredPoint2D();
    auto positionBuffer = m_particleSystem->GetPositionBuffer();
    auto colorBuffer = m_particleSystem->GetColorBuffer();
    for(int i = 0; i < m_particleSystem->GetParticleCount(); i++)
    {
        vertices[i].set(positionBuffer[i].x * pixelsPerMeter,
                        -(positionBuffer[i].y * pixelsPerMeter),
                        colorBuffer[i].r,
                        colorBuffer[i].g,
                        colorBuffer[i].b,
                        colorBuffer[i].a);
    }
    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}

void Layer::componentComplete()
{
    setWidth(window()->width());
    setWidth(window()->height());
    connect(window(), &QQuickWindow::widthChanged, [&]()
    {
        setWidth(window()->width());
    });
    connect(window(), &QQuickWindow::heightChanged, [&]()
    {
        setHeight(window()->height());
    });
    setWidth(width());
    QQuickItem::componentComplete();
}

qint32 Layer::getMaximumParticleCount() const
{
    return m_particleSystem->GetMaxParticleCount();
}

void Layer::setMaximumParticleCount(qint32 maximumParticleCount)
{
    m_particleSystem->SetMaxParticleCount(maximumParticleCount);
}



void Layer::think(int delta)
{
    if(!m_paused)
    {
        m_entityManager.update(delta);
        update();
    }
}

qreal Layer::getGravX()
{
    return m_entityManager.getWorld()->getWorld()->GetGravity().x;
}

qreal Layer::getGravY()
{
    return m_entityManager.getWorld()->getWorld()->GetGravity().y;
}

void Layer::setGravX(const qreal &x)
{
    auto gravity = m_entityManager.getWorld()->getWorld()->GetGravity();
    gravity.x = x;
    m_entityManager.getWorld()->getWorld()->SetGravity(gravity);
}

void Layer::setGravY(const qreal &y)
{
    auto gravity = m_entityManager.getWorld()->getWorld()->GetGravity();
    gravity.y = y;
    m_entityManager.getWorld()->getWorld()->SetGravity(gravity);
}
