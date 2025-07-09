#pragma once
#include "ModelUtil.h"
#include "GLGameObject.h"
#include "State.h"
#include <QImage>
#include <QKeyEvent>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QWidget>

namespace QtLudo {
const std::array<QVector2D, 66> positionMappings = {
    QVector2D(-6.0f, -6.0f), QVector2D(-3.0f, -6.0f), QVector2D(-6.0f, -3.0f),
    QVector2D(-3.0f, -3.0f), QVector2D(-7.0f, -1.0f), QVector2D(-6.0f, -1.0f),
    QVector2D(-5.0f, -1.0f), QVector2D(-4.0f, -1.0f), QVector2D(-3.0f, -1.0f),
    QVector2D(-2.0f, -1.0f), QVector2D(-1.0f, -1.0f), QVector2D(-1.0f, -2.0f),
    QVector2D(-1.0f, -3.0f), QVector2D(-1.0f, -4.0f), QVector2D(-1.0f, -5.0f),
    QVector2D(-1.0f, -6.0f), QVector2D(-1.0f, -7.0f), QVector2D(0.0f, -7.0f),
    QVector2D(1.0f, -7.0f),  QVector2D(1.0f, -6.0f),  QVector2D(1.0f, -5.0f),
    QVector2D(1.0f, -4.0f),  QVector2D(1.0f, -3.0f),  QVector2D(1.0f, -2.0f),
    QVector2D(1.0f, -1.0f),  QVector2D(2.0f, -1.0f),  QVector2D(3.0f, -1.0f),
    QVector2D(4.0f, -1.0f),  QVector2D(5.0f, -1.0f),  QVector2D(6.0f, -1.0f),
    QVector2D(7.0f, -1.0f),  QVector2D(7.0f, 0.0f),   QVector2D(7.0f, 1.0f),
    QVector2D(6.0f, 1.0f),   QVector2D(5.0f, 1.0f),   QVector2D(4.0f, 1.0f),
    QVector2D(3.0f, 1.0f),   QVector2D(2.0f, 1.0f),   QVector2D(1.0f, 1.0f),
    QVector2D(1.0f, 2.0f),   QVector2D(1.0f, 3.0f),   QVector2D(1.0f, 4.0f),
    QVector2D(1.0f, 5.0f),   QVector2D(1.0f, 6.0f),   QVector2D(1.0f, 7.0f),
    QVector2D(0.0f, 7.0f),   QVector2D(-1.0f, 7.0f),  QVector2D(-1.0f, 6.0f),
    QVector2D(-1.0f, 5.0f),  QVector2D(-1.0f, 4.0f),  QVector2D(-1.0f, 3.0f),
    QVector2D(-1.0f, 2.0f),  QVector2D(-1.0f, 1.0f),  QVector2D(-2.0f, 1.0f),
    QVector2D(-3.0f, 1.0f),  QVector2D(-4.0f, 1.0f),  QVector2D(-5.0f, 1.0f),
    QVector2D(-6.0f, 1.0f),  QVector2D(-7.0f, 1.0f),  QVector2D(-7.0f, 0.0f),
    QVector2D(-6.0f, 0.0f),  QVector2D(-5.0f, 0.0f),  QVector2D(-4.0f, 0.0f),
    QVector2D(-3.0f, 0.0f),  QVector2D(-2.0f, 0.0f),  QVector2D(-1.0f, 0.0f),
};

QOpenGLTexture *loadTexture(const char *path);

class GameOpenGLWidget : public QOpenGLWidget,
                         protected QOpenGLFunctions_3_3_Core {
  Q_OBJECT

public:
  explicit GameOpenGLWidget(QWidget *parent = nullptr);
  ~GameOpenGLWidget();
  void initializeGame(GameState *state);

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  // void keyPressEvent(QKeyEvent *event) override;
  void initializeGameObject(GameObject *gameObject);

  /*
signals:
  void pauseGame();
  */

private:
  QVector2D positionToCoords(LudoColor color, uint8_t position,
                             float tileSize = 1.0f);
  std::vector<GameObject *> createObjects();
  void updateAllPositions();
  void updatePosition(LudoColor color, int index);
  GameObject *createBoard(float tileSize);
  GameObject *createFigure(float tileSize, LudoColor color);

  QOpenGLTexture *loadTexture(const char *path);
  QOpenGLShaderProgram *shaderProgram;
  std::vector<Model> models;
  std::vector<GameObject *> gameObjects;
  GameState *gameState;
};
} // namespace QtLudo
