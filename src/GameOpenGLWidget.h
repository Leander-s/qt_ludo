#pragma once
#include "ModelUtil.h"
#include <QKeyEvent>
#include <QWidget>
#include <QtOpenGL/QOpenGLFunctions_3_3_Core>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <iostream>

namespace QtLudo {
class GameObject {
public:
  GameObject(const GameObject &other);
  GameObject(const Model &newModel);
  GameObject(const Model &newModel, const QVector3D &position);
  void translate(const QVector3D &translation);
  void rotate(float angle, const QVector3D &axis);

  QMatrix4x4 modelMatrix;
  Model model;
  GLuint VAO, VBO, IBO;
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

  void initializeGameObject(GameObject &gameObject);

signals:
  void pauseGame();

private:
  GLuint VAO, VBO, IBO;
  QOpenGLShaderProgram *shaderProgram;
  std::vector<Model> models;
  std::vector<GameObject> gameObjects;
};
} // namespace QtLudo
