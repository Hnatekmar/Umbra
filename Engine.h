
#ifndef ENGINE_H
#define ENGINE_H
#include <QQuickItem>
#include <QList>
#include <QElapsedTimer>
#include <QTimer>
#include <QQuickWindow>
#include <vector>
#include <QMap>
#include <algorithm>
#include <chrono>
#include "Scene.h"

 /*
  * class Engine
  *
  */
class Engine : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(unsigned currentScene READ getCurrentScene WRITE setCurrentScene)
public:

   explicit Engine (QQuickItem* parent = 0);

   unsigned getCurrentScene();
   void setCurrentScene(unsigned currentScene);

   void itemChange(ItemChange change, const ItemChangeData& data) override;

   /**
    * Zjisti, zda byla klavesa stisknuta
    * @return
    */
   Q_INVOKABLE bool isPressed(int key);

   virtual bool eventFilter(QObject * obj, QEvent * event) override;

   /**
    * @return poslední pozice myši v okně
    */
   Q_INVOKABLE QPoint getMousePos();

   /**
    * @return true v případě, že bylo stisknuto levé tlačítko myši
    */
   Q_INVOKABLE bool isLeftMouseButtonPressed();

   /**
    * @return true v případě, že bylo stisknuto pravé tlačítko myši
    */
   Q_INVOKABLE bool isRightMouseButtonPressed();

   /**
    * @return true v případě, že bylo stisknuto prostřední tlačítko myši
    */
   Q_INVOKABLE bool isMiddleMouseButtonPressed();

   /**
    * @return natočení kolečka myši
    */
   Q_INVOKABLE qreal getMouseDelta();

private slots:
   void gameTick();

private:
   /**
    * @brief Zaznamená událost puštení klávesy
    * @param event - klávesová událost
    */
   void keyUp(QKeyEvent *event);

   /**
    * @brief Zaznamená událost stisknutí klávesy
    * @param event - klávesová událost
    */
   void keyDown(QKeyEvent* event);
   virtual void componentComplete() override;
   unsigned m_currentScene;
   QPoint m_mousePos;
   std::vector<Scene*> m_scenes;
   QMap<int, bool> m_pressedKeys;
   QTimer m_timer;
   QElapsedTimer m_elapsedTimer;
   Qt::MouseButtons m_mouseButtons;
   qreal m_mouseDelta;
};

#endif // ENGINE_H
