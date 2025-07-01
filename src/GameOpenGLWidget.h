#pragma once
#include "ModelUtil.h"
#include <QImage>
#include <QKeyEvent>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QWidget>
#include <iostream>
#include <qopengltexture.h>

namespace QtLudo {
QOpenGLTexture *loadTexture(const char *path);
class GameObject {
public:
  GameObject(const Model &newModel, const char *texturePath);
  GameObject(const Model &newModel, const QVector3D &position,
             const char *texturePath);
  ~GameObject();
  void translate(const QVector3D &translation);
  void rotate(float angle, const QVector3D &axis);

  QMatrix4x4 modelMatrix;
  Model model;
  GLuint VAO, VBO, IBO;
  QString texturePath;
  QOpenGLTexture *texture;
  bool ready;
};
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
  void keyPressEvent(QKeyEvent *event) override;
  void initializeGameObject(GameObject *gameObject);

signals:
  void pauseGame();

private:
  void createBoard(float tileSize);
  QOpenGLShaderProgram *shaderProgram;
  std::vector<Model> models;
  std::vector<GameObject *> gameObjects;
};
} // namespace QtLudo
