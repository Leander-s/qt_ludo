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
QOpenGLTexture *loadTexture(const char *path);

class GameOpenGLWidget : public QOpenGLWidget,
                         protected QOpenGLFunctions_3_3_Core {
  Q_OBJECT

public:
  explicit GameOpenGLWidget(QWidget *parent = nullptr);
  ~GameOpenGLWidget();
  void initializeGame(MapConfig _config, GameState *state);
  void updateAllPositions();
  void updatePosition(LudoColor color, int index);

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
  GameObject *createBoard(float tileSize);
  GameObject *createFigure(float tileSize, LudoColor color);

  QOpenGLTexture *loadTexture(const char *path);
  QOpenGLShaderProgram *shaderProgram;
  std::vector<Model> models;
  std::vector<GameObject *> gameObjects;
  GameState *gameState;
  MapConfig config;
};
} // namespace QtLudo
