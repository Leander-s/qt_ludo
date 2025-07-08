#pragma once
#include "Game.h"
#include "ModelUtil.h"
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

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  //void keyPressEvent(QKeyEvent *event) override;
  void initializeGameObject(GameObject *gameObject);

  /*
signals:
  void pauseGame();
  */

private:
  QOpenGLTexture *loadTexture(const char *path);
  QOpenGLShaderProgram *shaderProgram;
  std::vector<Model> models;
  std::vector<GameObject *> gameObjects;
  Ludo *game;
};
} // namespace QtLudo
