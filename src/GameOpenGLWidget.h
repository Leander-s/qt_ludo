#pragma once
#include "GLGameObject.h"
#include "Map.h"
#include "ModelUtil.h"
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
  void initializeGame(Map *_map, GameState *_state);
  void updateAllPositions();
  void updatePosition(const quint8 totalFigureIndex);

protected:
  void initializeGL() override;
  void resizeGL(const int w, const int h) override;
  void paintGL() override;
  void initializeGameObject(GameObject *gameObject);

  /*
signals:
  void pauseGame();
  */

private:
  std::vector<GameObject *> createObjects();
  GameObject *createBoard();
  GameObject *createFigure(LudoColor color);
  QOpenGLTexture *loadTexture(const char *path);

  QOpenGLShaderProgram *shaderProgram;
  std::vector<Model> models;
  std::vector<GameObject *> gameObjects;
  GameState *gameState;
  Map *map;
  MapConfig config;
};
} // namespace QtLudo
