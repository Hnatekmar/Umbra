#include "Engine.h"

Engine::Engine (QQuickItem* parent):  QQuickItem(parent),
                                      m_currentScene(0),
                                      m_scenes(),
                                      m_pressedKeys(),
                                      m_timer(),
                                      m_elapsedTimer(),
                                      m_mouseButtons(),
                                      m_mouseDelta()
{
     m_timer.setTimerType(Qt::PreciseTimer);
}

unsigned Engine::getCurrentScene()
{
    return m_currentScene;
}

void Engine::setCurrentScene(unsigned currentScene)
{
    if(currentScene < m_scenes.size())
    {
        m_scenes.at(m_currentScene)->setVisible(false);
        m_currentScene = currentScene;
        m_scenes.at(m_currentScene)->setVisible(true);
    }
}

void Engine::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    if(change == QQuickItem::ItemChildAddedChange)
    {
        Scene* scene = dynamic_cast<Scene*>(data.item);
        if(scene != nullptr)
        {
            if(m_scenes.size()!=0)
            {
                scene->setVisible(false);
            }
            m_scenes.push_back(scene);
        }
    }
    QQuickItem::itemChange(change, data);
}

bool Engine::isPressed(int key)
{
    return m_pressedKeys[key];
}

bool Engine::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->type() == QKeyEvent::KeyPress)
        {
            keyUp(keyEvent);
        }
        else
        {
            keyDown(keyEvent);
        }
    }
    else if(event->type() == QEvent::MouseMove)
    {
        m_mousePos = static_cast<QMouseEvent*>(event)->pos();
    }
    else if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease)
    {
        m_mouseButtons = static_cast<QMouseEvent*>(event)->buttons();
    }
    else if(event->type() == QEvent::Wheel)
    {
        auto wheelEvent = static_cast<QWheelEvent*>(event);
        m_mouseDelta = wheelEvent->delta() / 180;
    }
    return QObject::eventFilter(obj, event);
}

void Engine::gameTick()
{
    if(m_scenes.size() != 0)
    {
        m_timer.stop();
        m_scenes.at(m_currentScene)->think(m_elapsedTimer.restart());
        m_pressedKeys.clear();
        m_timer.start();
    }
}

void Engine::componentComplete()
{
    qDebug() << "Engine inicializovan";
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(gameTick()));
    m_timer.setInterval(16); // 60 fps
    m_timer.start();
    m_elapsedTimer.start();
    window()->installEventFilter(this);
    QQuickItem::componentComplete();
}

void Engine::keyUp(QKeyEvent *event)
{
    m_pressedKeys[event->key()] = true;
}

void Engine::keyDown(QKeyEvent *event)
{
    m_pressedKeys[event->key()] = false;
}

QPoint Engine::getMousePos()
{
    return m_mousePos;
}

bool Engine::isLeftMouseButtonPressed()
{
    return m_mouseButtons & Qt::LeftButton;
}

bool Engine::isRightMouseButtonPressed()
{
    return m_mouseButtons & Qt::RightButton;
}

bool Engine::isMiddleMouseButtonPressed()
{
    return m_mouseButtons & Qt::MiddleButton;
}

qreal Engine::getMouseDelta()
{
    return m_mouseDelta;
}
